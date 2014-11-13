/**
 * @file    time.c
 * 
 * @brief    time() system call
 * 
 * Group 17
 *
 * Names: Peter Wei <pwei@andrew.cmu.edu>
 *	  Vruti Sivakumaran <vsivakum@andrew.cmu.edu>
*/
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#define MS_PER_OVERFLOW ((uint32_t) ((UINT_MAX /OSTMR_FREQ)*1000u))

extern unsigned long curr_time;
extern volatile unsigned long global_timer;
unsigned long time() {
    //Set current time to value of global timer
    curr_time = global_timer;
    //Return global timer
    return global_timer;
}
