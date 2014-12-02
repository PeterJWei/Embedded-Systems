/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <bits/swi.h>

	.file "task_create.S"
        .global task_create

@int task_create(task_t* tasks, size_t num_tasks)
task_create:
    swi CREATE_SWI

    @ if failure
    cmp r0, #0
    movpl pc, lr @pl means >= 0

    @ Store the absolute value of return value in errno
    neg r0, r0
    ldr r1, =errno
    str r0, [r1]

    @ Store -1 in return value
    mov r0, #-1
    mov pc, lr
