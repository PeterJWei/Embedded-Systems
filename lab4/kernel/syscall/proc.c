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
#include "include.h"

//subroutine of selection sort
void swap_tasks(task_t** t, int i, int j) {
    task_t* temp = t[j];
    t[j] = t[i];
    t[i] = temp;
}

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    if (num_tasks > 64) { //too many tasks
        return -EINVAL;
    }
    if (!valid_addr(tasks, (sizeof(task_t)*num_tasks), RAM_START_ADDR, RAM_END_ADDR)) {
        return -EFAULT; //bad address
    }
    uint8_t i, j;
    task_t** t = malloc(sizeof(task_t*) * num_tasks);
    for (i = 0; i < num_tasks; i++) {
        t[i] = &tasks[i]; //set pointers
    }
    for (i = 0; i < num_tasks-1; i++) {
        for (j = i+1; j < num_tasks; j++) {
            if (t[i]->T > t[j]->T) {
                swap_tasks(t, i, j); //selection sort tasks by period
            }
        }
    }
    if (!assign_schedule(t, num_tasks)) { //run ub_test
        return -ESCHED;
    }
    allocate_tasks(t, num_tasks); //initialize tcbs
    dispatch_nosave();
    return 1;
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
    if (dev > 3) { //bad dev
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
