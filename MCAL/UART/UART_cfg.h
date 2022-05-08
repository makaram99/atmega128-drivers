/******************************************************************************
 * @file        UART_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref UART.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef UART_CFG_H
#define UART_CFG_H

#define UART_TIMEOUT_CYCLE_COUNT  (16000)

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef enum {
    UART_DATA_5_BITS,
    UART_DATA_6_BITS,
    UART_DATA_7_BITS,
    UART_DATA_8_BITS,
    UART_DATA_9_BITS,
} UART_DATA_BITS_t;

typedef enum {
    UART_STOP_1_BIT,
    UART_STOP_2_BIT,
} UART_STOP_BITS_t;

typedef enum {
    UART_PARITY_DISABLE,
    UART_PARITY_ODD,
    UART_PARITY_EVEN,
} UART_PARITY_t;

typedef enum {
    UART_MODE_ASYNCHRONOUS_NORMAL,
    UART_MODE_ASYNCHRONOUS_DOUBLE_SPEED,
    UART_MODE_SYNCHRONOUS_MASTER,
    UART_MODE_SYNCHRONOUS_SLAVE,
} UART_MODE_t;

typedef enum {
    UART_MODE_TX,
    UART_MODE_RX,
    UART_MODE_TX_RX,
} UART_MODE_TYPE_t;

typedef enum{
    UART_RISING_EDGE_CLOCK,         /* Transmit on rising edge and receive on falling edge */
    UART_FALLING_EDGE_CLOCK,        /* Transmit on falling edge and receive on rising edge */
}UART_CLOCK_POLARITY_t;

typedef struct {
    const u32_t           baud_rate;
    UART_DATA_BITS_t    data_bits;
    UART_STOP_BITS_t    stop_bits;
    UART_PARITY_t       parity;
    UART_MODE_t         mode;
    UART_MODE_TYPE_t    mode_type;
    UART_CLOCK_POLARITY_t    clock_polarity;
} UART_CFG_t;

extern UART_CFG_t UART0_Configs;
extern UART_CFG_t UART1_Configs;

#endif                  
