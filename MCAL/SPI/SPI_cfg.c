/******************************************************************************
 * @file        SPI_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref SPI.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_reg.h"
#include "DIO.h"
#include "SPI.h"
#include "SPI_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

SPI_CONFIG_t SPI_Config = {
    .connections = { 
        .SS     = { .pin = PIN_0, .port = PORT_B},
        .SCK    = { .pin = PIN_1, .port = PORT_B},
        .MOSI   = { .pin = PIN_2, .port = PORT_B},
        .MISO   = { .pin = PIN_3, .port = PORT_B}
    },
    .mode           = SPI_MASTER,
    .clockDivider   = SPI_PRESCALER_8,
    .dataOrder      = SPI_DATA_ORDER_MSB_FIRST,
    .doubleSpeed    = SPI_DOUBLE_SPEED_DISABLE,
    .clockMode      = SPI_MODE0,
};
