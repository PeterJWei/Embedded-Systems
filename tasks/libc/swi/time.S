@ time.S: time sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>

	.file	"time.S"
	.text

	.global	time
@unsigned long time();
time:
    swi TIME_SWI @make the system call
    mov pc, lr
