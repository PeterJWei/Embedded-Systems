//Group 17
//Peter Wei (pwei) and Vruti Sivakumaran (vsivakum)
#include <exports.h>
#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"
#include "include/types.h"

//helper function to see the system registers
void check_ic() {
    printf("pending register: %x %x\n", reg_read(INT_ICPR_ADDR), (reg_read(INT_ICPR_ADDR)>>25) & 0x1);
    printf("irq mask register: %x %x\n", reg_read(INT_ICMR_ADDR), (reg_read(INT_ICMR_ADDR)>>25) & 0x1);
    printf("irq level register: %d\n", reg_read(INT_ICLR_ADDR));
    printf("match register 0: %d\n", reg_read(OSTMR_OSMR_ADDR(0)));
    printf("timer: %d\n", reg_read(OSTMR_OSCR_ADDR));
    printf("ossr: %d\n", reg_read(OSTMR_OSSR_ADDR));
    getc();
}
