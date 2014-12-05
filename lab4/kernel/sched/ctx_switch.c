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
//    printf("save\n");
    uint8_t pcur = get_cur_prio();
    tcb_t* tcur = get_cur_tcb();
    void *ctxcur = (void *)(&(tcur->context));
//    hexdump(ctxcur, 0x30);
//    printf("%#x\n", (uint32_t)(tcur->context.lr));
//    printf("%#x\n", (uint32_t)(tcur->context.sp));

    uint8_t prio = highest_prio();
//    printf("%#x\n", prio);

    tcb_t* t = runqueue_remove(prio);
    void *ctx = (void *)(&(t->context));
//    printf("%#x\n", (uint32_t)t);
//    printf("%#x\n", (uint32_t)tcur);
   hexdump(ctx, 0x30);

    runqueue_add(tcur, pcur); //put back the old task into the runnable queue

    cur_tcb = t;
//    KSHIGH = t->kstack_high;
//    printf("save pointers %#x %#x\n", (uint32_t)(ctxcur), (uint32_t)(ctx));
//    printf("%#x\n", (uint32_t)(t->context.lr));
//    printf("%#x\n\n", (uint32_t)(t->context.sp));
//    printf("%#x\n", (uint32_t)(t->context.r6));
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
//    printf("nosave\n");
    uint8_t prio = highest_prio();
    tcb_t* t = runqueue_remove(prio);
    cur_tcb = t;
    void *ctx = (void *)(&(t->context));
//    printf("nosave pointers %#x\n", (uint32_t)(ctx));
//    printf("%#x\n", (uint32_t)(t->context.r6));
//    printf("%#x\n", (uint32_t)t);
    hexdump(ctx, 0x30);
//    KSHIGH = t->kstack_high;
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
//    printf("sleep\n");
    tcb_t* tcur = get_cur_tcb();
    void *ctxcur = (void *)(&(tcur->context));

//    hexdump(ctxcur, 0x30);
 //   printf("%#x\n", (uint32_t)(tcur->context.lr));
 //   printf("%#x\n", (uint32_t)(tcur->context.sp));
    uint8_t prio = highest_prio();

    tcb_t* t = runqueue_remove(prio);
    void *ctx = (void *)(&(t->context));
//    printf("%#x\n", (uint32_t)t);
//    printf("%#x\n", (uint32_t)tcur);
    hexdump(ctx, 0x30);
//    printf("sleep pointers %#x %#x\n", (uint32_t)(ctxcur), (uint32_t)(ctx));
//    printf("%#x\n", (uint32_t)(t->context.lr));
//    printf("%#x\n\n", (uint32_t)(t->context.sp));
//    printf("%#x\n", (uint32_t)(t->context.r6));
    cur_tcb = t;
//    KSHIGH = t->kstack_high;
    ctx_switch_full(ctx, ctxcur);
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
    return cur_tcb->cur_prio; //fix this; dummy return to prevent compiler warning
}

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
    return cur_tcb;
}
