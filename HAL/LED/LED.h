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
}LED_t;


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                               API's PROTOTYPES                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/********************************************************************************
 * @brief Initializes LEDs connected to DIO
 ********************************************************************************/
void LED_Init(void);

/********************************************************************************
 * @brief Turns on/off a specific LED
 * @param[in] led: the LED to be turned on/off, LED_0 to LED_7
 * @param[in] state: the state of the LED, LED_ON or LED_OFF
 * @par For example:
 *      * LED_Write(LED_0, LED_ON) turns on LED_0
 *      * LED_Write(LED_0, LED_OFF) turns off LED_0
 ********************************************************************************/
void LED_Write(const LED_t led, const STATE_t state);

/**********************************************************************************
 * @brief       Toggle state of a specific LED
 * @param[in]   led: The LED to be turned on/off
 * @example     LED_Toggle(LED_0);
 **********************************************************************************/
/**********************************************************************************
 * @brief       Toggle state of a specific LED
 * @param[in]   led: The LED to be oggles
 * @par         Example:
 *              @code 
 *              // toggle LED_0: LED_0 will be turned on if it was off and vice versa 
 *              LED_Toggle(LED_0);   
 *              @endcode
 **********************************************************************************/
void LED_Toggle(const LED_t led);

/**********************************************************************************
 * @brief Turn on/off a specific LED
 * @param[in] led: The LED to be turned on/off
 * @param[in] state: The state of the LED, either LED_ON or LED_OFF
 * @par Example:
 *      @code LED_Set(LED_0, LED_ON);   // turn on LED_0    @endcode
 *      @code LED_Set(LED_0, LED_OFF);  // turn off LED_0   @endcode
 **********************************************************************************/
STATE_t LED_Read(const LED_t led);

#endif     /* LED_H */              
