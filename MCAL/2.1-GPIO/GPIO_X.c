/*
 * GPIO_X.c
 *
 *  Created on: May 26, 2023
 *      Author: Mostafa Anwar
 */


// includes ::
#include "GPIO_X.h"

//defines ::

#define GPIOA_BASE_ADDRESS  0x40020000
#define GPIOB_BASE_ADDRESS  0x40020400
#define GPIOC_BASE_ADDRESS  0x40020800

#define CLEAR_1BITS  1
#define CLEAR_2BITS  3
#define CLEAR_4BITS  15

//types ::
typedef struct{
	u32 MODER;
	u32 OTYPER;
	u32 OSPEEDR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIO_t;

//variables ::

static volatile GPIO_t * const GPIOA = (volatile GPIO_t*const)GPIOA_BASE_ADDRESS;
static volatile GPIO_t * const GPIOB = (volatile GPIO_t*const)GPIOB_BASE_ADDRESS;
static volatile GPIO_t * const GPIOC = (volatile GPIO_t*const)GPIOC_BASE_ADDRESS;


//static functions prototypes ::


// interface functions implementation ::

/*1-CONTROL REGS :: */

Res_t GPIOX_PIN_Direction(u32 GPIO ,u32 PIN ,u32 MODE )
{
	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :
		temp = GPIOA->MODER ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (MODE << PIN*2 );
		GPIOA -> MODER = temp ;
		return RES_OK ;
		break;

	case GPIO_B :
		temp = GPIOB -> MODER ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (MODE << PIN*2 );
		GPIOB -> MODER = temp ;
		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			u32 temp = GPIOC -> MODER ;
			temp &= ~( CLEAR_2BITS << PIN*2 );
			temp |= (MODE << PIN*2 );
			GPIOC -> MODER = temp ;
			return RES_OK ;
		}
		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_PIN_OUTPUTConfg(u32 GPIO , u32 PIN , u32 Output_Type  ,u32 SPEED_Type )
{
	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :
		temp = GPIOA -> OTYPER ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Output_Type << PIN );
		GPIOA -> OTYPER = temp ;

		temp = GPIOA->OSPEEDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (SPEED_Type << PIN*2 );
		GPIOA -> OSPEEDR = temp ;


		return RES_OK ;
		break;

	case GPIO_B :
		temp = GPIOB -> OTYPER ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Output_Type << PIN );
		GPIOB -> OTYPER = temp ;

		temp = GPIOB->OSPEEDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (SPEED_Type << PIN*2 );
		GPIOB -> OSPEEDR = temp ;


		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			temp = GPIOC -> OTYPER ;
			temp &= ~( CLEAR_1BITS << PIN );
			temp |= (Output_Type << PIN );
			GPIOC -> OTYPER = temp ;

			temp = GPIOC->OSPEEDR ;
			temp &= ~( CLEAR_2BITS << PIN*2 );
			temp |= (SPEED_Type << PIN*2 );
			GPIOC -> OSPEEDR = temp ;

			return RES_OK ;
		}
		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_PIN_AlternatefunctionConfg(u32 GPIO , u32 PIN , u32 Output_Type  ,u32 SPEED_Type , u32 AFUN)
{

	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :
		temp = GPIOA -> OTYPER ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Output_Type << PIN );
		GPIOA -> OTYPER = temp ;

		temp = GPIOA->OSPEEDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (SPEED_Type << PIN*2 );
		GPIOA -> OSPEEDR = temp ;

		if(PIN <8 )
		{
			temp = GPIOA->AFRL ;
			temp &= ~( CLEAR_4BITS << PIN*4 );
			temp |= (AFUN << PIN*4 );
			GPIOA -> AFRL = temp ;
		}
		else
		{
			temp = GPIOA->AFRH ;
			temp &= ~( CLEAR_4BITS << (PIN-8)*4 );
			temp |= (AFUN << (PIN-8)*4 );
			GPIOA -> AFRH = temp ;
		}


		return RES_OK ;
		break;

	case GPIO_B :
		temp = GPIOB -> OTYPER ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Output_Type << PIN );
		GPIOB -> OTYPER = temp ;

		temp = GPIOB->OSPEEDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (SPEED_Type << PIN*2 );
		GPIOB -> OSPEEDR = temp ;

		if(PIN <8 )
		{
			temp = GPIOA->AFRL ;
			temp &= ~( CLEAR_4BITS << PIN*4 );
			temp |= (AFUN << PIN*4 );
			GPIOA -> AFRL = temp ;
		}
		else
		{
			temp = GPIOA->AFRH ;
			temp &= ~( CLEAR_4BITS << (PIN-8)*4 );
			temp |= (AFUN << (PIN-8)*4 );
			GPIOA -> AFRH = temp ;
		}


		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			temp = GPIOC -> OTYPER ;
			temp &= ~( CLEAR_1BITS << PIN );
			temp |= (Output_Type << PIN );
			GPIOC -> OTYPER = temp ;

			temp = GPIOC->OSPEEDR ;
			temp &= ~( CLEAR_2BITS << PIN*2 );
			temp |= (SPEED_Type << PIN*2 );
			GPIOC -> OSPEEDR = temp ;

			temp = GPIOA->AFRH ;
			temp &= ~( CLEAR_4BITS << (PIN-8)*4 );
			temp |= (AFUN << (PIN-8)*4 );
			GPIOA -> AFRH = temp ;

			return RES_OK ;
		}
		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_PIN_INPUTConfg(u32 GPIO , u32 PIN ,u32 PULL_Type  )
{
	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :

		temp = GPIOA->PUPDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (PULL_Type << PIN*2 );
		GPIOA -> PUPDR = temp ;

		return RES_OK ;
		break;

	case GPIO_B :

		temp = GPIOB->PUPDR ;
		temp &= ~( CLEAR_2BITS << PIN*2 );
		temp |= (PULL_Type << PIN*2 );
		GPIOB -> PUPDR = temp ;

		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{

			temp = GPIOC->PUPDR ;
			temp &= ~( CLEAR_2BITS << PIN*2 );
			temp |= (PULL_Type << PIN*2 );
			GPIOC -> PUPDR = temp ;

			return RES_OK ;
		}
		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_GetPIN_Value(u32 GPIO ,u32 PIN ,u32 *RES)
{
	switch(GPIO)
	{

	case GPIO_A :
		*RES = ( ( (GPIOA->IDR)  >> PIN ) & BIT0_MASK );
		return RES_OK ;
		break;

	case GPIO_B :

		*RES = ( ( (GPIOB->IDR)  >> PIN ) & BIT0_MASK );
		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			*RES = ( ( (GPIOC->IDR)  >> PIN ) & BIT0_MASK );
			return RES_OK ;
		}

		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_SetPIN_Value(u32 GPIO ,u32 PIN ,u32 Value)
{
	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :
		temp = GPIOA->ODR ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Value << PIN );
		GPIOA->ODR = temp ;

		return RES_OK ;
		break;

	case GPIO_B :
		temp = GPIOB->ODR ;
		temp &= ~( CLEAR_1BITS << PIN );
		temp |= (Value << PIN );
		GPIOB->ODR = temp ;
		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			temp = GPIOC->ODR ;
			temp &= ~( CLEAR_1BITS << PIN );
			temp |= (Value << PIN );
			GPIOC->ODR = temp ;
			return RES_OK ;
		}

		else { return RES_NOK ; }
		break;

	default:
		return RES_NOK ;
		break;

	}
}
