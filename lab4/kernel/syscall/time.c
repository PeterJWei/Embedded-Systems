/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>
#include <arm/reg.h>
#include "include.h"
#include <arm/psr.h>
#include "time.h"


extern volatile unsigned long global_timer;
unsigned long time_syscall(void) {
    return global_timer;
}



/** @brief Waits in a tight loop for atleast the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 * 
 */
void sleep_syscall(unsigned long millis  __attribute__((unused))) {
    //set start time
    unsigned long starttime = global_timer;
    //set end time
    unsigned long endtime = starttime + millis;
    //loop while global_timer is not yet end time
    while (global_timer <= endtime) {
    }
}
