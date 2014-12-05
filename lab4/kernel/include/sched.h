/** @file sched.h
 *
 * @brief Declares core scheduler and task management routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-21
 */

#ifndef SCHED_H
#define SCHED_H

#include <task.h>
#include <types.h>

void sched_init(task_t* main_task);

/* Scheduler invocations */
void dispatch_save(void);
void dispatch_nosave(void);
void dispatch_sleep(void);

/* Entry assist */
void launch_task(void); /* takes lambda and argument in r4, r5 */

/* Task initialization */
void allocate_tasks(task_t** tasks, size_t num_tasks);
int assign_schedule(task_t** tasks, size_t num_tasks);

/* Current task state */
uint8_t get_cur_prio(void);
tcb_t* get_cur_tcb(void);

/* Run-queue/priority management */
void runqueue_add(tcb_t* tcb, uint8_t prio);
tcb_t* runqueue_remove(uint8_t prio);
tcb_t* runqueue_peek(uint8_t prio);
uint8_t highest_prio(void);

double max_ub[OS_MAX_TASKS] = {1.0000, 0.8280, 0.7790, 0.7560, 0.7430, 0.7340, 0.7280, 0.7240, 
                            0.7200, 0.7180, 0.7150, 0.7130, 0.7120, 0.7105, 0.7090, 0.7080, 
                            0.7070, 0.7067, 0.7060, 0.7050, 0.7047, 0.7040, 0.7037, 0.7033, 
                            0.7028, 0.7025, 0.7021, 0.7018, 0.7015, 0.7012, 0.7010, 0.7007, 
                            0.7005, 0.7003, 0.7001, 0.6999, 0.6997, 0.6995, 0.6993, 0.6992, 
                            0.6990, 0.6989, 0.6988, 0.6986, 0.6985, 0.6984, 0.6983, 0.6982, 
                            0.6981, 0.6980, 0.6979, 0.6978, 0.6977, 0.6976, 0.6985, 0.6975, 
                            0.6974, 0.6973, 0.6972, 0.6972, 0.6971, 0.6970, 0.6970, 0.6969};
#endif /* SCHED_H */
