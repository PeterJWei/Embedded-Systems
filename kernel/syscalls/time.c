#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#define MS_PER_OVERFLOW ((uint32_t) ((UINT_MAX /OSTMR_FREQ)*1000u))

extern unsigned long curr_time;
extern volatile unsigned long global_timer;
unsigned long time() {
    curr_time = global_timer;
    return global_timer;
}
