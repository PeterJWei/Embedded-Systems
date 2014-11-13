@ sleep.S: sleep sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>

	.file	"sleep.S"
	.text

	.global	sleep
@void sleep(unsigned int ms);
sleep:
    swi SLEEP_SWI @make the system call
    mov pc, lr
