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
int assign_schedule(task_t** tasks  /*__attribute__((unused))*/, size_t num_tasks  /*__attribute__((unused))*/)
{/*
	task_t temp;
	size_t i,j;
	uint8_t ub=0;
	uint8_t max = num_tasks*((2 << (1/num_tasks)) -1);
	
	//Bubble sort the tasks
	for (i =0; i <num_tasks; i++) {
		ub+=((*tasks)[i].C)/((*tasks)[i].T);
		for(j=0;i<num_tasks;j++) {
			if((*tasks)[j].T > (*tasks)[j+1].T) {
				temp=(*tasks)[j];
				(*tasks)[j]=(*tasks)[j+1];
				(*tasks)[j+1]=temp_task;
			}
		}
	}
	//ub test 
	if(ub <=max) return 1;
	else */return 0;
	
}
