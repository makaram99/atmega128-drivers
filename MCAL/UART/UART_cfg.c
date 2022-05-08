/******************************************************************************
 * @file        UART_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref UART.c
 * @version     1.0.0
 * @date        2022-03-03
 * @copyright   Copyright (c) 2022
 ******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "registers.h"
#include "UART.h"
#include "UART_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/***********************************************************************
 * @note Baud rate options:
 *          - 2400UL    --> 2400 bits per second
 *          - 4800UL    --> 4800 bits per second
 *          - 9600UL    --> 9600 bits per second
 *          - 14400UL   --> 14400 bits per second
 *          - 19200UL   --> 19200 bits per second
 *          - 28800UL   --> 28800 bits per second
 *          - 38400UL   --> 38400 bits per second
 *          - 57600UL   --> 57600 bits per second
 *          - 76800UL   --> 76800 bits per second
 *          - 115200UL  --> 115200 bits per second
 *          - 230400UL  --> 230400 bits per second
 *          - 250000UL  --> 250000 bits per second
 *          - 500000UL  --> 500000 bits per second
 *          - 1000000UL --> 1000000 bits per second
 ***********************************************************************/

UART_CFG_t UART0_Configs = {
    .baud_rate  = 9600,
    .data_bits  = UART_DATA_8_BITS,
    .stop_bits  = UART_STOP_1_BIT,
    .parity     = UART_PARITY_DISABLE,
    .mode       = UART_MODE_ASYNCHRONOUS_NORMAL,
    .mode_type  = UART_MODE_TX_RX,
};

UART_CFG_t UART1_Configs = {
    .baud_rate  = 9600,
    .data_bits  = UART_DATA_8_BITS,
    .stop_bits  = UART_STOP_1_BIT,
    .parity     = UART_PARITY_DISABLE,
    .mode       = UART_MODE_ASYNCHRONOUS_NORMAL,
    .mode_type  = UART_MODE_TX_RX,
};