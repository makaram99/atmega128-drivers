/******************************************************************************
 * @file        LED.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref LED.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef LED_H       
#define LED_H      

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                  TYPEDEFS                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef enum {
    LED_0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    NUM_OF_LEDS
}LED_t;


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                               API's PROTOTYPES                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/********************************************************************************
 * @brief Initializes LEDs connected to DIO
 ********************************************************************************/
ERROR_t LED_Init(void);


/******************************************************************************
 * @brief Turn on or off the led
 * 
 * @param[in] led: The led to turn on or off
 * @param[in] state: The state to turn on or off the led
 * @return ERROR_t: The error status of the function. See the enum \ref ERROR_t.
 ******************************************************************************/
ERROR_t LED_SetClr(const LED_t led, const STATE_t state);

/********************************************************************************
 * @brief       Turns on a specific LED
 * @param[in]   led: the LED to be turned on, See options in \ref LED_t.
 * @return      ERROR_t: error code, See options in \ref ERROR_t.
 * @par         Example:
 *              @code
 *              LED_Set(LED_0);     // turns on LED_0
 *              LED_Set(LED_5)      // turns on LED_5
 *              LED_Set(LED_10);    // returns ERROR_INVALID_PARAMETER
 *              @endcode
 ********************************************************************************/
#define LED_Set(led)    ( LED_SetClr(led, HIGH) )

/********************************************************************************
 * @brief       Turns off a specific LED
 * @param[in]   led: the LED to be turned off, See options in \ref LED_t.
 * @return      ERROR_t: error code, See options in \ref ERROR_t.
 * @par         Example:
 *              @code
 *              LED_Clr(LED_0);     // turns off LED_0
 *              LED_Clr(LED_5)      // turns off LED_5
 *              LED_Clr(LED_10);    // returns ERROR_INVALID_PARAMETER
 *              @endcode
 ********************************************************************************/
#define LED_Clr(led)    ( LED_SetClr(led, LOW) )

/**********************************************************************************
 * @brief       Toggle state of a specific LED. If the LED is on, it turns off, 
 *              and vice versa.
 * @param[in]   led: The LED to be toggled. See options in \ref LED_t.
 * @return      ERROR_t: error code, See options in \ref ERROR_t.
 * @par         Example:
 *  @code 
 *      LED_Toggle(LED_0);   // toggle LED_0: turn on if it was off and vice versa
 *      LED_Toggle(LED_5);   // toggle LED_5: turn on if it was off and vice versa
 *      LED_Toggle(LED_10);  // returns ERROR_INVALID_PARAMETER
 *  @endcode
 **********************************************************************************/
ERROR_t LED_Toggle(const LED_t led);

/**********************************************************************************
 * @brief Reads the state of a specific LED.
 * @param[in] led: The LED to be read. See options in \ref LED_t.
 * @param[out] ptrToState: The state of the LED. See options in \ref STATE_t.
 * @par Example:
 *  @code 
 *      LED_Read(LED_0, &state);    // If LED_0 is on, state will be HIGH
 *      LED_Read(LED_5, &state);    // If LED_5 is off, state will be LOW
 *      LED_Read(LED_10, &state);   // returns ERROR_INVALID_PARAMETER
 * @endcode
 **********************************************************************************/
ERROR_t LED_Read(const LED_t led, STATE_t * const ptrToState);

#endif     /* LED_H */              
