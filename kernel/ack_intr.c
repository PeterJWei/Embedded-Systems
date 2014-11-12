#include <exports.h>
#include "include/arm/timer.h"
#include "include/arm/interrupt.h"
#include "include/arm/reg.h"
#include "include/types.h"
#include "enable_irq.h"

int ack_intr() {
    uint32_t ossr = reg_read(OSTMR_OSSR_ADDR);
    reg_write(OSTMR_OSSR_ADDR, 0x1);
    return (ossr & 0x1);
}
