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

/**********************************************************************************/
/*OUTPUT CONFG*/
	/**options for pins**/
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
	/**options for ports**/
#define DIRECTION_PORT_INPUT          0x00000000
#define DIRECTION_PORT_OUTPUT		  0x55555555
#define DIRECTION_PORT_ALTERNATE_FUN  0xAAAAAAAA
#define DIRECTION_PORT_FUN            0xFFFFFFFF

#define PORT_VALUE_LOW   0x00000000
#define PORT_VALUE_HIGH  0x0000FFFF

#define OUTPUT_PORT_TYPE_PUSHPULL    0x00000000
#define OUTPUT_PORT_TYPE_OPENDRAIN   0x0000FFFF

#define SPEED_PORT_TYPE_Low      0x00000000
#define SPEED_PORT_TYPE_Medium   0x55555555
#define SPEED_PORT_TYPE_High     0xAAAAAAAA
#define SPEED_PORT_TYPE_VerHigh  0xFFFFFFFF

#define PULL_PORT_TYPE_FLOATING    0x00000000
#define PULL_PORT_TYPE_PULLUP      0x55555555
#define PULL_PORT_TYPE_PULLDOWN    0xAAAAAAAA

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
typedef struct
{
	u32 GPIO ;
	u32 PIN;
	u32 MODE ;
	u32 Output_Type;
	u32 SPEED_Type ;
	u32 PULL_Type ;
	u32 AFUN ;
}GPIO_Cfg_t;

//variables ::

//prototypes of functions ::

/*
    typedef struct GPIO_Cfg_t: Structure definition for configuring GPIO pins.

    Members:
        - GPIO: The GPIO port to configure.
        - PIN: The specific pin within the GPIO port to configure.
        - MODE: The mode configuration for the pin.
        - Output_Type: The type of output configuration for the pin.
        - SPEED_Type: The speed type for the pin.
        - PULL_Type: The pull-up/pull-down configuration for the pin.
        - AFUN: The alternate function configuration for the pin.

    typedef Res_t GPIOX_InitPin(GPIO_Cfg_t *PinCfg): Function declaration for initializing a GPIO pin.

    Input:
        - PinCfg: A pointer to a GPIO_Cfg_t structure that holds the configuration settings for the GPIO pin.

    Output:
        - Res_t: The result of the pin initialization operation (e.g., success or failure).
*/
Res_t GPIOX_InitPin(GPIO_Cfg_t *PinCfg);
/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_GetPIN_Value: This function is used to get the value of a pin.
    Inputs: 
        - GPIO_X: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - PIN_X: The specific pin within the GPIO port to select (e.g., PIN_0, PIN_1, etc.).
        - &RESULT: A pointer to the variable that will store the pin value.
    Output: 
        - Res_X: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_GetPIN_Value(GPIO_A, PIN_0, &RESULT)
*/
Res_t GPIOX_GetPinValue (u32 GPIO ,u32 PIN ,u32 *RES);
/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_SetPIN_Value: This function is used to set the value of a pin.
    Inputs: 
        - GPIO_X: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - PIN_X: The specific pin within the GPIO port to select (e.g., PIN_0, PIN_1, etc.).
        - Value: The value to set for the pin (e.g., Value_Low).
    Output: 
        - Res_X: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_SetPIN_Value(GPIO_A, PIN_0, Value_Low)
*/
Res_t GPIOX_SetPinValue(u32 GPIO ,u32 PIN ,u32 Value);
/***********************************************************************************************************/
/***********************************************************************************************************/

Res_t GPIOX_TogPin(u32 GPIO ,u32 PIN) ;

/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_SetPortDirection: This function is used to select the direction of a GPIO port.
    Inputs: 
        - GPIO_X: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - DIRECTION_PORT_X: The direction to select for the port (e.g., DIRECTION_PORT_INPUT).
    Output: 
        - Res_X: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_SetPortDirection(GPIO_A, DIRECTION_PORT_INPUT)
*/
Res_t GPIOX_SetPortDirection (u32 GPIO, u32 DIRECTION_PORT);
/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_SetPortValue: This function is used to set the value of a GPIO port.
    Inputs: 
        - GPIO_X: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - PORT_VALUE_X: The value to set for the port (e.g., PORT_VALUE_LOW).
    Output: 
        - Res_X: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_SetPortValue(GPIO_A, PORT_VALUE_LOW)
*/
Res_t GPIOX_SetPortValue (u32 GPIO, u32 PORT_VALUE );
/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_ConfigPortOutput: This function is used to select the output port configuration.
    Inputs: 
        - GPIO: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - OUTPUT_PORT_TYPE: The output type to select for the port (e.g., OUTPUT_PORT_TYPE_PUSHPULL).
        - SPEED_PORT_TYPE: The speed type to select for the port (e.g., SPEED_PORT_TYPE_Low).
    Output: 
        - Res_t: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_ConfigPortOutput(GPIO_A, OUTPUT_PORT_TYPE_PUSHPULL, SPEED_PORT_TYPE_Low)
*/
Res_t GPIOX_ConfigPortOutput (u32 GPIO , u32 OUTPUT_PORT_TYPE  , u32 SPEED_PORT_TYPE );
/***********************************************************************************************************/
/***********************************************************************************************************/

/*
    GPIOX_ConfigPortInput: This function is used to select the input port configuration.
    Inputs: 
        - GPIO_X: The GPIO port to select (e.g., GPIO_A, GPIO_B, etc.).
        - PULL_PORT_TYPE: The pull type to select for the pin (e.g., PULL_PORT_TYPE_PULLUP).
    Output: 
        - Res_X: The output of the function (e.g., success or failure).
    Call in main: 
        - Example usage: GPIOX_ConfigPortInput(GPIO_A, PULL_PORT_TYPE_PULLUP)
*/
Res_t GPIOX_ConfigPortInput (u32 GPIO ,u32 PULL_PORT_TYPE  );

#endif /* GPIO_X_H_ */
