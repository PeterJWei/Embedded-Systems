#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>

//size for each overflow
#define OVERFLOW_MS ((UINT_MAX / OSTMR_FREQ) * 1000)

void sleep(unsigned long ms) {
   unsigned long end_time = get_clock() -4 + ms;
   while (end_time!=get_clock());
}
