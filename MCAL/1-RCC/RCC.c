/*
 * RCC.c
 *
 *  Created on: May 21, 2023
 *      Author: Mostafa Anwar
 */

// includes ::
#include "util.h"
#include "RCC.h"

//defines ::

#define RCC_BASE_ADDRESS  0x40023800

/*the start of the bit of every prescaler variable */
#define RCC_PLLCFGR_Q0    24
#define RCC_PLLCFGR_P0    16
#define RCC_PLLCFGR_N0    6
#define RCC_PLLCFGR_M0    0
#define RCC_PLLCFGR_SRC   22

/*the READY BITS AFTER ENABLE THE CLK System  */
#define ClkSys_HSIBIT 1
#define ClkSys_HSEBIT 17
#define ClkSys_PLLBIT 25
/*to check which system selected*/
#define ClkSys_SELECTBIT      2
#define ClkSys_GETMASK        3
#define ClkSys_SELECT_AS_PLL  2

#define SysSelc_clearmask  0xfffffffc

//types ::

typedef struct{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 RCC_SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;
}RCC_t;

//variables ::

static volatile RCC_t * const RCC = (volatile RCC_t*const)RCC_BASE_ADDRESS;

//static functions prototypes
static void PLL_Src_Type(u32 PLL_src) ;

// interface functions implementation ::

/*1-CONTROL REGS :: */

Res_t RCC_EnableClk(u32 ClkSys)
{
	if((ClkSys==ClkSys_HSI)||(ClkSys==ClkSys_HSE)||(ClkSys==ClkSys_PLL))
	{
		RCC->CR |= ClkSys;

		if (ClkSys==ClkSys_HSI)
		{
			while( (((RCC->CR)>>ClkSys_HSIBIT )&ONE_ENABLE)!=1);
			return RES_OK;
		}
		else if (ClkSys==ClkSys_HSE)
		{
			while( (((RCC->CR)>>ClkSys_HSEBIT )&ONE_ENABLE)!=1);
			return RES_OK;
		}
		else if (ClkSys==ClkSys_PLL)
		{
			while( (((RCC->CR)>>ClkSys_PLLBIT )&ONE_ENABLE)!=1);
			return RES_OK;
		}
		else
		{ return RES_ARGS; }
	}
	else
	{  return RES_ARGS; }
}

Res_t RCC_DisableClk(u32 ClkSys)
{
	if((ClkSys==ClkSys_HSI)||(ClkSys==ClkSys_HSE)||(ClkSys==ClkSys_PLL))
	{
		RCC->CR &= (~(ClkSys));
		return RES_OK;
	}
	else
	{
		return RES_ARGS;
	}
}

Res_t RCC_EnableClkPeripheral(u8 BusSys , u32 Peri)
{
	switch(BusSys)
	{
	case BusSys_AHB1:
		RCC->AHB1ENR |=Peri;
		break;
	case BusSys_AHB2:
		RCC->AHB2ENR |=Peri;
		break;
	case BusSys_APB1:
		RCC->APB1ENR |=Peri;
		break;
	case BusSys_APB2:
		RCC->APB2ENR |=Peri;
		break;
	default:
		return RES_ARGS;
		break ;
	}
	return RES_OK ;
}

Res_t RCC_DisableClkPeripheral(u8 BusSys , u32 Peri)
{
	switch(BusSys)
	{
	case BusSys_AHB1:
		RCC->AHB1ENR &= (~Peri);
		break;
	case BusSys_AHB2:
		RCC->AHB2ENR &= (~Peri);
		break;
	case BusSys_APB1:
		RCC->APB1ENR &= (~Peri);
		break;
	case BusSys_APB2:
		RCC->APB2ENR &= (~Peri);
		break;
	default:
		return RES_ARGS;
		break ;
	}
	return RES_OK ;
}

Res_t RCC_ResetClkPeripheral(u8 BusSys , u32 Peri)
{
	switch(BusSys)
	{
	case BusSys_AHB1:
		RCC->AHB1RSTR |=Peri;
		RCC->AHB1RSTR &= (~Peri);
		break;
	case BusSys_AHB2:
		RCC->AHB2RSTR |=Peri;
		RCC->AHB1RSTR &= (~Peri);
		break;
	case BusSys_APB1:
		RCC->APB1RSTR |=Peri;
		RCC->AHB1RSTR &= (~Peri);
		break;
	case BusSys_APB2:
		RCC->APB2RSTR |=Peri;
		RCC->AHB1RSTR &= (~Peri);
		break;
	default:
		return RES_ARGS;
		break ;
	}
	return RES_OK ;
}


/*2-CONfig REGS :: */

Res_t RCC_SelectSystemClk(u32 SysSelc)
{

	if((SysSelc==SysSelc_HSI)||(SysSelc==SysSelc_HSE)||(SysSelc==SysSelc_PLL))
	{
		u32 temp = RCC->CFGR ;

		temp &= SysSelc_clearmask ;
		temp |= SysSelc;

		RCC->CFGR  = temp ;
		return RES_OK;
	}
	else
	{
		return RES_ARGS;
	}
}

Res_t RCC_ConfigPLL(u32 PLL_src ,u32 PLLM , u32 PLLN , u32 PLLP , u32 PLLQ)
{
	if( ((PLL_src==PLL_src_HSI)||(PLL_src==PLL_src_HSE))&&((2<=PLLM)&&(PLLM<=63))&&((192<=PLLN)&&(PLLN<=432))&&((PLLP<=3))&&((2<=PLLQ)&&(PLLQ<=15))   )
	{
		RCC->PLLCFGR=(PLLQ<<RCC_PLLCFGR_Q0)|(PLLP<<RCC_PLLCFGR_P0)|(PLLN<<RCC_PLLCFGR_N0)|(PLLM<<RCC_PLLCFGR_M0)|(PLL_src<<RCC_PLLCFGR_SRC);
		return RES_OK;
	}
	else
	{
		return RES_ARGS ;
	}

}

Res_t RCC_ConfigPrescalerBus(u32 BusPre)
{
	u32 temp = RCC->CFGR ;

	if (((temp>>ClkSys_SELECTBIT)& ClkSys_GETMASK) == ClkSys_SELECT_AS_PLL )
	{
		RCC->CFGR |= BusPre ;
		return RES_OK;
	}
	else
	{ return RES_ARGS ; }

}


Res_t RCC_SwitchBetweenClkSys(u32 OLD_SysClk ,u32 NEW_SysClk)
{
	if ( (OLD_SysClk == OLD_SysClk_HSI) && (NEW_SysClk==NEW_SysClk_HSE) )
	{
		RCC_EnableClk(ClkSys_HSE);
		RCC_SelectSystemClk(SysSelc_HSE);
		RCC_DisableClk(ClkSys_HSI);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_HSE) && (NEW_SysClk==NEW_SysClk_HSI) )
	{
		RCC_EnableClk(ClkSys_HSI);
		RCC_SelectSystemClk(SysSelc_HSI);
		RCC_DisableClk(ClkSys_HSE);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_HSI) && (NEW_SysClk==NEW_SysClk_PLL_src_HSI) )
	{
		PLL_Src_Type(PLL_src_HSI);
		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		return RES_OK;
	}
	else if ( (OLD_SysClk == OLD_SysClk_HSI) && (NEW_SysClk==NEW_SysClk_PLL_src_HSE) )
	{
		RCC_EnableClk(ClkSys_HSE);
		PLL_Src_Type(PLL_src_HSE);
		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		RCC_DisableClk(ClkSys_HSI);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_HSE) && (NEW_SysClk==NEW_SysClk_PLL_src_HSE) )
	{
		PLL_Src_Type(PLL_src_HSE);
		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		return RES_OK;
	}
	else if ( (OLD_SysClk == OLD_SysClk_HSE) && (NEW_SysClk==NEW_SysClk_PLL_src_HSI) )
	{
		RCC_EnableClk(ClkSys_HSI);
		PLL_Src_Type(PLL_src_HSI);
		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		RCC_DisableClk(ClkSys_HSE);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSI) && (NEW_SysClk==NEW_SysClk_HSI) )
	{
		RCC_SelectSystemClk(SysSelc_HSI);
		RCC_DisableClk(ClkSys_PLL);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSI) && (NEW_SysClk==NEW_SysClk_HSE) )
	{
		RCC_EnableClk(ClkSys_HSE);
		RCC_SelectSystemClk(SysSelc_HSE);
		RCC_DisableClk(ClkSys_PLL);
		RCC_DisableClk(ClkSys_HSI);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSE) && (NEW_SysClk==NEW_SysClk_HSI) )
	{
		RCC_EnableClk(ClkSys_HSI);
		RCC_SelectSystemClk(SysSelc_HSI);
		RCC_DisableClk(ClkSys_PLL);
		RCC_DisableClk(ClkSys_HSE);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSE) && (NEW_SysClk==NEW_SysClk_HSE) )
	{
		RCC_SelectSystemClk(SysSelc_HSE);
		RCC_DisableClk(ClkSys_PLL);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSI) && (NEW_SysClk==NEW_SysClk_PLL_src_HSE) )
	{
		RCC_EnableClk(ClkSys_HSE);
		RCC_SelectSystemClk(SysSelc_HSE);
		RCC_DisableClk(ClkSys_PLL);
		PLL_Src_Type(PLL_src_HSE);

		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		RCC_DisableClk(ClkSys_HSI);
		return RES_OK;
	}

	else if ( (OLD_SysClk == OLD_SysClk_PLL_src_HSE) && (NEW_SysClk==NEW_SysClk_PLL_src_HSI) )
	{
		RCC_EnableClk(ClkSys_HSI);
		RCC_SelectSystemClk(SysSelc_HSI);
		RCC_DisableClk(ClkSys_PLL);
		PLL_Src_Type(PLL_src_HSI);

		RCC_EnableClk(ClkSys_PLL);
		RCC_SelectSystemClk(SysSelc_PLL);
		RCC_DisableClk(ClkSys_HSE);
		return RES_OK;
	}

	else { return RES_ARGS ; }
}

//static functions implementation ::

static void PLL_Src_Type(u32 PLL_src)
{
	RCC->PLLCFGR |= (PLL_src<<RCC_PLLCFGR_SRC) ;
}

