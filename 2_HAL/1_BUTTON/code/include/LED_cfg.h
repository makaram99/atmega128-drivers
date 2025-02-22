/******************************************************************************
 * @file        LED_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref LED.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef LED_CFG_H   
#define LED_CFG_H   

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                    DO NOT CHANGE ANYTHING BELOW THIS LINE                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct{
    LED_t   led;
    DIO_PIN_t   pin;
    DIO_PORT_t  port;
}LED_CONFIGS_t;

extern LED_CONFIGS_t ledConfigs[];
extern const u8_t countLedsConfigured;

#endif      /* LED_CFG_H */               
