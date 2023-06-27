/*
 * SCHEDULER.h
 *
 *  Created on: Jun 14, 2023
 *      Author: Mostafa Anwar
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/******************includes*******************************/
#include "STD_TYPES.h"


/**********************types**********************************/

typedef struct
{
	void(*runnable)(void);
	u32  PeriodMSec ;
	u32 Priority ;
	char *Name ;
}Runnable_t;


/***********************proto types of interface functions*******************/
/*
    void SCHED_RegisterRunnable(Runnable_t *UserRunnable): Registers a user-defined runnable with the scheduler.

    This function registers a user-defined runnable with the scheduler, allowing it to be scheduled and executed by the scheduler.

    Inputs:
        - UserRunnable: A pointer to the user-defined runnable structure.

    Output: None

    Call in main:
        - SCHED_RegisterRunnable(&myRunnable);
*/
void SCHED_RegisterRunnable(Runnable_t *UserRunnable);

/*
    void SCHED_Init(void): Initializes the scheduler.

    This function initializes the scheduler, preparing it for task scheduling and execution.

    Inputs: None

    Output: None

    Call in main:
        - SCHED_Init();
*/
void SCHED_Init(void);


/*
    void SCHED_Start(void): Starts the scheduler.

    This function starts the scheduler, allowing it to begin scheduling and executing tasks.

    Inputs: None

    Output: None

    Call in main:
        - SCHED_Start();
*/
void SCHED_Start(void);


#endif /* SCHEDULER_H_ */
