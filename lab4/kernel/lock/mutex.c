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
        gtMutex[i].bAvailable = 0;
        gtMutex[i].bLock = 0;
    }
}

int mutex_create(void)
{
    int i;
    for (i = 0; i < OS_NUM_MUTEX; i++) {
        if (!gtMutex[i].bAvailable) {
            gtMutex[i].bAvailable = 1;
            gtMutex[i].bLock = 0;
            return i;
        }
    }
    return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
    tcb_t *t = get_cur_tcb();
    if (mutex > OS_NUM_MUTEX || !gtMutex[mutex].bAvailable) {
        return -EINVAL;
    }
    if (gtMutex[mutex].bLock == 1 && gtMutex[mutex].pHolding_Tcb == t) {
            return -EDEADLOCK; //if task already holding the lock
    } else if (gtMutex[mutex].bLock == 1) {
        t->sleep_queue = gtMutex[mutex].pSleep_queue;
        gtMutex[mutex].pSleep_queue = t;
        dispatch_sleep();
    }
    gtMutex[mutex].bLock = 1;
    gtMutex[mutex].pHolding_Tcb = t;
    return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
    tcb_t *t = get_cur_tcb();
    if (mutex > OS_NUM_MUTEX || !gtMutex[mutex].bAvailable) {
        return -EINVAL;
    }
    if (!gtMutex[mutex].bLock == 1 || (gtMutex[mutex].pHolding_Tcb != t)) {
            return -EPERM; //if task already holding the lock
    }
    gtMutex[mutex].bLock = 0;
    gtMutex[mutex].pHolding_Tcb = 0;
    tcb_t *next_t = gtMutex[mutex].pSleep_queue;
    gtMutex[mutex].pSleep_queue = next_t->sleep_queue;
    runqueue_add(next_t, next_t->native_prio);
    return 0;
}

