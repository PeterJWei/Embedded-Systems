/**
*
*/

#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#define MS_PER_OVERFLOW ((uint32_t) ((UINT_MAX /OSTMR_FREQ)*1000u))

unsigned long time() {
	return get_clock();
	//return (clock_overflows*MS_PER_OVERFLOW)+ get_ms(reg_read(OSTMR_OSCR_ADDR));
}
