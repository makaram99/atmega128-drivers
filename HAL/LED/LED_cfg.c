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

LED_CONFIGS_t ledConfigs[] = {
    {LED_0, PIN_6, PORT_F},    /* NEON Lamp    */
};

const u8_t countLedsConfigured = SIZE_OF_ARRAY(ledConfigs);