/******************************************************************************
 * @file        NRF24_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref NRF24.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NRF24_reg.h"
#include "DIO.h"
#include "GIE.h"
#include "SPI.h"
#include "NRF24.h"
#include "NRF24_cfg.h"

NRF24_t NRF24_cfg = {
    .pins  = {  .ce  = { .pin = DIO_PIN_7, .port = DIO_PORT_E },
                .csn = { .pin = DIO_PIN_0, .port = DIO_PORT_B } 
             },
    .channel    = 76,          /* Channel number */
    .payload_len = 20,      /* Use static payload length ... */
    .addressWidth = 5,      /* ... of 5 bytes */
    .txAddress  = { 0xE7, 0xE7, 0xE7, 0xE7, 0xE7 },
    .rx0Address = { 0xE7, 0xD3, 0xF0, 0x35, 0x77, },
    .rx1Address = { 0xC2, 0xC2, 0xC2, 0xC2, 0xC2 },
    .rx2Address = { 0xC3, 0xC2, 0xC2, 0xC2, 0xC2 },
    .rx3Address = { 0xC4, 0xC2, 0xC2, 0xC2, 0xC2 },
    .rx4Address = { 0xC5, 0xC2, 0xC2, 0xC2, 0xC2 },
    .rx5Address = { 0xC6, 0xC2, 0xC2, 0xC2, 0xC2 },
    .rxPipe = RX_PIPE1,
};

