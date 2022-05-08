/**********************************************************************************
 * @file        LED.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       LED Driver 
 * @version     1.0.0
 * @date        2022-02-01
 **********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "LED.h"
#include "LED_cfg.h"

/**********************************************************************************
 * @brief       Initialize LEDs Configurations
 **********************************************************************************/
void LED_Init(void) {
    /* do nothing   */
}

void LED_Write(const LED_t led, const STATE_t state) { 
    for(u8_t i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, state);
        }
    }
}

STATE_t LED_Read(const LED_t led) { 
    STATE_t state = LOW;

    for(u8_t i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            state = DIO_ReadPin(ledConfigs[i].pin, ledConfigs[i].port);
        }
    }

    return state;
}

void LED_Toggle(const LED_t led) {
    for(u8_t i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            if(HIGH == DIO_ReadPin(ledConfigs[i].pin, ledConfigs[i].port)) {
                DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, LOW);
            }else {
                DIO_WritePin(ledConfigs[i].pin, ledConfigs[i].port, HIGH);
            }
        } else {
            /* do nothing */
        }
    }
}