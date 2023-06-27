/*
 * SYSTICK.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Mostafa Anwar
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
/*****************includes**************************/
#include "STD_TYPES.h"
#include "util.h"


/*************************types*********************/
typedef  void(*SysTickHandler)(void)  ;


/***************function proto types ***********************/
/*
    Res_t SYSTICK_SetPeriodMSec(u32 periodMsec): Sets the period of the SysTick timer in milliseconds.

    Input:
        - periodMsec: The desired period of the SysTick timer in milliseconds.

    Output:
        - Res_t: The result of the operation (e.g., success or failure).
*/
Res_t SYSTICK_SetPeriodMSec(u32 periodMsec);

/*
    void SYSTICK_Start(void): Starts the SysTick timer.

    This function enables the SysTick timer to start counting.

    No inputs.

    No output.
*/
void SYSTICK_Start(void);

/*
    void SYSTICK_Stop(void): Stops the SysTick timer.

    This function stops the SysTick timer from counting.

    No inputs.

    No output.
*/
void SYSTICK_Stop(void);

/*
    Res_t SYSTICK_SetCallBackFunc(SysTickHandler SysTickCBF): Sets the callback function for the SysTick timer.

    This function sets the callback function to be executed when the SysTick timer interrupt occurs.

    Inputs:
        - SysTickCBF: A function pointer to the callback function.

    Output:
        - Res_t: The result of the operation (e.g., success or failure).

    Returns:
        - RES_OK if the callback function is set successfully.
        - RES_NOK if an error occurs.

    Call in main:
        - SYSTICK_SetCallBackFunc(mySysTickCallback);
*/
Res_t SYSTICK_SetCallBackFunc(SysTickHandler SysTickCBF);


#endif /* SYSTICK_H_ */
