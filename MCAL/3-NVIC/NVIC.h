/*
 * NVIC.h
 *
 *  Created on: May 27, 2023
 *      Author: Mostafa Anwar
 */

#ifndef NVIC_H_
#define NVIC_H_

//includes
#include "STD_TYPES.h"
#include "util.h"

//defines
/*Select number of group and subgroup */
#define NumGroup_16GRP_0SUB  0x05FA0000
#define NumGroup_8GRP_2SUB   0x05FA0400
#define NumGroup_4GRP_4SUB   0x05FA0500
#define NumGroup_2GRP_8SUB   0x05FA0600
#define NumGroup_0GRP_16SUB  0x05FA0700



//types

//prototypes functions

/*
    NVIC_SCB_SelectNumGroupAndSub : to Select number of group and subgroup
    inputs: options from [NumGroup_X]
    output: options from [Res_X]
    call in main: NVIC_SCB_SelectNumGroupAndSub(NumGroup_16GRP_0SUB)
*/
Res_t MNVIC_SCB_SelectNumGroupAndSub(u32 NumGroup);

/*
    NVIC_EnableIntPeri : to Select the position of INTR from Vector table for STM32F401 without clear the old tasks
    inputs: options from [INTR_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_EnableIntPeri(5)
*/
Res_t MNVIC_EnableIntPeriWithOldTasks(u32 INTR_ID);

/*
    NVIC_EnableIntPeri : to Select the position of INTR from Vector table for STM32F401 with clear the old tasks
    inputs: options from [INTR_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_EnableIntPeri(5)
*/
Res_t MNVIC_EnableIntPeri(u32 INTR_ID);

/*
    NVIC_DisableIntPeri : to Select the position of INTR from Vector table for STM32F401
    inputs: options from [INTR_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_DisableIntPeri(5)
*/
Res_t MNVIC_DisableIntPeri(u32 INTR_ID);

/*
    NVIC_EnablePendingPeri : to Select the pending of INTR from Vector table for STM32F401
    inputs: options from [INTR_PENDING_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_EnableIntPeri(5)
*/
Res_t MNVIC_EnablePendingPeri(u32 INTR_PENDING_ID);

/*
    NVIC_DisablePendingPeri : to Select the pending of INTR from Vector table for STM32F401
    inputs: options from [INTR_PENDING_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_DisablePendingPeri(5)
*/
Res_t MNVIC_DisablePendingPeri(u32 INTR_PENDING_ID);

/*
    NVIC_GetActiveFlag : to read the active flag of INTR from Vector table for STM32F401
    inputs: options from [INTR_ACTIVE_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_GetActiveFlag(5)
*/
Res_t MNVIC_GetActiveFlag(u32 INTR_ACTIVE_ID , u32 *Result);

/*
    NVIC_SetSWPriority : to read the active flag of INTR from Vector table for STM32F401
    Note:must use the NVIC_SCB_SelectNumGroupAndSub function before it
    inputs: options from [INTR_ID ,Priority ]
    range :0<=INTR_ID<=240 & 0<=priority<=15
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_SetSWPriority(5 , 0x10)
*/
Res_t MNVIC_SetSWPriority(u32 INTR_ID , u32 Priority);

/*
    NVIC_SWTriggerINTR : to trigger the INTR from Vector table for STM32F401
    inputs: options from [INTR_ID]
    range :0<=INTR_ID<=84
    0 for WWDG
    1 for EXTI16
        .
        .
        .
    84 for SPI4
    output: options from [Res_X]
    call in main: NVIC_SWTriggerINTR(5)
*/
Res_t MNVIC_SWTriggerINTR(u32 INTR_ID);



#endif /* NVIC_H_ */
