/*
 * GPIO_X.h
 *
 *  Created on: May 26, 2023
 *      Author: Mostafa Anwar
 */

#ifndef GPIO_X_H_
#define GPIO_X_H_

// includes ::

#include "STD_TYPES.h"
#include "util.h"

//defines ::

#define GPIO_A   0
#define GPIO_B   1
#define GPIO_C   2

#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7
#define PIN_8   8
#define PIN_9   9
#define PIN_10  10
#define PIN_11  11
#define PIN_12  12
#define PIN_13  13
#define PIN_14  14
#define PIN_15  15


#define MODE_Input             0
#define MODE_output            1
#define MODE_Alternate_Fun     2
#define MODE_Analog            3


/*OUTPUT CONFG*/

#define Output_Type_pushpull    0
#define Output_Type_Opendrain   1

#define SPEED_Type_Low      0
#define SPEED_Type_Medium   1
#define SPEED_Type_High     2
#define SPEED_Type_VerHigh  3

#define PULL_Type_Floating   0
#define PULL_Type_Pullup     1
#define PULL_Type_Pulldown   2

#define Value_Low    0
#define Value_High   1



#define AFUN_0   0
#define AFUN_1   1
#define AFUN_2   2
#define AFUN_3   3
#define AFUN_4   4
#define AFUN_5   5
#define AFUN_6   6
#define AFUN_7   7
#define AFUN_8   8
#define AFUN_9   9
#define AFUN_10  10
#define AFUN_11  11
#define AFUN_12  12
#define AFUN_13  13
#define AFUN_14  14
#define AFUN_15  15

//types ::


//variables ::

//prototypes of functions ::

/*
    GPIO_X_PINDirection : to Select the mode of pins
    inputs: options from [GPIO_X  &  PIN_X  &  MODE_X ]
    output: options from [Res_X]
    call in main: GPIO_X_PINDirection(GPIO_A  &  PIN_0  &  MODE_Input )
*/
Res_t GPIOX_PIN_Direction(u32 GPIO ,u32 PIN ,u32 MODE );

/*
    GPIOX_PIN_OUTPUTConfg : to Select the o/p pin confg
    inputs: options from [GPIO_X  &  PIN_X  & Output_Type_X  & SPEED_Type &  PULL_Type_X ]
    output: options from [Res_X]
    call in main: GPIOX_PIN_OUTPUTConfg(GPIO_A , PIN_0 ,Output_Type_pushpull ,SPEED_Type_High ,PULL_Type_Pulldown )
*/
Res_t GPIOX_PIN_OUTPUTConfg(u32 GPIO , u32 PIN , u32 Output_Type  ,u32 SPEED_Type);


/*
    GPIOX_PIN_AlternatefunctionConfg: Selects the alternate function pin configuration.
    Inputs:
        - GPIO: The GPIO port to configure (e.g., GPIO_A, GPIO_B, etc.).
        - PIN: The specific pin within the GPIO port to configure (e.g., PIN_0, PIN_1, etc.).
        - Output_Type: The type of output configuration for the pin (e.g., Output_Type_pushpull).
        - SPEED_Type: The speed type for the pin (e.g., SPEED_Type_High).
        - AFUN: The alternate function to configure for the pin (e.g., AFUN_0).
    Output:
        - Res_t: The result of the configuration operation (e.g., success or failure).
    Call in main:
        - GPIOX_PIN_AlternatefunctionConfg(GPIO_A, PIN_0, Output_Type_pushpull, SPEED_Type_High, AFUN_0)
*/

/*
    GPIOX_PIN_AlternatefunctionConfg : to Select the Alternate function pin confg
    inputs: options from [GPIO_X  &  PIN_X  & Output_Type_X  & SPEED_Type &  PULL_Type_X ]
    output: options from [Res_X]
    call in main: GPIOX_PIN_AlternatefunctionConfg(GPIO_A , PIN_0 ,Output_Type_pushpull ,SPEED_Type_High , AFUN_0)
*/
Res_t GPIOX_PIN_AlternatefunctionConfg(u32 GPIO , u32 PIN , u32 Output_Type  ,u32 SPEED_Type , u32 AFUN);

/*
    GPIOX_PIN_INPUTConfg : to Select the i/p pin confg
    inputs: options from [GPIO_X  &  PIN_X  &  PULL_Type_X ]
    output: options from [Res_X]
    call in main: GPIOX_PIN_INPUTConfg(GPIO_A , PIN_0  ,  PULL_Type_Pulldown )
*/
Res_t GPIOX_PIN_INPUTConfg(u32 GPIO , u32 PIN ,u32 PULL_Type  );

/*
    GPIOX_GetPIN_Value : to GET pin VALUE
    inputs: options from [GPIO_X , PIN_X  , &RESUALTE ]
    output: options from [Res_X]
    call in main: GPIOX_GetPIN_Value(GPIO_A ,PIN_0 , &RES)
*/
Res_t GPIOX_GetPIN_Value(u32 GPIO ,u32 PIN ,u32 *RES);

/*
    GPIOX_SetPIN_Value : to set pin value
    inputs: options from [GPIO_X , PIN_X  , Value  ]
    output: options from [Res_X]
    call in main: GPIOX_SetPIN_Value(GPIO_A ,PIN_0 , Value_Low)
*/
Res_t GPIOX_SetPIN_Value(u32 GPIO ,u32 PIN ,u32 Value);

#endif /* GPIO_X_H_ */
