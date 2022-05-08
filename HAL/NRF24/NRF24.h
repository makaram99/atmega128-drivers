/******************************************************************************
 * @file        NRF24.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref NRF24.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef NRF24_H       
#define NRF24_H       

void NRF24_Init(void);
void NRF24_TxMode(void);
void NRF24_SendString(u8_t *data, u8_t length);
void NRF24_RxMode(void);
u8_t NRF24_Available(void);
ERROR_t NRF24_ReceiveString(u8_t *data, u8_t length);

#endif                  
