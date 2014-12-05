/** @file ub_test.c
 * 
 * @brief The UB Test for basic schedulability
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

//#define DEBUG 0

#include <sched.h>
#ifdef DEBUG
#include <exports.h>
#endif

 
/**
 * @brief Perform UB Test and reorder the task list.
 *
 * The task list at the end of this method will be sorted in order is priority
 * -- from highest priority (lowest priority number) to lowest priority
 * (highest priority number).
 *
 * @param tasks  An array of task pointers containing the task set to schedule.
 * @param num_tasks  The number of tasks in the array.
 *
 * @return 0  The test failed.
 * @return 1  Test succeeded.  The tasks are now in order.
 */

double uRef[64]= {1.0000, 0.82842, 0.77976, 0.75682, 0.74349, 0.73477, 0.72862, 0.72406, 0.72053, 0.71773, 0.71545, 0.71355, 0.71195, 0.71059, 0.70941, 0.70838, 0.70747, 0.70666, 0.70594, 0.70529, 0.70471, 0.70418, 0.70369, 0.70325, 0.70284, 0.70246, 0.70212, 0.70179, 0.70149, 	0.70121, 0.70095, 0.70070, 0.70047, 0.70026, 0.70005, 0.69986, 0.69968, 0.69950, 0.69934, 0.69918, 0.69903, 	0.69889, 0.69876, 0.69863, 0.69851, 0.69839, 0.69828, 0.69817, 0.69807, 0.69797, 0.69787, 0.69778, 0.69769, 0.69761, 0.69753, 0.69745, 0.69737, 0.69730, 0.69723, 0.69716, 0.69710, 0.69703, 0.69697, 0.69691};

int assign_schedule(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{

	// fix this; dummy return to prevent compiler k_t temp;
    task_t temp;
    size_t i,j;
    //uint8_t ub=0;
    uint8_t max = num_tasks*((2 << (1/num_tasks)) -1);

    //Bubble sort the tasks
    for (i =0; i <num_tasks; i++) {
        //ub+=((*tasks)[i].C)/((*tasks)[i].T);
        for(j=0;i<num_tasks;j++) {
            if((*tasks)[j].T > (*tasks)[j+1].T) {
                temp=(*tasks)[j];
                (*tasks)[j]=(*tasks)[j+1];
                (*tasks)[j+1]=temp;
            }
        }
    }
    //ub test
    for(i =0; i<num_tasks; i++) {
	double ub=0.0;
	for(j=0; j<=i;j++) {
		ub+=((*tasks)[j].C)/((*tasks)[i].T);
	}
	ub+=((*tasks)[i].B)/((*tasks)[i].T);

	if(ub >= uRef[i]) return 0;
    }
    return 1;
    //if(ub <=max) return 1;
    //else return 0;
}
