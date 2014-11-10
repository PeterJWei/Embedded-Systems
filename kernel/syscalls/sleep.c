#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>
#include "../interrupts/interrupts.h"
#include "../interrupts/timers.h"

//size for each overflow
#define OVERFLOW_MS ((UINT_MAX / OSTMR_FREQ) * 1000)

void sleep(unsigned long ms) {
   uint32_t overflow = ms / OVERFLOW_MS;
   uint32_t r = get_ticks(ms % OVERFLOW_MS);

   reg_write(OSTMR_OSMR_ADDR(0), reg_read(OSTMR_OSCR_ADDR));
   while (sleep_interrupts < overflow);

   reg_write(OSTMR_OSMR_ADDR(0), reg_read(OSTMR_OSCR_ADDR) + r);
   while(sleep_interrupts == overflows_needed);

   sleep_interrupts=0;
}
