/******************************************************************************
 * @file        BUTTON_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref BUTTON.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef BUTTON_CFG_H   
#define BUTTON_CFG_H

typedef enum{
    DEBOUNCE_OFF,
    DEBOUNCE_ON
}DEBOUNCE_t;

typedef struct{
    BUTTON_t                button;
    PIN_t                   pin;
    PORT_t                  port;
    ACTIVATION_STATUS_t     ActiveHighOrLow;
    DEBOUNCE_t              debounceStatus;
}BUTTON_CONFIGS_t;

extern BUTTON_CONFIGS_t buttonsConfigs[];
extern const u8_t countButtonsConfigured;

#endif      /* BUTTON_CFG_H */              
