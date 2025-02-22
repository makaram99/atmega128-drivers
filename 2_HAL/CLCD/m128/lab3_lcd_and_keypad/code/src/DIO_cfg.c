/******************************************************************************
 * @file        DIO_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref DIO.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "MATH.h"
#include "DIO.h"
#include "DIO_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Configuration of the DIO pins.
 * @details This array contains the configuration of the used DIO pins.
 *          Configurations are:
 *          - Pin
 *          - Port
 *          - Direction   
 *          - Pullup     (if applicable)
 ******************************************************************************/
DIO_PIN_CONFIGS_t  pinConfigs[] = {
    /* CLCD      */
    {DIO_PINS_CLCD_RS, DIO_PIN_1, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},            /* RS */
    {DIO_PINS_CLCD_E,  DIO_PIN_2, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},            /* E */
    {DIO_PINS_CLCD_RW, DIO_PIN_3, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},            /* RW */

    {DIO_PINS_CLCD_D0, DIO_PIN_0, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D0 */
    {DIO_PINS_CLCD_D1, DIO_PIN_1, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D1 */
    {DIO_PINS_CLCD_D2, DIO_PIN_2, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D2 */
    {DIO_PINS_CLCD_D3, DIO_PIN_3, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D3 */
    {DIO_PINS_CLCD_D4, DIO_PIN_4, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D4 */
    {DIO_PINS_CLCD_D5, DIO_PIN_5, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D5 */
    {DIO_PINS_CLCD_D6, DIO_PIN_6, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D6 */
    {DIO_PINS_CLCD_D7, DIO_PIN_7, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},            /* D7 */

    {DIO_PINS_KEYPAD_R0, DIO_PIN_0, DIO_PORT_D, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PINS_KEYPAD_R1, DIO_PIN_1, DIO_PORT_D, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PINS_KEYPAD_R2, DIO_PIN_2, DIO_PORT_D, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PINS_KEYPAD_R3, DIO_PIN_3, DIO_PORT_D, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PINS_KEYPAD_C0, DIO_PIN_4, DIO_PORT_D, DIO_INPUT, DIO_PULLUP_ON}, 
    {DIO_PINS_KEYPAD_C1, DIO_PIN_5, DIO_PORT_D, DIO_INPUT, DIO_PULLUP_ON}, 
    {DIO_PINS_KEYPAD_C2, DIO_PIN_6, DIO_PORT_D, DIO_INPUT, DIO_PULLUP_ON}, 
    {DIO_PINS_KEYPAD_C3, DIO_PIN_7, DIO_PORT_D, DIO_INPUT, DIO_PULLUP_ON},   
};


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Number of used DIO pins.
 * @details This variable counts the number of used DIO pins which is equal to
 *          the number of elements in the \ref pinConfigs array. 
 ******************************************************************************/
const u8_t countPinsConfigured = sizeof(pinConfigs) / sizeof(pinConfigs[0]);

