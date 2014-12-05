/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author Harry Q Bovik < PUT YOUR NAMES HERE
 *
 * 
 * @date  
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

mutex_t gtMutex[OS_NUM_MUTEX];

void mutex_init()
{
    int i;
    for (i = 0; i < OS_NUM_MUTEX; i++) {
        //set everything to not available and not locked
        gtMutex[i].bAvailable = 0;
        gtMutex[i].bLock = 0;
    }
}

int mutex_create(void)
{
    disable_interrupts();
    int i;
    for (i = 0; i < OS_NUM_MUTEX; i++) {
        //if mutex is not available
        if (!gtMutex[i].bAvailable) {
            //make available
            gtMutex[i].bAvailable = 1;
            //unlock
            gtMutex[i].bLock = 0;
            enable_interrupts();
            return i;
        }
    }
    enable_interrupts();
    return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
    disable_interrupts();
    tcb_t *t = get_cur_tcb();
    //if mutex number is incorrect or if the mutex is not available
    if (mutex > OS_NUM_MUTEX || !gtMutex[mutex].bAvailable) {
        return -EINVAL;
    }
    //if mutex is already held by itself
    if (gtMutex[mutex].bLock == 1 && gtMutex[mutex].pHolding_Tcb == t) {
        return -EDEADLOCK; //if task already holding the lock
    } else if (gtMutex[mutex].bLock == 1) {
        //if someone else is holding the lock
#ifdef DEBUG_MUTEX
        printf("process %d holding lock!\n", gtMutex[mutex].pHolding_Tcb->native_prio);
#endif
        t->sleep_queue = gtMutex[mutex].pSleep_queue;
        gtMutex[mutex].pSleep_queue = t;
        //put on sleep queue
        enable_interrupts();
        dispatch_sleep();
    }
    //if not locked, lock it and now we hold the lock
    gtMutex[mutex].bLock = 1;
    t->holds_lock = 1;
    gtMutex[mutex].pHolding_Tcb = t;
    enable_interrupts();
    return 0;
}

#define MULTIMUTEX
int mutex_unlock(int mutex  __attribute__((unused)))
{
#ifdef MULTIMUTEX
    int i;
#endif
    disable_interrupts();
    tcb_t *t = get_cur_tcb();
    //if mutex number is incorrect or if the mutex is not available
    if (mutex > OS_NUM_MUTEX || !gtMutex[mutex].bAvailable) {
        return -EINVAL;
    }
    //if mutex is not held by us or unlocked
    if (!gtMutex[mutex].bLock == 1 || (gtMutex[mutex].pHolding_Tcb != t)) {
        return -EPERM;
    }
    gtMutex[mutex].bLock = 0; //unlock
    gtMutex[mutex].pHolding_Tcb = 0; //clear tcb holding
    tcb_t *next_t = gtMutex[mutex].pSleep_queue;
    if (next_t) { //if we find a tcb waiting for the mutex, add to runnable queue
        gtMutex[mutex].pSleep_queue = next_t->sleep_queue;
#ifdef DEBUG_MUTEX
        printf("%d taken off sleep queue\n", next_t->native_prio);
#endif
        runqueue_add(next_t, next_t->native_prio);
    }
#ifdef MULTIMUTEX
    for (i = 0; i < OS_NUM_MUTEX; i++) { //look for if we are holding more mutexes
        if (!gtMutex[i].bAvailable) {
            t->holds_lock = 0; //if we reach end of valid mutexes
            break;
        }
        if (gtMutex[mutex].bLock == 1 && gtMutex[mutex].pHolding_Tcb == t) { //if we are holding a mutex
            t->holds_lock = 1;
            break;
        }
        t->holds_lock = 0; //we aren't holding any mutexes
    }
#endif
#ifndef MULTIMUTEX
    t->holds_lock = 0;
#endif
    enable_interrupts();
    return 0;
}

