/******************************************************************************
 * @file        DIO_service.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Digital Input Output (DIO) driver for Atmega128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "DIO_service.h"

void DIO_InitPort(const PORT_t port, const DIR_t direction, const PULLUP_t pullup) {
    u8_t i = 0;

    for(i = 0; i < 8; ++i) {
        DIO_InitPin(i, port, direction, pullup);
    }
}

void DIO_SetPortPullup(const PORT_t port, const PULLUP_t pullup) {
    u8_t i = 0;

    for(i = 0; i < REGISTER_SIZE; ++i) {
        DIO_SetPinPullup(i, port, pullup);
    }
}

void DIO_TogglePort(const PORT_t port) {
    u8_t i = 0;

    for(i = 0; i < REGISTER_SIZE; ++i) {
        DIO_TogglePin(i, port);
    }
}

void DIO_WritePort(const PORT_t port, const u8_t value) {
    u8_t i = 0;

    for(i = 0; i < REGISTER_SIZE; ++i) {
        DIO_WritePin(i, port, GET_BIT(value, i));
    }
}

void DIO_WriteLowNibble(const PORT_t port, const u8_t value) {
    u8_t i = 0;

    for(i = 0; i < (REGISTER_SIZE / 2); ++i) {
        DIO_WritePin(i, port, GET_BIT(value, i));
    }
}


void DIO_WriteHighNibble(const PORT_t port, const u8_t value) {
    u8_t i = 0;

    for(i = (REGISTER_SIZE / 2); i < REGISTER_SIZE; ++i) {
        DIO_WritePin(i, port, GET_BIT(value, i));
    }
}


u8_t DIO_ReadPort(const PORT_t port) {
    u8_t value = 0;
    u8_t i = 0;

    for(i = 0; i < REGISTER_SIZE; ++i) {
        value |= (DIO_ReadPin(i, port) << i);
    }

    return value;
}

