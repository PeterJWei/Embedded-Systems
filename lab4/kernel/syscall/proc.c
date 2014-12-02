/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>
#include "../disable_interrupts.h"

void swap_tasks(task_t** t, int i, int j) {
    task_t* temp = t[j];
    t[j] = t[i];
    t[i] = temp;
}

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    uint8_t i, j;
    task_t** t = malloc(sizeof(task_t*) * num_tasks);
    for (i = 0; i < num_tasks; i++) {
        t[i] = &tasks[i];
    }
    for (i = 0; i < num_tasks-1; i++) {
        for (j = i+1; j < num_tasks; j++) {
            if (t[i]->T > t[j]->T) {
                swap_tasks(t, i, j);
            }
        }
    }
    printf("hello!\n");
    allocate_tasks(t, num_tasks);
    printf("hello!\n");
    dispatch_nosave();
    printf("hello!\n");
    return 1;
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
    if (dev > 3) {
        return -EINVAL;
    }
    dev_wait(dev);
    return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	while(1);
}
