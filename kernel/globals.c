/*
 * globals.c: Defines the global variables
 *
 * Author: Mike Kasick <mkasick@andrew.cmu.edu>
 * Date:   Sun, 07 Oct 2007 01:31:00 -0400
 */

int user_setup_stack_ptr;
int irq_setup_stack_ptr;
volatile unsigned long global_timer;
unsigned long curr_time;
int period;
