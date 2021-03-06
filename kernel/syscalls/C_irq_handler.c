#include "C_irq_handler.h"
#include "include.h"
#include "read.h"
#include "write.h"
#include "exit_handler.h"
/* C_IRQ_Handler */
extern volatile unsigned long global_timer;
extern int period;
void C_IRQ_Handler() {
    uint32_t mr = reg_read(OSTMR_OSMR_ADDR(0)); //read the match register
    reg_write(OSTMR_OSMR_ADDR(0), mr + period); //add 10 ms to the match register
    global_timer += 10; //increment global timer by 10 ms
}
