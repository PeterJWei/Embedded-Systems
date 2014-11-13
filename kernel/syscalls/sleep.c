/**
 * @file   	sleep.c
 *
 * @brief   	sleep() system call.
 *
 * Group 17
 *
 * Names: Peter Wei <pwei@andrew.cmu.edu>
 *	  Vruti Sivakumaran <vsivakum@andrew.cmu.edu>
*/
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include "include.h"
#include <arm/psr.h>

extern unsigned long curr_time;
extern volatile unsigned long global_timer;
void sleep(unsigned long ms) {
    //set start time
    unsigned long starttime = global_timer;
    //set end time
    unsigned long endtime = starttime + ms;
    //loop while global_timer is not yet end time
    while (global_timer <= endtime) {
    }
}
