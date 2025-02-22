/**************************************************************************
 * @file        I2C_service.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       I2C service implementation
 * @version     1.0.0
 * @date        2022-05-07
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C.h"
#include "I2C_service.h"



ERROR_t I2C_SendString(const u8_t *str, const u8_t length) {
    ERROR_t error = ERROR_OK;

    for(u8_t i = 0; i < length; ++i) {
        error = I2C_SendByte(str[i]);

        if(error != ERROR_OK) {
            error = ERROR_NOK;
            break;
        }
    }

    return error;
}

ERROR_t I2C_ReceiveString(u8_t * const str, const u8_t length) {
    ERROR_t error = ERROR_OK;

    u8_t i = 0;
    while(i < length) {
        error = I2C_ReceiveByte(&str[i]);
        ++i;
        
        if(error == ERROR_NOK) {
            break;
        }
    }

    return error;
}

