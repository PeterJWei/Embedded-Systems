/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include "sched_i.h"

#define DEBUG_MUTEX
#ifdef DEBUG_MUTEX
#include <exports.h>
#include "../syscall/include.h"
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
	
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
    uint8_t pcur = get_cur_prio();
    tcb_t* tcur = get_cur_tcb();
    void *ctxcur = (void *)(&(tcur->context)); //get our current context

    uint8_t prio = highest_prio();

    tcb_t* t = runqueue_remove(prio); //remove the new context
    void *ctx = (void *)(&(t->context));

    runqueue_add(tcur, pcur); //put back the old task into the runnable queue

    cur_tcb = t; //change to the new tcb
    ctx_switch_full(ctx, ctxcur);
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
    uint8_t prio = highest_prio(); //switch to the highest priority task
    tcb_t* t = runqueue_remove(prio); //remove from the run queue
    cur_tcb = t; //change to that task
    void *ctx = (void *)(&(t->context)); //get the context
    ctx_switch_half(ctx);
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
    tcb_t* tcur = get_cur_tcb(); //get the current tcb
    void *ctxcur = (void *)(&(tcur->context)); //get the current context

    uint8_t prio = highest_prio(); //get the next task

    tcb_t* t = runqueue_remove(prio);
    void *ctx = (void *)(&(t->context)); //get the context
    cur_tcb = t;
    ctx_switch_full(ctx, ctxcur);
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
    return cur_tcb->cur_prio;
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
    return cur_tcb;
}
