#include "C_swi_handler.h"
#include "include.h"
#include "read.h"
#include "write.h"
#include "time.h"
#include "../check_ic.h"
#include "../include/task.h"
#include "../include/syscall.h"
/* C_SWI_Handler uses SWI number to call the appropriate function. */
int C_SWI_Handler(int swiNum, int *regs) {
    int count = 0;
    switch (swiNum) {
        // ssize_t read(int fd, void *buf, size_t count);
        case READ_SWI:
            count = read_handler(regs[0], (void *) regs[1], (size_t) regs[2]);
            break;
        // ssize_t write(int fd, const void *buf, size_t count);
        case WRITE_SWI:
            count = write_handler((int) regs[0], (void *) regs[1], (size_t) regs[2]);
            break;
        // void exit(int status);
//        case EXIT_SWI:
//            exit_handler((int) regs[0]); // never returns
//            break;
	case TIME_SWI:
	    count = time_syscall();
//            printf("got count: %d\n", (unsigned int)count);
	    break;
	case SLEEP_SWI:
	    sleep_syscall((int)regs[0]);
	    break;
        case CREATE_SWI:
            task_create((task_t *)regs[0], (size_t)regs[1]);
            break;
        case MUTEX_CREATE:
            printf("mutex create!\n");
            break;
        case MUTEX_LOCK:
            printf("mutex lock!\n");
            break;
        case MUTEX_UNLOCK:
            printf("mutex unlock!\n");
            break;
        case EVENT_WAIT:
            count = event_wait((unsigned int)regs[0]);
            break;
        default:
            printf("Error in ref C_SWI_Handler: Invalid SWI number.");
            count = 0;
//            exit_handler(BAD_CODE); // never returns
    }
    return count;
}
