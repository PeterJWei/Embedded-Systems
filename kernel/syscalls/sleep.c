#include <types.h>
#include <arm/reg.h>
#include <arm/timer.h>

void sleep(unsigned long ms) {
   unsigned long end_time = get_clock() -4 + ms
   while (end_time!=get_clock());
}
