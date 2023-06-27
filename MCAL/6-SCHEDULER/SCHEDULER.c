/*
 * SCHEDULER.c
 *
 *  Created on: Jun 14, 2023
 *      Author: Mostafa Anwar
 */
/********************************includes*******************************/
#include "SCHEDULER.h"
#include "SYSTICK.h"
#include "SCHEDULER_config.h"


/********************************defines********************************/
#define MAX_RUNNABLES   10

/*****************************variables********************************/
static u32 size ;
static Runnable_t *runnables[MAX_RUNNABLES] ;
static u32 IsReady = 0 ;

/****************proto types of static function *************************/
static void Scheduler(void);

static void SchedReady(void);

/****************implementation of interface functions******************/

void SCHED_Init(void)
{
	SYSTICK_SetPeriodMSec(TICK_TIME) ;
	SYSTICK_SetCallBackFunc(SchedReady);
}

void SCHED_Start(void)
{
	SYSTICK_Start();

	while(1)
	{
		if(IsReady == 1)
		{
			IsReady =0 ;
			Scheduler();
		}
	}
}



void SCHED_RegisterRunnable(Runnable_t *UserRunnable)
{
	if(UserRunnable != Null)
	{
		if(size < MAX_RUNNABLES)
		{
			runnables[UserRunnable->Priority] = UserRunnable ;
			size++ ;
		}
	}
}

/****************implementation of static functions******************/
static void Scheduler(void)
{
	static u32 TimeMs ;
	u32 index ;

	if(TimeMs)
	{
		for(index=0 ; index < MAX_RUNNABLES ; index++)
		{
			if(runnables[index] != Null)
			{
				if( (TimeMs % runnables[index]->PeriodMSec) == 0 )
				{
					runnables[index]->runnable();
				}
			}
		}
	}
	TimeMs += TICK_TIME ;
}

static void SchedReady(void)
{
	IsReady =1 ;
}
