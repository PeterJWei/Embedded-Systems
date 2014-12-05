/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>

#define NULL 0 

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

void sched_init(task_t* main_task  __attribute__((unused)))
{
	
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */
 
static void __attribute__((unused)) idle(void)
{
	 enable_interrupts();
	 while(1);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    uint8_t i;
    for (i = 0; i < num_tasks; i++) {
        system_tcb[i].native_prio = i;
        system_tcb[i].cur_prio = i;
        system_tcb[i].holds_lock = 0;
        system_tcb[i].sleep_queue = NULL;
        system_tcb[i].context.r4 = (uint32_t) (tasks[i]->lambda); //function name
        system_tcb[i].context.r5 = (uint32_t) (tasks[i]->data); //function args
        system_tcb[i].context.r6 = (uint32_t) (tasks[i]->stack_pos); //function stack pointer
        system_tcb[i].context.lr = launch_task; //set entry
        system_tcb[i].context.sp = (void *)(&(system_tcb[i].kstack_high[0])); //set kernel stack
        runqueue_add(&(system_tcb[i]), i); //add to runqueue
    }
    system_tcb[num_tasks].native_prio = num_tasks;
    system_tcb[num_tasks].cur_prio = num_tasks;
    system_tcb[num_tasks].holds_lock = 0;
    system_tcb[num_tasks].sleep_queue = NULL;
    system_tcb[num_tasks].context.r4 = (uint32_t) &(idle); //setup idle task
    system_tcb[num_tasks].context.r5 = (uint32_t) 'q';
    system_tcb[num_tasks].context.r6 = (uint32_t) 0xa1100000; //arbitrary stack position
    system_tcb[num_tasks].context.lr = launch_task;
    system_tcb[num_tasks].context.sp = (void *)(&(system_tcb[num_tasks].kstack_high[0]));
    runqueue_add(&(system_tcb[num_tasks]), num_tasks);
}
