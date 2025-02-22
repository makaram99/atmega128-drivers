/******************************************************************************
 * @file        I2C_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref I2C.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_reg.h"
#include "DIO.h"
#include "I2C.h"
#include "I2C_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

I2C_CONFIG_t I2C_Config = {
    .connections = { 
        .SS     = { .pin = DIO_PIN_0, .port = DIO_PORT_B},
        .SCK    = { .pin = DIO_PIN_1, .port = DIO_PORT_B},
        .MOSI   = { .pin = DIO_PIN_2, .port = DIO_PORT_B},
        .MISO   = { .pin = DIO_PIN_3, .port = DIO_PORT_B}
    },
    .mode           = I2C_MASTER,
    .clockDivider   = I2C_PRESCALER_8,
    .dataOrder      = I2C_DATA_ORDER_MSB_FIRST,
    .doubleSpeed    = I2C_DOUBLE_SPEED_DISABLE,
    .clockMode      = I2C_MODE0,
};
