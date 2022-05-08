/******************************************************************************
 * @file        WHEELS_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref WHEELS.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef WHEELS_CFG_H
#define WHEELS_CFG_H

typedef struct {
    PIN_t   ENA_pin;
    PORT_t  ENA_port;
    PIN_t   ENB_pin;
    PORT_t  ENB_port;
    
    PWM_t   IN1A_channel;
    PWM_t   IN2A_channel;
    PWM_t   IN1B_channel;
    PWM_t   IN2B_channel;

    PIN_t   CTA_pin;
    PORT_t  CTA_port;
    PIN_t   CTB_pin;
    PORT_t  CTB_port;

    u8_t      currentSensitivity; /* In mV/A */
    u8_t      SpeedPercentage;    /* 0 - 100 */
    WHEELS_POSITION_t   WHEELS_Position;
}WHEELS_CONFIG_t;

typedef enum{
    ROTATE_STOP  ,
    ROTATE_FWD   ,
    ROTATE_BACK  ,
    ROTATE_RIGHT_SMOOTH ,
    ROTATE_RIGHT_SHARP  ,
    ROTATE_LEFT_SMOOTH  ,
    ROTATE_LEFT_SHARP
}ROTATE_DIR_t;

extern WHEELS_CONFIG_t WHEELS_Config;

#endif                  
