/********************************************************************************
 * @file        WHEELS_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref WHEELS.c
 * @version     1.0.0
 * @date        2022-03-19
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "TIMER.h"
#include "WHEELS.h"
#include "WHEELS_cfg.h"

WHEELS_CONFIG_t WHEELS_Config = {
    .ENA_pin    = DIO_PIN_3,
    .ENA_port   = DIO_PORT_G,

    .ENB_pin    = DIO_PIN_4,
    .ENB_port   = DIO_PORT_G,
    
    .IN1A_channel    = PWM_0,    
    .IN2A_channel    = PWM_1,
    .IN1B_channel    = PWM_2,    
    .IN2B_channel    = PWM_3,

    .CTA_pin    = DIO_PIN_6,
    .CTA_port   = DIO_PORT_A,

    .CTB_pin    = DIO_PIN_7,
    .CTB_port   = DIO_PORT_A,

    .currentSensitivity = 155,  /* 155 mV/A */
    .SpeedPercentage    = 60,      /* Speed = 60% */
    .WHEELS_Position    = WHEELS_ON_FRONT,
};