/** @file inversion.c
 *
 * @brief Simple test for priority inversion
 *
 * @author Tao Yang(taoy)
 * @date   2010-11-30
 */
#include <stdio.h>
#include <unistd.h>
#include <task.h>
#include <lock.h>


volatile int inv[3];
volatile int mid = -1;
volatile int once = 0;

void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{	
	mid = mutex_create();
	if(mid < 0) panic("Can not create Mutex???");
	while(1) {
		puts("In 1 ");
		mutex_lock(mid);
		mutex_unlock(mid);
	
		// check inversion
		if(inv[1] > inv[0]) {
			panic("Priority inverted: FAIL **************");
		}
		// make sure prioritis are restroed
		else if(inv[2] > inv[0]) {
			panic("Priority not restored: FAIL **************");
		} else if(inv[2] == 3) {
			panic("Test complete");
		}
		inv[0]++;
		if (event_wait(0) < 0) {
					panic("Dev 0 failed");
		}
	}	
	str = str;
}

void fun2(void* str)
{
	while(1)
	{
		puts("In 2");
		inv[1]++;
		if (event_wait(1) < 0)
			panic("Dev 1 failed");
	}
	str = str;
}

void fun3(void* str)
{
	while(1)
	{
		puts("In 3");
		mutex_lock(mid);
		sleep(1000);	// this would be atomic if HLP is implemented
		mutex_unlock(mid);
		inv[2]++;
		if (event_wait(2) < 0)
			panic("Dev 2 failed");
	}
	str = str;
}
int main(int argc, char** argv)
{
	once = 0;
	inv[0] = 0;
	inv[1] = 0;
	inv[2] = 0;
	task_t tasks[3];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'A';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].B = 1;
	tasks[0].T = PERIOD_DEV3; // 50
	tasks[1].lambda = fun2;
	tasks[1].data = (void*)'B';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].B = 1;
	tasks[1].T = PERIOD_DEV0; // 100
	tasks[2].lambda = fun3;
	tasks[2].data = (void*)'C';
	tasks[2].stack_pos = (void*)0xa1200000;
	tasks[2].C = 1;
	tasks[2].B = 1;
	tasks[2].T = PERIOD_DEV1;	// 200
	puts("Test begin");
	task_create(tasks, 3);
	puts("*********** TASK CREATE FAIL ******************!");
	argc = argc;
	argv = argv;
	return 0;
}
