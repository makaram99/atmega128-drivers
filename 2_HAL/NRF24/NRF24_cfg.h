/******************************************************************************
 * @file        NRF24_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref NRF24.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef NRF24_CFG_H
#define NRF24_CFG_H

typedef struct{
    DIO_PIN_t   pin;
    DIO_PORT_t  port;
}CONNECTIONS_t;

typedef struct{
    CONNECTIONS_t ce;
    CONNECTIONS_t csn;
    CONNECTIONS_t irq;
}PINS_t;

typedef enum{
    RX_PIPE0,  
    RX_PIPE1,
    RX_PIPE2,
    RX_PIPE3,
    RX_PIPE4,
    RX_PIPE5, 
}PIPE_t;

typedef struct{
    PINS_t pins;
    u8_t     channel;
    u8_t     payload_len;
    u8_t     addressWidth;
    u8_t     txAddress[5];
    u8_t     txPayload[32];
    u8_t     rx0Address[5];
    u8_t     rx0Payload[32];
    u8_t     rx1Address[5];
    u8_t     rx1Payload[32];
    u8_t     rx2Address[5];
    u8_t     rx2Payload[32];
    u8_t     rx3Address[5];
    u8_t     rx3Payload[32];
    u8_t     rx4Address[5];
    u8_t     rx4Payload[32];
    u8_t     rx5Address[5];
    u8_t     rx5Payload[32];
    PIPE_t rxPipe;


}NRF24_t;

extern NRF24_t NRF24_cfg;


#endif                  
