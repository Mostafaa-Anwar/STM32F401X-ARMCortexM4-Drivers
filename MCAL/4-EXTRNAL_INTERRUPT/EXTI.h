/*
 * EXTI.h
 *
 *  Created on: Jun 3, 2023
 *      Author: Mostafa Anwar
 */

#ifndef EXTI_H_
#define EXTI_H_

//includes
#include "util.h"
#include "STD_TYPES.h"

// defines
#define EXTI_PORT_A	 0x0     // Define value for EXTI Port A
#define EXTI_PORT_B  0x1     // Define value for EXTI Port B
#define EXTI_PORT_C  0x2     // Define value for EXTI Port C

#define EXTI_PIN_0   0       // Define value for EXTI Pin 0
#define EXTI_PIN_1   1       // Define value for EXTI Pin 1
#define EXTI_PIN_2   2       // Define value for EXTI Pin 2
#define EXTI_PIN_3   3       // Define value for EXTI Pin 3
#define EXTI_PIN_4   4       // Define value for EXTI Pin 4
#define EXTI_PIN_5   5       // Define value for EXTI Pin 5
#define EXTI_PIN_6   6       // Define value for EXTI Pin 6
#define EXTI_PIN_7   7       // Define value for EXTI Pin 7
#define EXTI_PIN_8   8       // Define value for EXTI Pin 8
#define EXTI_PIN_9   9       // Define value for EXTI Pin 9
#define EXTI_PIN_10  10      // Define value for EXTI Pin 10
#define EXTI_PIN_11  11      // Define value for EXTI Pin 11
#define EXTI_PIN_12  12      // Define value for EXTI Pin 12
#define EXTI_PIN_13  13      // Define value for EXTI Pin 13
#define EXTI_PIN_14  14      // Define value for EXTI Pin 14
#define EXTI_PIN_15  15      // Define value for EXTI Pin 15


#define MODE_RISING_EDGE     0     // Define value for rising edge mode
#define MODE_FALLING_EDGE    1     // Define value for falling edge mode
#define MODE_ONCHANGE_EDGE   2     // Define value for any change edge mode

//types ::

//prototypes functions  ::

/*
    EXTI_SetConfig: Function declaration for setting EXTI configuration.
    Inputs:
        - EXTI_PORT_X: The EXTI port to configure (e.g., EXTI_PORT_A, EXTI_PORT_B, etc.).
        - EXTI_PIN_X: The specific pin within the EXTI port to configure (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
        - MODE_X: The mode configuration for EXTI (e.g., MODE_RISING_EDGE, MODE_FALLING_EDGE, etc.).
    Output:
        - Res_X: The result of the configuration operation (e.g., success or failure).
    Call in main:
        - EXTI_SetConfig(EXTI_PORT_A, EXTI_PIN_8, MODE_RISING_EDGE)
*/
Res_t EXTI_SetConfig(u32 EXTI_PORT , u32 EXTI_PIN , u32 MODE);

/*
    EXTI_EnableInter: Function declaration to enable interrupt for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to enable interrupt for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the interrupt enable operation (e.g., success or failure).
    Call in main:
        - EXTI_EnableInter(EXTI_PIN_8)
*/
Res_t EXTI_EnableInter(u32 EXTI_PIN );

/*
    EXTI_DisableInter: Function declaration to disable interrupt for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to disable interrupt for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the interrupt disable operation (e.g., success or failure).
    Call in main:
        - EXTI_DisableInter(EXTI_PIN_8)
*/
Res_t EXTI_DisableInter( u32 EXTI_PIN);

/*
    EXTI_EnableEvent: Function declaration to enable event for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to enable event for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the event enable operation (e.g., success or failure).
    Call in main:
        - EXTI_EnableEvent(EXTI_PIN_8)
*/
Res_t EXTI_EnableEvent(u32 EXTI_PIN);

/*
    EXTI_DisableEvent: Function declaration to disable event for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to disable event for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the event enable operation (e.g., success or failure).
    Call in main:
        - EXTI_DisableEvent(EXTI_PIN_8)
*/
Res_t EXTI_DisableEvent(u32 EXTI_PIN);

/*
    EXTI_SetCallBack: Function declaration to set a callback function for EXTI pin.
    Inputs:
        - ptr: A function pointer to the callback function.
        - EXTI_PIN: The specific pin within the EXTI port to set the callback for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the callback set operation (e.g., success or failure).
    Call in main:
        - EXTI_SetCallBack(Name_func, EXTI_PIN_8)
*/
Res_t EXTI_SetCallBack(void(*ptr)(void) ,u32 EXTI_PIN);

/*
    EXTI_EnableSWInter: Function declaration to enable software interrupt for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to enable software interrupt for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the software interrupt enable operation (e.g., success or failure).
    Call in main:
        - EXTI_EnableSWInter(EXTI_PIN_8)
*/
Res_t EXTI_EnableSWInter(u32 EXTI_PIN);

/*
    EXTI_GetPendingFlag: Function declaration to get the pending flag status for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to check the pending flag for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - u32: The result of the pending flag check operation (e.g., flag status).
    Call in main:
        - EXTI_GetPendingFlag(EXTI_PIN_8)
*/
u32 EXTI_GetPendingFlag(u32 EXTI_PIN);

/*
    EXTI_ClearPendingFlag: Function declaration to clear the pending flag for EXTI pin.
    Inputs:
        - EXTI_PIN: The specific pin within the EXTI port to clear the pending flag for (e.g., EXTI_PIN_8, EXTI_PIN_9, etc.).
    Output:
        - Res_t: The result of the pending flag clear operation (e.g., success or failure).
    Call in main:
        - EXTI_ClearPendingFlag(EXTI_PIN_8)
*/
Res_t EXTI_ClearPendingFlag(u32 EXTI_PIN );

#endif /* EXTI_H_ */
