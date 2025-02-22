/******************************************************************************
 * @file        LED_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref LED.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "MATH.h"
#include "DIO.h"
#include "LED.h"
#include "LED_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                     CHANGE THE FOLLOWING TO YOUR NEEDS                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

LED_CONFIGS_t ledConfigs[] = {
    {LED_0, DIO_PINS_LED_0},
    {LED_1, DIO_PINS_LED_1},
    {LED_2, DIO_PINS_LED_2},
};

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                     DO NOT CHANGE ANYTHING BELOW THIS LINE                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

const u8_t countLedsConfigured = sizeof(ledConfigs) / sizeof(ledConfigs[0]);