/*
 * EXTI.c
 *
 *  Created on: Jun 3, 2023
 *      Author: Mostafa Anwar
 */
#include "util.h"
#include "EXTI.h"



#define LEN4_TOSELECTPORT  4    // Length of 4 bits to select a port
#define SHIFT_FOR_4BIT     4    // Shift value for 4-bit selection

#define SYSCFG_BASE_ADDRESS   0x40013808   // Base address for SYSCFG peripheral
#define EXTI_BASE_ADDRESS     0x40013C00   // Base address for EXTI peripheral


typedef struct{
	u32 EXTICR[4] ;

}SYSCFG_t;


typedef struct{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;

}EXTI_t;

//variables ::

static volatile SYSCFG_t * const SYSCFG = (volatile SYSCFG_t * const)SYSCFG_BASE_ADDRESS;
static volatile EXTI_t   * const EXTI   = (volatile EXTI_t   * const)EXTI_BASE_ADDRESS;

static void (*EXTI_CallBack[16] ) (void) = {Null} ;



Res_t EXTI_SetConfig(u32 EXTI_PORT , u32 EXTI_PIN , u32 Mode)
{
	if(EXTI_PIN<=EXTI_PIN_15)
	{
		SYSCFG->EXTICR[EXTI_PIN/ LEN4_TOSELECTPORT ] &= ~(EXTI_PIN_15 << ((EXTI_PIN % LEN4_TOSELECTPORT )* SHIFT_FOR_4BIT )) ;
		SYSCFG->EXTICR[EXTI_PIN/ LEN4_TOSELECTPORT ] |= (EXTI_PORT << ((EXTI_PIN % LEN4_TOSELECTPORT )* SHIFT_FOR_4BIT )) ;


		switch (Mode)
		{
		case MODE_RISING_EDGE :
			EXTI->RTSR |= ( ONE_ENABLE << EXTI_PIN)  ;
			EXTI->FTSR &= ~( ONE_ENABLE << EXTI_PIN)  ;
			return RES_OK ;
			break ;

		case MODE_FALLING_EDGE :
			EXTI->FTSR |= ( ONE_ENABLE << EXTI_PIN)  ;
			EXTI->RTSR &= ~(ONE_ENABLE << EXTI_PIN)  ;
			return RES_OK ;
			break ;

		case MODE_ONCHANGE_EDGE :
			EXTI->RTSR |= ( ONE_ENABLE << EXTI_PIN)  ;
			EXTI->FTSR |= ( ONE_ENABLE << EXTI_PIN)  ;
			return RES_OK ;
			break ;
		default:
			return RES_ARGS ;
			break ;

		}
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_EnableInter(u32 EXTI_PIN )
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->IMR |= ( ONE_ENABLE << EXTI_PIN) ;   //ENABLE INTER
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_DisableInter( u32 EXTI_PIN)
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->IMR &= ~( ONE_ENABLE << EXTI_PIN) ;   //DISABLE INTER
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_EnableEvent(u32 EXTI_PIN)
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->EMR = ( ONE_ENABLE << EXTI_PIN) ;   //ENABLE EVEN
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_DisableEvent(u32 EXTI_PIN)
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->EMR &= ~( ONE_ENABLE << EXTI_PIN) ;   //DISABLE EVEN
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_EnableSWInter(u32 EXTI_PIN)
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->SWIER = (ONE_ENABLE << EXTI_PIN) ;   //ENABLE SoftWare Inter
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

u32 EXTI_GetPendingFlag(u32 EXTI_PIN)
{
	u32 Res ;
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		Res = ( EXTI->PR >> EXTI_PIN) & ONE_ENABLE ;  //Get Pending Flag
		return Res ;
	}
	else
	{
		return RES_ERROR ;
	}
}

Res_t EXTI_ClearPendingFlag(u32 EXTI_PIN )
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{
		EXTI->PR |= (1 << EXTI_PIN)  ;  //  Clear Pending Flag
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}

Res_t EXTI_SetCallBack(void(*ptr)(void) ,u32 EXTI_PIN)
{
	if(EXTI_PIN<= EXTI_PIN_15)
	{

		EXTI_CallBack[EXTI_PIN] = ptr ;
		return RES_OK ;
	}
	else
	{
		return RES_ARGS ;
	}
}



void EXTI0_IRQHandler(void)
{
	if(EXTI_CallBack[0] != Null )
	{
		EXTI_CallBack[0]() ;
		EXTI_ClearPendingFlag(EXTI_PIN_0);   //clear INTER
	}

}


void EXTI1_IRQHandler(void)
{
	if(EXTI_CallBack[1] != Null )
	{
		EXTI_CallBack[1]() ;
		EXTI_ClearPendingFlag(EXTI_PIN_1);   //clear INTER
	}

}


void EXTI2_IRQHandler(void)
{
	if(EXTI_CallBack[2] != Null )
	{
		EXTI_CallBack[2]() ;
		EXTI_ClearPendingFlag(EXTI_PIN_2);   //clear INTER
	}

}


void EXTI3_IRQHandler(void)
{
	if(EXTI_CallBack[3] != Null )
	{
		EXTI_CallBack[3]() ;
		EXTI_ClearPendingFlag(EXTI_PIN_3);   //clear INTER
	}

}


void EXTI4_IRQHandler(void)
{
	if(EXTI_CallBack[4] != Null )
	{
		EXTI_CallBack[4]() ;
		EXTI_ClearPendingFlag(EXTI_PIN_4);   //clear INTER
	}

}


void EXTI9_5_IRQHandler(void)
{

	if(EXTI_GetPendingFlag(EXTI_PIN_5) == ONE_ENABLE)
	{
		if(EXTI_CallBack[5] != Null )
		{
			EXTI_CallBack[5]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_5);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_6) == ONE_ENABLE)
	{
		if(EXTI_CallBack[6] != Null )
		{
			EXTI_CallBack[6]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_6);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_7) == ONE_ENABLE)
	{
		if(EXTI_CallBack[7] != Null )
		{
			EXTI_CallBack[7]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_7);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_8) == ONE_ENABLE)
	{
		if(EXTI_CallBack[8] != Null )
		{
			EXTI_CallBack[8]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_8);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_9) == ONE_ENABLE)
	{
		if(EXTI_CallBack[9] != Null )
		{
			EXTI_CallBack[9]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_9);  //clear INTER
		}
	}

}


void EXTI15_10_IRQHandler(void)
{

	if(EXTI_GetPendingFlag(EXTI_PIN_10) == ONE_ENABLE)
	{
		if(EXTI_CallBack[10] != Null )
		{
			EXTI_CallBack[10]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_10);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_11) == ONE_ENABLE)
	{
		if(EXTI_CallBack[11] != Null )
		{
			EXTI_CallBack[11]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_11);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_12) == ONE_ENABLE)
	{
		if(EXTI_CallBack[12] != Null )
		{
			EXTI_CallBack[12]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_12);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_13) == ONE_ENABLE)
	{
		if(EXTI_CallBack[13] != Null )
		{
			EXTI_CallBack[13]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_13);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_14) == ONE_ENABLE)
	{
		if(EXTI_CallBack[14] != Null )
		{
			EXTI_CallBack[14]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_14);  //clear INTER
		}
	}

	if(EXTI_GetPendingFlag(EXTI_PIN_15) == ONE_ENABLE)
	{
		if(EXTI_CallBack[15] != Null )
		{
			EXTI_CallBack[15]() ;
			EXTI_ClearPendingFlag(EXTI_PIN_15);  //clear INTER
		}
	}

}
