/******************************************************************************
 * @file        LIFTER_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref LIFTER.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef LIFTER_CFG_H
#define LIFTER_CFG_H

/*******************************************************************************
 * @brief If you are using enable pin, Write 1, else write 0
 ******************************************************************************/
#define ENABLE_CONNECTION 0

/*******************************************************************************
 * DO NOT CHANGE ANYTHING BELOW THIS LINE
 ******************************************************************************/
typedef enum{
    LIFTER_UP,
    LIFTER_DOWN,
}LIFTER_DIR_t;

typedef struct{
    DIO_PIN_t       directionPin;
    DIO_PORT_t      directionPinPort;
    DIO_PIN_t       pulsePin;
    DIO_PORT_t      pulsePinPort;
    DIO_PIN_t       enablePin;
    DIO_PORT_t      enablePinPort;
    u8_t          overallStroke;
    u16_t         pulsesPerRevolution;
    u8_t          revolutionStroke;
    u8_t          speed;
}LIFTER_CONFIGS_t;

extern LIFTER_CONFIGS_t LifterConfigs;

#endif                  
