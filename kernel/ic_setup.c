//Group 17
//Peter Wei (pwei) and Vruti Sivakumaran (vsivakum)
#include <exports.h>
#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"
#include "include/types.h"
#include "enable_irq.h"

extern int period;

//setup the interrupt controller
void ic_setup() {
    uint32_t set_ic_mask = 0x1 << (INT_OSTMR_0);
    uint32_t clear_ic_mask = ~set_ic_mask;
    reg_set(INT_ICMR_ADDR, set_ic_mask);
    reg_clear(INT_ICMR_ADDR, clear_ic_mask); //only allow timer interrupt

    uint32_t clear_ic_level = set_ic_mask;
    reg_clear(INT_ICLR_ADDR, clear_ic_level); //allow timer interrupt irq

    reg_write(OSTMR_OSMR_ADDR(0), period); //begin with 10 ms interval

    uint32_t clear_os_timer_regs = 0x0;
    reg_write(OSTMR_OSMR_ADDR(1), clear_os_timer_regs); //clear mask register

    reg_write(OSTMR_OSMR_ADDR(2), clear_os_timer_regs); //clear mask register

    reg_write(OSTMR_OSMR_ADDR(3), clear_os_timer_regs); //clear mask register

    uint32_t clear_os_timer_IER = 0x1;
    reg_set(OSTMR_OIER_ADDR, clear_os_timer_IER); //clear the bit for timer interrupt
    reg_write(OSTMR_OSCR_ADDR, 0x1); //write 1 to the counter register
}
