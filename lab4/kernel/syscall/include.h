#ifndef INCLUDE_H
#define INCLUDE_H
#include <exports.h>
#include "../include/assert.h"
#include <bits/errno.h>
#include <bits/fileno.h>
#include <bits/swi.h>
#include "../include/types.h"
#include "../globals.h"
#include "../include/arm/reg.h"
#include "../include/arm/timer.h"
#include "../include/arm/interrupt.h"
#include "../include/sched.h"
#include "../include/device.h"
// 0xe59ff014 (LDR pc, [pc, 0x14]) --> 0x014 through masking
#define SWI_VECT_ADDR 0x08
#define IRQ_VECT_ADDR 0x18
#define PC_OFFSET 0x08

// Cannot write to this address. kernel.bin loaded here. Stack grows down.
#define USER_STACK_TOP 0xa3000000

// (LDR pc, [pc, 0x000]) 0xe59ff000 --> 0x000 through masking
#define LDR_PC_PC_INSTR 0xe59ff000
#define LDR_SIGN_MASK 0x00800000

#define BAD_CODE 0x0badc0de

#define SFROM_START 0x00000000
#define SFROM_END 0x00ffffff
#define SDRAM_START 0xa0000000
#define SDRAM_END 0xa3ffffff

//typedef enum {FALSE, TRUE} bool;
int check_mem(char *buf, int count, unsigned start, unsigned end);
#endif
