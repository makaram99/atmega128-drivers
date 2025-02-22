/******************************************************************************
 * @file        BUTTON_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref BUTTON.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "MATH.h"
#include "DIO.h"
#include "BUTTON.h"
#include "BUTTON_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                     CHANGE THE FOLLOWING TO YOUR NEEDS                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*****************************************************************************
 * @note    ACTIVE_LOW means that the pin is:
 *              * LOW when the sensor is pressed
 *              * HIGH when the sensor is not pressed
 *          ACTIVE_HIGH means that the pin is:
 *              * HIGH when the sensor is pressed
 *              * LOW when the sensor is not pressed
 *****************************************************************************/
BUTTON_CONFIGS_t buttonsConfigs[] = {
    {BUTTON_0, DIO_PIN_0, DIO_PORT_D, ACTIVE_LOW, DEBOUNCE_OFF},
    {BUTTON_1, DIO_PIN_1, DIO_PORT_D, ACTIVE_HIGH, DEBOUNCE_OFF},
    {BUTTON_2, DIO_PIN_2, DIO_PORT_D, ACTIVE_LOW, DEBOUNCE_OFF},
    {BUTTON_3, DIO_PIN_3, DIO_PORT_D, ACTIVE_LOW, DEBOUNCE_OFF},
};

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                     DO NOT CHANGE ANYTHING BELOW THIS LINE                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

const u8_t countButtonsConfigured = sizeof(buttonsConfigs) / sizeof(buttonsConfigs[0]);
