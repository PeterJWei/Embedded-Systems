#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"

void IC_setup() {
    uint32_t set_ic_mask = 0x1 << (INT_OSTMR_0-1);
    reg_set(INT_ICMR_ADDR, set_ic_mask);

    uint32_t clear_ic_level = set_ic_mask;
    reg_clear(INT_ICLR_ADDR, clear_ic_level);

    
}
