/** @file dagger.c
 *
 * @brief Creates two simple periodic tasks.
 *
 * @note  This is like knife -- but smaller :)
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-30
 */
#include <stdio.h>
#include <task.h>
#include <lock.h>
#include <unistd.h>


void panic(const char* str)
{
	puts(str);
	while(1);
}

void fun1(void* str)
{
	while(1)
	{
		putchar((int)str);
		if (event_wait(0) < 0)
			panic("Dev 0 failed");
	}
}

void fun2(void* str)
{
	while(1)
	{
                mutex_lock(0);
		putchar(0x77);
		putchar(0x6f);
		putchar(0x72);
		putchar(0x6c);
		putchar(0x64);
                putchar(0xA);
                mutex_unlock(0);
		putchar((int)str);
		if (event_wait(1) < 0)
			panic("Dev 1 failed");
	}
}

void fun3(void* str)
{
	while(1)
	{
                mutex_lock(0);
		putchar(0x68);
		putchar(0x65);
		putchar(0x6c);
		putchar(0x6c);
		putchar(0x6f);
//                while(1) {}
                mutex_unlock(0);
		putchar((int)str);
		if (event_wait(2) < 0)
			panic("Dev 2 failed");
	}
}

int main(int argc, char** argv)
{
        mutex_create();
	task_t tasks[2];
	tasks[0].lambda = fun1;
	tasks[0].data = (void*)'@';
	tasks[0].stack_pos = (void*)0xa2000000;
	tasks[0].C = 1;
	tasks[0].T = PERIOD_DEV0;
	tasks[0].B = 0;
	tasks[1].lambda = fun2;
	tasks[1].data = (void*)'<';
	tasks[1].stack_pos = (void*)0xa1000000;
	tasks[1].C = 1;
	tasks[1].T = PERIOD_DEV1;
	tasks[1].B = 0;
	tasks[2].lambda = fun3;
	tasks[2].data = (void*)'$';
	tasks[2].stack_pos = (void*)0xa1800000;
	tasks[2].C = 1;
	tasks[2].T = PERIOD_DEV2;
	tasks[2].B = 0;

	task_create(tasks, 3);
	argc=argc; /* remove compiler warning */
	argv[0]=argv[0]; /* remove compiler warning */

	puts("Why did your code get here!\n");
	return 0;
}
