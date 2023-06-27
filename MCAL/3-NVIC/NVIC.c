/*
 * NVIC.c
 *
 *  Created on: May 27, 2023
 *      Author: Mostafa Anwar
 */
//includes

#include "NVIC.h"
//defines

#define  SCB_AIRCR               *((volatile u32*)0xE000ED0C)
#define  SCB_AIRCR_VECTKEY       0x05FA
#define  NVIC_BASE_ADDRESS       0xE000E100
#define  LEN_REG                 32

#define  ONE_FORSETBIT           1
#define  ONE_FORGETBIT           1

#define SHIFT_TOLAST_4MSB        4
//types

typedef struct
{
	u32 ISER[8];
	u32 RESERVES1[24];
	u32 ICER[8];
	u32 RESERVES2[24];
	u32 ISPR[8];
	u32 RESERVES3[24];
	u32 ICPR[8];
	u32 RESERVES4[24];
	u32 IAPR[8];
	u32 RESERVES5[56];
	u8  IPR[240];
	u32 RESERVES6[580];
	u32 STIR;

}NVIC_t;

//variables

static volatile NVIC_t* const NVIC = (volatile NVIC_t* const)NVIC_BASE_ADDRESS ;

//static functions prototypes

//interface functions implementations

Res_t MNVIC_SCB_SelectNumGroupAndSub(u32 NumGroup)
{
	if((NumGroup==NumGroup_16GRP_0SUB)||(NumGroup==NumGroup_8GRP_2SUB)||(NumGroup==NumGroup_4GRP_4SUB)||(NumGroup==NumGroup_2GRP_8SUB)||(NumGroup==NumGroup_0GRP_16SUB))
	{
		SCB_AIRCR=NumGroup ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}


Res_t MNVIC_EnableIntPeri(u32 INTR_ID)
{
	if(INTR_ID<=84)
	{
		MNVIC_DisablePendingPeri(INTR_ID);
		NVIC->ISER[INTR_ID/LEN_REG] = (ONE_FORSETBIT<<(INTR_ID % LEN_REG)) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t MNVIC_EnableIntPeriWithOldTasks(u32 INTR_ID)
{
	if( INTR_ID<=84)
	{
		NVIC->ISER[INTR_ID/LEN_REG] = (ONE_FORSETBIT<<(INTR_ID % LEN_REG)) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t MNVIC_DisableIntPeri(u32 INTR_ID)
{

	if( INTR_ID<=84)
	{
		NVIC->ICER[INTR_ID/LEN_REG] = (ONE_FORSETBIT<<(INTR_ID % LEN_REG)) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}



Res_t MNVIC_EnablePendingPeri(u32 INTR_PENDING_ID)
{
	if( INTR_PENDING_ID<=84)
	{
		NVIC->ISPR[INTR_PENDING_ID/LEN_REG] = (ONE_FORSETBIT<<(INTR_PENDING_ID % LEN_REG)) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t MNVIC_DisablePendingPeri(u32 INTR_PENDING_ID)
{
	if( INTR_PENDING_ID<=84)
	{
		NVIC->ICPR[INTR_PENDING_ID/LEN_REG] = (ONE_FORSETBIT<<(INTR_PENDING_ID % LEN_REG)) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}



Res_t MNVIC_GetActiveFlag(u32 INTR_ACTIVE_ID , u32 *Result)
{
	if( INTR_ACTIVE_ID<=84)
	{
		*Result = ((NVIC->IAPR[INTR_ACTIVE_ID/LEN_REG]>>(INTR_ACTIVE_ID % LEN_REG))&ONE_FORGETBIT) ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t MNVIC_SetSWPriority(u32 INTR_ID , u32 Priority)
{
	if((INTR_ID<=240)&&(Priority<=15))
	{
		NVIC->IPR[INTR_ID] =(Priority<<SHIFT_TOLAST_4MSB);
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}

}

Res_t MNVIC_SWTriggerINTR(u32 INTR_ID)
{
	if(INTR_ID<=240)
	{
		NVIC->STIR = INTR_ID ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}


//static functions implementations
