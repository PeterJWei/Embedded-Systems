/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-12-01
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include "include/arm/interrupt.h"

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
   int i;
   /* the following line is to get rid of the warning and should not be needed	
   devices[0]=devices[0];*/
   for (i =0; i<NUM_DEVICES; i++) {
	devices[i].sleep_queue=0;
	devices[i].next_match=dev_freq[i];
   }
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev /*__attribute__((unused))*/)
{
	tcb_t *t = get_cur_tcb();
        
	t->sleep_queue=devices[dev].sleep_queue;
	devices[dev].sleep_queue=t;

	dispatch_sleep();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis/* __attribute__((unused))*/)
{
    tcb_t *t;
    int i;

    for(i = 0; i<NUM_DEVICES; i++) {
        //if device passed one period
        if(millis >= devices[i].next_match) {
            //update match register
            while (millis >= devices[i].next_match) {
                devices[i].next_match+=dev_freq[i];
            }
            //pull task from sleep_queue
            t=devices[i].sleep_queue;
            //add tasks to run queue
            while(t) {
                runqueue_add(t, t->native_prio);
                t=t->sleep_queue;
            }
            //reset sleep queue
        devices[i].sleep_queue=0;
    }
}
}

