#include "C_irq_handler.h"
#include "include.h"
#include "read.h"
#include "write.h"
#include "exit_handler.h"
/* C_IRQ_Handler */
extern int global_timer;
void C_IRQ_Handler() {
    uint32_t mr = reg_read(OSTMR_OSMR_ADDR(0));
    reg_write(OSTMR_OSMR_ADDR(0), mr + 3686400);
    global_timer++;
    printf("global timer! %d\n", global_timer);
}
