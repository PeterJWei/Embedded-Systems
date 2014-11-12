#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include "include.h"
#include <arm/psr.h>

#define MS_PER_OVERFLOW ((uint32_t) ((UINT_MAX /OSTMR_FREQ)*1000u))

extern unsigned long curr_time;
extern volatile unsigned long global_timer;
//extern int period;
void sleep(unsigned long ms) {
    unsigned long starttime = global_timer;
    unsigned long endtime = starttime + ms;
    while (global_timer <= endtime) {
    }
}
