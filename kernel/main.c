#include <exports.h>
#include <bits/errno.h>
#include <bits/fileno.h>
#include <bits/swi.h>

#include "globals.h"
#include "swi_handler.h"
#include "irq_handler.h"
#include "user_setup.h"
#include "syscalls/exit_handler.h"
#include "syscalls/read.h"
#include "syscalls/write.h"

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

#include "syscalls/include.h"

uint32_t global_data;

/* Checks the SWI Vector Table. */
bool check_swi_vector() {
    int swi_vector_instr = *((int *)SWI_VECT_ADDR);
    // Check if the offset is negative.
    if ((swi_vector_instr & LDR_SIGN_MASK) == 0) {
        return FALSE;
    }
    // Check that the instruction is a (LDR pc, [pc, 0x000])
    if ((swi_vector_instr & 0xFFFFF000) != LDR_PC_PC_INSTR) {
        return FALSE;
    }
    return TRUE;
}

bool check_irq_vector() {
    int irq_vector_instr = *((int *)IRQ_VECT_ADDR);
    // Check if the offset is negative.
    if ((irq_vector_instr & LDR_SIGN_MASK) == 0) {
        return FALSE;
    }
    // Check that the instruction is a (LDR pc, [pc, 0x000])
    if ((irq_vector_instr & 0xFFFFF000) != LDR_PC_PC_INSTR) {
        return FALSE;
    }
    return TRUE;
}

int kmain(int argc, char** argv, uint32_t table) {
    app_startup(); /* Note that app_startup() sets all uninitialized and */ 
		/* zero global variables to zero. Make sure to consider */
		/* any implications on code executed before this. */
    global_data = table;

    /* Add your code here */

    if (check_swi_vector() == FALSE || check_irq_vector() == FALSE) {
        return BAD_CODE;
    }

    /** Wire in the SWI and IRQ handlers. **/
    // Jump offset already incorporates PC offset. Usually 0x10 or 0x14.
    int jmp_offset_swi = (*((int *) SWI_VECT_ADDR))&(0xFFF);
    int jmp_offset_irq = (*((int *) IRQ_VECT_ADDR))&(0xFFF);

    // &S_Handler" in Jump Table.
    int *swi_handler_addr = *(int **)(SWI_VECT_ADDR + PC_OFFSET + jmp_offset_swi);
    int *irq_handler_addr = *(int **)(IRQ_VECT_ADDR + PC_OFFSET + jmp_offset_irq);

    // Save original Uboot SWI handler instructions.
    int swi_instr_1 = *swi_handler_addr;
    int swi_instr_2 = *(swi_handler_addr + 1);
    int irq_instr_1 = *irq_handler_addr;
    int irq_instr_2 = *(irq_handler_addr + 1);

    // Wire in our own: LDR pc, [pc, #-4] = 0xe51ff004
    *swi_handler_addr = 0xe51ff004;
    *(swi_handler_addr + 1) = (int) &swi_handler; // New swi handler.
    *irq_handler_addr = 0xe51ff004;
    *(irq_handler_addr + 1) = (int) &irq_handler; // New swi handler.

    // Copy argc and argv to user stack in the right order.
    int *spTop = ((int *) USER_STACK_TOP) - 1;
    int i = 0;
    for (i = argc-1; i >= 0; i--) {
        *spTop = (int)argv[i];
        spTop--;
    }
    *spTop = argc;

    printf("got here\n");
    getc();
    /** Jump to user program. **/
    int usr_prog_status = user_setup(spTop);


    /** Restore SWI Handler. **/
    *swi_handler_addr = swi_instr_1;
    *(swi_handler_addr + 1) = swi_instr_2;
    *irq_handler_addr = irq_instr_1;
    *(irq_handler_addr + 1) = irq_instr_2;

    return usr_prog_status;
}
