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

#define BIT_MASK_PORTC_DIRECTION    0xFC000000
#define BIT_MASK_PORTC_VALUE        0x0000E000

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
Res_t GPIOX_InitPin(GPIO_Cfg_t *PinCfg)
{
	u32 temp ;
	u32 temp2 ;
		switch(PinCfg->GPIO)
		{
		case GPIO_A :
			temp = GPIOA->MODER ;
			temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
			temp |= ((PinCfg->MODE) << (PinCfg->PIN)*2 );
			temp2 =temp ;
			(GPIOA->MODER) = temp2;
			break;

		case GPIO_B :
			temp = GPIOB -> MODER ;
			temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
			temp |= (PinCfg->MODE << (PinCfg->PIN)*2 );
			GPIOB -> MODER = temp ;
			break;

		case GPIO_C :

			if ( (PinCfg->PIN == PIN_13) || (PinCfg->PIN == PIN_14) || (PinCfg->PIN == PIN_15) )
			{
				u32 temp = GPIOC -> MODER ;
				temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
				temp |= (PinCfg->MODE << (PinCfg->PIN)*2 );
				GPIOC -> MODER = temp ;
			}
			else { return RES_NOK ; }
			break;

		default:
			return RES_NOK ;
			break;
		}

		if(PinCfg->MODE == MODE_output)
		{
			u32 temp ;
				switch(PinCfg->GPIO)
				{

				case GPIO_A :
					temp = GPIOA -> OTYPER ;
					temp &= ~( CLEAR_1BITS << PinCfg->PIN );
					temp |= (PinCfg->Output_Type << PinCfg->PIN );
					GPIOA -> OTYPER = temp ;
					temp = GPIOA->OSPEEDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->SPEED_Type << PinCfg->PIN*2 );
					GPIOA -> OSPEEDR = temp ;
					return RES_OK ;
					break;

				case GPIO_B :
					temp = GPIOB -> OTYPER ;
					temp &= ~( CLEAR_1BITS << PinCfg->PIN );
					temp |= (PinCfg->Output_Type << PinCfg->PIN );
					GPIOB -> OTYPER = temp ;
					temp = GPIOB->OSPEEDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->SPEED_Type << (PinCfg->PIN)*2 );
					GPIOB -> OSPEEDR = temp ;
					return RES_OK ;
					break;

				case GPIO_C :

					if ( (PinCfg->PIN == PIN_13) || (PinCfg->PIN == PIN_14) || (PinCfg->PIN == PIN_15) )
					{
						temp = GPIOC -> OTYPER ;
						temp &= ~( CLEAR_1BITS << PinCfg->PIN );
						temp |= (PinCfg->Output_Type << PinCfg->PIN );
						GPIOC -> OTYPER = temp ;
						temp = GPIOC->OSPEEDR ;
						temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
						temp |= (PinCfg->SPEED_Type << PinCfg->PIN*2 );
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

		if(PinCfg->MODE == MODE_Alternate_Fun)
		{
			u32 temp ;
				switch(PinCfg->GPIO)
				{

				case GPIO_A :
					temp = GPIOA -> OTYPER ;
					temp &= ~( CLEAR_1BITS << PinCfg->PIN );
					temp |= (PinCfg->Output_Type << PinCfg->PIN );
					GPIOA -> OTYPER = temp ;
					temp = GPIOA->OSPEEDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->SPEED_Type << (PinCfg->PIN)*2 );
					GPIOA -> OSPEEDR = temp ;
					if(PinCfg->PIN <8 )
					{
						temp = GPIOA->AFRL ;
						temp &= ~( CLEAR_4BITS << (PinCfg->PIN)*4 );
						temp |= (PinCfg->AFUN << (PinCfg->PIN)*4 );
						GPIOA -> AFRL = temp ;
					}
					else
					{
						temp = GPIOA->AFRH ;
						temp &= ~( CLEAR_4BITS << ((PinCfg->PIN)-8)*4 );
						temp |= (PinCfg->AFUN << ((PinCfg->PIN)-8)*4 );
						GPIOA -> AFRH = temp ;
					}
					return RES_OK ;
					break;

				case GPIO_B :
					temp = GPIOB -> OTYPER ;
					temp &= ~( CLEAR_1BITS << PinCfg->PIN );
					temp |= (PinCfg->Output_Type << PinCfg->PIN );
					GPIOB -> OTYPER = temp ;
					temp = GPIOB->OSPEEDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->SPEED_Type << (PinCfg->PIN)*2 );
					GPIOB -> OSPEEDR = temp ;

					if(PinCfg->PIN <8 )
					{
						temp = GPIOA->AFRL ;
						temp &= ~( CLEAR_4BITS << (PinCfg->PIN)*4 );
						temp |= (PinCfg->AFUN << (PinCfg->PIN)*4 );
						GPIOA -> AFRL = temp ;
					}
					else
					{
						temp = GPIOA->AFRH ;
						temp &= ~( CLEAR_4BITS << ((PinCfg->PIN)-8)*4 );
						temp |= (PinCfg->AFUN << ((PinCfg->PIN)-8)*4 );
						GPIOA -> AFRH = temp ;
					}
					return RES_OK ;
					break;

				case GPIO_C :
					if ( (PinCfg->PIN == PIN_13) || (PinCfg->PIN == PIN_14) || (PinCfg->PIN == PIN_15) )
					{
						temp = GPIOC -> OTYPER ;
						temp &= ~( CLEAR_1BITS << PinCfg->PIN );
						temp |= (PinCfg->Output_Type << PinCfg->PIN );
						GPIOC -> OTYPER = temp ;
						temp = GPIOC->OSPEEDR ;
						temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
						temp |= (PinCfg->SPEED_Type << (PinCfg->PIN)*2 );
						GPIOC -> OSPEEDR = temp ;
						temp = GPIOA->AFRH ;
						temp &= ~( CLEAR_4BITS << ((PinCfg->PIN)-8)*4 );
						temp |= (PinCfg->AFUN << ((PinCfg->PIN)-8)*4 );
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

		if(PinCfg->MODE == MODE_Input)
		{
			u32 temp ;
				switch(PinCfg->GPIO)
				{
				case GPIO_A :
					temp = GPIOA->PUPDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->PULL_Type << (PinCfg->PIN)*2 );
					GPIOA -> PUPDR = temp ;
					return RES_OK ;
					break;

				case GPIO_B :
					temp = GPIOB->PUPDR ;
					temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
					temp |= (PinCfg->PULL_Type << (PinCfg->PIN)*2 );
					GPIOB -> PUPDR = temp ;
					return RES_OK ;
					break;

				case GPIO_C :
					if ( (PinCfg->PIN == PIN_13) || (PinCfg->PIN == PIN_14) || (PinCfg->PIN == PIN_15) )
					{
						temp = GPIOC->PUPDR ;
						temp &= ~( CLEAR_2BITS << (PinCfg->PIN)*2 );
						temp |= (PinCfg->PULL_Type << (PinCfg->PIN)*2 );
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
		else
		{
			return RES_ARGS ;
		}
}


Res_t GPIOX_GetPinValue (u32 GPIO ,u32 PIN ,u32 *RES)
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


Res_t GPIOX_SetPinValue(u32 GPIO ,u32 PIN ,u32 Value)
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

Res_t GPIOX_TogPin(u32 GPIO ,u32 PIN)
{
	u32 temp ;
	switch(GPIO)
	{

	case GPIO_A :
		temp = GPIOA->ODR ;
		temp ^= (1 << PIN );
		GPIOA->ODR = temp ;

		return RES_OK ;
		break;

	case GPIO_B :
		temp = GPIOB->ODR ;
		temp ^= (1 << PIN );
		GPIOB->ODR = temp ;
		return RES_OK ;
		break;

	case GPIO_C :

		if ( (PIN == PIN_13) || (PIN == PIN_14) || (PIN == PIN_15) )
		{
			temp = GPIOC->ODR ;
			temp ^= (1 << PIN );
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

Res_t GPIOX_SetPortDirection (u32 GPIO, u32 DIRECTION_PORT)
{
	switch(GPIO)
	{

	case GPIO_A :
		GPIOA -> MODER = DIRECTION_PORT ;
		return RES_OK ;
		break;

	case GPIO_B :
		GPIOB -> MODER = DIRECTION_PORT ;
		return RES_OK ;
		break;

	case GPIO_C :
		GPIOC -> MODER = (BIT_MASK_PORTC_DIRECTION & DIRECTION_PORT) ;  //use bit mast because port c is pin 13,14,15
		return RES_OK ;
		break;
	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_SetPortValue (u32 GPIO, u32 PORT_VALUE )
{
	switch(GPIO)
	{

	case GPIO_A :
		GPIOA->ODR = PORT_VALUE ;
		return RES_OK ;
		break;

	case GPIO_B :
		GPIOB->ODR = PORT_VALUE ;
		return RES_OK ;
		break;

	case GPIO_C :
		GPIOC -> ODR = (BIT_MASK_PORTC_VALUE & PORT_VALUE) ;  //use bit mast because port c is pin 13,14,15
		return RES_OK ;
		break;

	default:
		return RES_NOK ;
		break;

	}
}


Res_t GPIOX_ConfigPortOutput (u32 GPIO , u32 OUTPUT_PORT_TYPE  , u32 SPEED_PORT_TYPE)
{
	switch(GPIO)
	{

	case GPIO_A :
		GPIOA -> OTYPER = OUTPUT_PORT_TYPE ;
		GPIOA -> OSPEEDR = SPEED_PORT_TYPE ;
		return RES_OK ;
		break;

	case GPIO_B :
		GPIOB -> OTYPER = OUTPUT_PORT_TYPE ;
		GPIOB -> OSPEEDR = SPEED_PORT_TYPE ;
		return RES_OK ;
		break;

	case GPIO_C :
		GPIOC -> OTYPER = (BIT_MASK_PORTC_VALUE & OUTPUT_PORT_TYPE) ;
		GPIOC -> OSPEEDR = (BIT_MASK_PORTC_DIRECTION & SPEED_PORT_TYPE) ;
		return RES_OK ;

	default:
		return RES_NOK ;
		break;
	}
}


Res_t GPIOX_ConfigPortInput (u32 GPIO  ,u32 PULL_PORT_TYPE)
{
	switch(GPIO)
	{
	case GPIO_A :
		GPIOA -> PUPDR = PULL_PORT_TYPE ;
		return RES_OK ;
		break;

	case GPIO_B :
		GPIOB -> PUPDR = PULL_PORT_TYPE ;
		return RES_OK ;
		break;

	case GPIO_C :
		GPIOC -> PUPDR = (BIT_MASK_PORTC_DIRECTION & PULL_PORT_TYPE) ; ;
		return RES_OK ;
		break;

	default:
		return RES_NOK ;
		break;
	}
}
