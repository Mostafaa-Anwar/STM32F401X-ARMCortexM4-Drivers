/*
 * RCC.h
 *
 *  Created on: May 21, 2023
 *  Author: Mostafa Anwar
 */

#ifndef RCC_H_
#define RCC_H_

// includes ::

#include "STD_TYPES.h"
#include "util.h"

//defines ::

#define ClkSys_HSI  BIT0_MASK
#define ClkSys_HSE  BIT16_MASK
#define ClkSys_PLL  BIT24_MASK

#define SysSelc_HSI  0
#define SysSelc_HSE  1
#define SysSelc_PLL  2

#define PLL_src_HSI  0
#define PLL_src_HSE  1

#define OLD_SysClk_HSI           0
#define OLD_SysClk_HSE           1
#define OLD_SysClk_PLL_src_HSI   2
#define OLD_SysClk_PLL_src_HSE   3

#define NEW_SysClk_HSI           0
#define NEW_SysClk_HSE           1
#define NEW_SysClk_PLL_src_HSI   2
#define NEW_SysClk_PLL_src_HSE   3



#define BusSys_AHB1  0
#define BusSys_AHB2  1
#define BusSys_APB1  2
#define BusSys_APB2  3

#define BusPre_AHB_2   0x00000080
#define BusPre_AHB_4   0x00000090
#define BusPre_AHB_8   0x000000A0
#define BusPre_AHB_16  0x000000B0

#define BusPre_APB1_2   0x00001000
#define BusPre_APB1_4   0x00001400
#define BusPre_APB1_8   0x00001800
#define BusPre_APB1_16  0x00001C00

#define BusPre_APB2_2   0x00008000
#define BusPre_APB2_4   0x0000A000
#define BusPre_APB2_8   0x0000C000
#define BusPre_APB2_16  0x0000E000

#define  Peri_AHB1_GPIOA      BIT0_MASK
#define  Peri_AHB1_GPIOB      BIT1_MASK
#define  Peri_AHB1_GPIOC      BIT2_MASK
#define  Peri_AHB1_GPIOD      BIT3_MASK
#define  Peri_AHB1_GPIOE      BIT4_MASK
#define  Peri_AHB1_GPIOH      BIT7_MASK
#define  Peri_AHB1_CRC        BIT12_MASK
#define  Peri_AHB1_DMA1       BIT21_MASK
#define  Peri_AHB1_DMA2       BIT22_MASK

#define  Peri_AHB2_OTGFS      BIT7_MASK

#define  Peri_APB1_TIM2       BIT0_MASK
#define  Peri_APB1_TIM3       BIT1_MASK
#define  Peri_APB1_TIM4       BIT2_MASK
#define  Peri_APB1_TIM5       BIT3_MASK
#define  Peri_APB1_WWDG       BIT11_MASK
#define  Peri_APB1_SPI2       BIT14_MASK
#define  Peri_APB1_SPI3       BIT15_MASK
#define  Peri_APB1_USART2     BIT17_MASK
#define  Peri_APB1_I2C1       BIT21_MASK
#define  Peri_APB1_I2C2       BIT22_MASK
#define  Peri_APB1_I2C3       BIT23_MASK
#define  Peri_APB1_PWR        BIT28_MASK

#define  Peri_APB2_TIM1       BIT0_MASK
#define  Peri_APB2_USART1     BIT4_MASK
#define  Peri_APB2_USART6     BIT5_MASK
#define  Peri_APB2_ADC1       BIT8_MASK
#define  Peri_APB2_SDIO       BIT11_MASK
#define  Peri_APB2_SPI1       BIT12_MASK
#define  Peri_APB2_SPI4       BIT13_MASK
#define  Peri_APB2_SYSCFG     BIT14_MASK
#define  Peri_APB2_TIM9       BIT16_MASK
#define  Peri_APB2_TIM10      BIT17_MASK
#define  Peri_APB2_TIM11      BIT18_MASK

//types ::




//prototypes of functions ::

/*
    RCC_EnableClk : to enable the system clock
    inputs: options from [ClkSys_X]
    output: options from [Res_X]
    call in main: RCC_EnableClk(ClkSys_HSE)
*/
Res_t RCC_EnableClk(u32 ClkSys);

/*
    RCC_DisableClk : to disable the system clock
    inputs: options from [ClkSys_X]
    output: options from [Res_X]
    call in main: RCC_DisableClk(ClkSys_HSE)
*/
Res_t RCC_DisableClk(u32 ClkSys);

/*
    RCC_SelectSystemClk : to select the system clock use after using RCC_EnableClk
    inputs: options from [SysSelc_X]
    output: options from [Res_X]
    call in main: RCC_SelectSystemClk(SysSelc_HSE)
*/
Res_t RCC_SelectSystemClk(u32 SysSelc);

/*
    RCC_ConfigPLL : to config the PLL(HSI,HSE) clk
    limitation: to use it disable PLL first And enable (HSE or HSI) to choose one of them as PLL_src
    inputs: options from [PLL_src_X]
    output: options from [Res_X]
    ranges:
    1- PLLM with 2 <= PLLM <= 63
    2- PLLN with 192 ≤ PLLN ≤ 432
    3- PLLP = 0 for divide by 2 &
    	      1 for divide by 4 &
    	      2 for divide by 6 &
    	      3 for divide by 8 &
    4- PLLQ with 2 ≤PLLQ ≤15
    call in main: RCC_ConfigPLL(PLL_src_HSE,2,192,8,15)
*/
Res_t RCC_ConfigPLL(u32 PLL_src ,u32 PLLM , u32 PLLN , u32 PLLP , u32 PLLQ);

/*
    RCC_SelectSystemBus : to config the system prescaler bus
    limitation: the option difference from bus to another
    inputs: options from [BusPre_X]
    output: no return(void)
    call in main: RCC_ConfigSystemBus(BusPre_AHB_2)
*/
Res_t RCC_ConfigPrescalerBus(u32 BusPre);

/*
    RCC_EnableClkPeripheral : to enable the clock peripheral
    inputs: options from [Peri_X] & [BusSys_X]
    output: options from [Res_X]
    call in main: RCC_EnableClkPeripheral(BusSys_APB1,Peri_APB1_TIM2)
*/
Res_t RCC_EnableClkPeripheral(u8 BusSys , u32 Peri);

/*
    RCC_EnableClkPeripheral : to disable the clock peripheral
    inputs: options from [Peri_X] & [BusSys_X]
    output: options from [Res_X]
    call in main: RCC_EnableClkPeripheral(BusSys_APB1,Peri_APB1_TIM2)
*/
Res_t RCC_DisableClkPeripheral(u8 BusSys , u32 Peri);

/*
    RCC_ResetClkPeripheral : to reset the clock peripheral
    inputs: options from [Peri_X] & [BusSys_X]
    output: options from [Res_X]
    call in main: RCC_EnableClkPeripheral(BusSys_APB1,Peri_APB1_TIM2)
*/
Res_t RCC_ResetClkPeripheral(u8 BusSys , u32 Peri);

/*
    RCC_SwitchBetweenClkSys : to switch from system clock to another
    inputs: options from [OLD_SysClk_X] & [NEW_SysClk_X]
    output: options from [Res_X]
    call in main: RCC_SwitchBetweenClkSys( OLD_SysClk_HSE, NEW_SysClk_HSI)
*/
Res_t RCC_SwitchBetweenClkSys(u32 OLD_SysClk ,u32 NEW_SysClk);

#endif /* RCC_H_ */
