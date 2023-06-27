/*
 * SYSTICK.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Mostafa Anwar
 */

#include "SYSTICK.h"

/*******************defines*******************************/
#define SYSTICK_BASE_ADDRESS  0xE000E010

#define MIN_LOAD_VAL  0x00000001
#define MAX_LOAD_VAL  0x00FFFFFF
/*******************types************************************/
typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}SysTick;

static SysTickHandler SysTickPtr ;

/********************variables*********************************/
static volatile SysTick* const STK = (volatile SysTick* const)SYSTICK_BASE_ADDRESS ;


/********************interface function implementation******************************/
Res_t SYSTICK_SetPeriodMSec(u32 periodMsec)
{
	if ((periodMsec >= MIN_LOAD_VAL) && (periodMsec <= MAX_LOAD_VAL))
	{
		STK->LOAD = 0 ;
		STK->LOAD = (periodMsec*2000) ;
		return RES_OK ;
	}
	else
	{
		return RES_NOK ;
	}
}

void SYSTICK_Start(void)
{
	// AHB = Internal = 16MHZ & CLOCK OF MSTK = AHB / 8 = 16MHZ / 8 = 2MHZ = .5 Micro For Each Count‏
	STK->CTRL= 0x00000003;
}

void SYSTICK_Stop(void)
{
	STK->CTRL = 0 ;
}

Res_t SYSTICK_SetCallBackFunc(SysTickHandler SysTickCBF)
{
	if(SysTickCBF != Null)
	{
		SysTickPtr = SysTickCBF ;
		return RES_OK ;
	}
	else
	{
		return RES_NOK ;
	}
}

void SysTick_Handler(void)
{
	if(SysTickPtr != Null)
	{
		SysTickPtr();
	}
}


