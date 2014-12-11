/** @file failub.c
 *
 * @brief 1. Creates task set to fail UB Test (C_i = T_i)
 *				2. Close failed UB tests
 *			  3. Make sure failed UB test did not modify task array
 * @author Austin Buchan
 *         Christopher Mar
 *         Kevin Woo 
 *
 * @date   2008-12-09
 *				 Modified by taoy at 2010/12/01
 */
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <bits/errno.h>
#include <errno.h>

volatile int spin = 0;
void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	puts("XXXXXXXXXXXX UB test FAIL XXXXXXXXXXXXXX");
	while(1)
	{
		spin++;
	}
	str = str;
}

void fun2(void* str)
{
	puts("XXXXXXXXXXXX In thread 2: FAIL XXXXXXXXXXXXXX");
	while(1)
	{
		spin++;
	}
	str = str;
}

int main(int argc, char** argv)
{
	int i = 0;
	task_t tasks[60];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'@';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = PERIOD_DEV0;
	tasks[0].B = 0;
	tasks[0].T = PERIOD_DEV0; // T=100
	tasks[1].lambda = fun2;
	tasks[1].data = (void*)'<';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[0].B = 0;
	tasks[1].T = PERIOD_DEV1; // T=200
	task_create(tasks, 2);
	if(errno != ESCHED) {
		puts("Failed UB test (simple case)");
	}
	else {
		puts("simple: Success  *******************");
	}

	// Longer fail
	for(i = 0;i<60; i++) {
		tasks[i].lambda = fun2;
		tasks[i].data = (void*)i;
		tasks[i].stack_pos = (void*)0xa1000000;
		tasks[i].C = 0;
		tasks[i].B = (float)i * 100;
		tasks[i].T = (float)i * 100 * 85; // T=200
	}
	task_create(tasks, 60);
	if(errno != ESCHED) {
		puts("Failed UB test (longer case)");
	} 
	else {
		puts("long : Success *******************");
	}
	
	// make sure they did not modify the task array
	for(i=0;i<60;i++) {
		if((int)(tasks[i].data) != i) {
			puts("Failed UB test modified task array");
			break;
		} 
	}	
	puts("Test complete");
	while(1) {
		spin++;
	}
	argc = argc;
	argv = argv;

	return 0;
}
