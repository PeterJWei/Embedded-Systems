#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"
#include "include/types.h"

void ic_setup() {
    uint32_t set_ic_mask = 0x1 << (INT_OSTMR_0-1);
    reg_set(INT_ICMR_ADDR, set_ic_mask);
//    volatile uint32_t *reg = (volatile uint32_t*)(INT_ICMR_ADDR);
//    *reg = *reg | set_ic_mask;

    uint32_t clear_ic_level = set_ic_mask;
    reg_clear(INT_ICLR_ADDR, clear_ic_level);
//    reg = (volatile uint32_t*)(INT_ICLR_ADDR);
//    *reg = *reg & (~clear_ic_level);

    uint32_t clear_os_timer_regs = 0xFFFFFFFF;   
    reg_clear(OSTMR_OSSR_M0, clear_os_timer_regs);
//    reg = (volatile uint32_t*)(OSTMR_OSSR_M0);
//    *reg = *reg & (~clear_os_timer_regs);

    reg_clear(OSTMR_OSSR_M1, clear_os_timer_regs);
//    reg = (volatile uint32_t*)(OSTMR_OSSR_M1);
//    *reg = *reg & (~clear_os_timer_regs);

    reg_clear(OSTMR_OSSR_M2, clear_os_timer_regs);
//    reg = (volatile uint32_t*)(OSTMR_OSSR_M2);
//    *reg = *reg & (~clear_os_timer_regs);

    reg_clear(OSTMR_OSSR_M3, clear_os_timer_regs);
//    reg = (volatile uint32_t*)(OSTMR_OSSR_M3);
//    *reg = *reg & (~clear_os_timer_regs);

    uint32_t clear_os_timer_IER = 0x1;
    reg_clear(OSTMR_OIER_ADDR, clear_os_timer_IER);
//    reg = (volatile uint32_t*)(OSTMR_OIER_ADDR);
//    *reg = *reg & (~clear_os_timer_IER);
}
