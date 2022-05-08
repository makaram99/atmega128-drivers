/******************************************************************************
 * @file        BUTTON.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Button Management Module
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "DIO.h"
#include "BUTTON.h"
#include "BUTTON_cfg.h"

void BUTTON_Init(void) {
    /* Do nothing   */
}

STATE_t BUTTON_Read(BUTTON_t button) {
    STATE_t status = 0; 
    u16_t const DEBOUNCE_COUNTER  = 200; 
    u16_t u16_pressedCounter = 0;
    u16_t idxCounter = 0;
    u8_t i = 0;

    /* Loop on configured button in cfg.c file */
    for(i = 0; i < countButtonsConfigured; ++i) {
        if(button == buttonsConfigs[i].button) {
            switch(buttonsConfigs[i].debounceStatus) {
                case DEBOUNCE_ON:
                    for(idxCounter = 0; idxCounter < DEBOUNCE_COUNTER; ++idxCounter) {
                        if(HIGH == DIO_ReadPin(buttonsConfigs[i].pin, buttonsConfigs[i].port)) {
                            ++u16_pressedCounter;
                        }
                    }

                    if(u16_pressedCounter >= DEBOUNCE_COUNTER) {
                        status = HIGH;
                    }else if( (u16_pressedCounter < DEBOUNCE_COUNTER) && (u16_pressedCounter > 0) ) {
                        if(ACTIVE_LOW == buttonsConfigs[i].ActiveHighOrLow) {
                            status = HIGH;
                        }
                    }else {
                        status = LOW;
                    }
                    break;

                case DEBOUNCE_OFF:
                    status = DIO_ReadPin(buttonsConfigs[i].pin, buttonsConfigs[i].port);
                    break;
                default:
                    /* DEBUG */
                    break;
            }   /* end switch of debounceStatus */

            if(ACTIVE_LOW == buttonsConfigs[i].ActiveHighOrLow) {
                (status == LOW) ? (status = HIGH) : (status = LOW);
            }
            /* Status of Active HIGH does not need changes  */ 

            break;  /* exit for loop    */

        }   /* end if button exists in database    */

    }   /* end for loop of searching button in database    */

    return status;
}

void BUTTON_SetPullup(BUTTON_t button, PULLUP_t pullup) {
    u8_t i = 0;

    /* Loop on configured button in cfg.c file */
    for(i = 0; i < countButtonsConfigured; ++i) {
        if(button == buttonsConfigs[i].button) {
            DIO_SetPinPullup(buttonsConfigs[i].pin, buttonsConfigs[i].port, pullup);
        } else {
            /* Do nothing: Check another button   */
        }
    }

    if(i == countButtonsConfigured) {
        /* DEBUG: Invalid Button */
    } else {
        /* Do nothing: Button found   */
    }
}
