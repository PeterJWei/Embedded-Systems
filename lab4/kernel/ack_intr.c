//Group 17
//Peter Wei (pwei) and Vruti Sivakumaran (vsivakum)

#include <exports.h>
#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"
#include "include/types.h"
#include "enable_irq.h"

//writes to the ossr that interrupt has been dealt with
int ack_intr() {
    uint32_t ossr = reg_read(OSTMR_OSSR_ADDR); //read ossr
    reg_write(OSTMR_OSSR_ADDR, 0x1); //mask bit 0 of ossr
    return (ossr & 0x1);
}
