/**
 * @file  start.S
 *
 * @brief Kernel startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Tue, 23 Oct 2007 11:20:33 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-07-06
 */

#include <asm.h>

	.file   "disable_interrupts.S"
        .global disable_interrupts

disable_interrupts:
    stmfd   sp!, {r0-r12, lr}
    mrs     r3, cpsr
    orr     r3, #0xC0
    msr     cpsr, r3
    ldmfd   sp!, {r1-r12, lr}
    movs    pc, lr
