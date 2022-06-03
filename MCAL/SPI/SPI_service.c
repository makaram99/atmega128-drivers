/**************************************************************************
 * @file        SPI_service.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       SPI service implementation
 * @version     1.0.0
 * @date        2022-05-07
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI.h"
#include "SPI_service.h"



ERROR_t SPI_SendString(const u8_t *str, const u8_t length) {
    ERROR_t error = ERROR_NO;

    for(u8_t i = 0; i < length; ++i) {
        error = SPI_SendByte(str[i]);

        if(error != ERROR_NO) {
            error = ERROR_YES;
            break;
        }
    }

    return error;
}

ERROR_t SPI_ReceiveString(u8_t * const str, const u8_t length) {
    ERROR_t error = ERROR_NO;

    u8_t i = 0;
    while(i < length) {
        error = SPI_ReceiveByte(&str[i]);
        ++i;
        
        if(error == ERROR_YES) {
            break;
        }
    }

    return error;
}

