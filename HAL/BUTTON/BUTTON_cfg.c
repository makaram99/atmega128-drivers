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

/*****************************************************************************
 * @note    ACTIVE_LOW means that the pin is:
 *              * LOW when the sensor is pressed
 *              * HIGH when the sensor is not pressed
 *          ACTIVE_HIGH means that the pin is:
 *              * HIGH when the sensor is pressed
 *              * LOW when the sensor is not pressed
 *****************************************************************************/
BUTTON_CONFIGS_t buttonsConfigs[] = {
    {BUTTON_0, PIN_6, PORT_D, ACTIVE_LOW, DEBOUNCE_OFF},
    {BUTTON_1, PIN_7, PORT_D, ACTIVE_LOW, DEBOUNCE_OFF},
};

const u8_t countButtonsConfigured = SIZE_OF_ARRAY(buttonsConfigs);
