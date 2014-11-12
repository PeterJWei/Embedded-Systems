#include "C_irq_handler.h"
#include "include.h"
#include "read.h"
#include "write.h"
#include "exit_handler.h"
/* C_IRQ_Handler */
void C_IRQ_Handler() {
    printf("hello from IRQ handler!\n");
//    printf("current time: %#x\n", 
    getc();

   // return count;
}
