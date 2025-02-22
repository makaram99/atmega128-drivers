/******************************************************************************
 * @file        BUTTON.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Button Management Module
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "LED.h"        /* For testing */
#include "BUTTON.h"
#include "BUTTON_cfg.h"

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                        PRIVATE FUNCTIONS PROTOTYPES                          */
/*                                                                              */
/*------------------------------------------------------------------------------*/
static ERROR_t BUTTON_ReadIndex(const BUTTON_t button, s8_t * const ptr_s8Index);
static ERROR_t BUTTON_Debounce(const u8_t index, STATE_t * const ptrToState);

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                        MACRO LIKE FUNCTIONS                                  */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#define ASSERT_BUTTON(button)    ( (button < NUM_OF_BUTTONS) && (button >= BUTTON_0) )
#define ASSERT_PULLUP(pullup)    ( (DIO_PULLUP_ON == pullup) || (DIO_PULLUP_OFF == pullup) )
#define ASSERT_DEBOUNCE(debounce) ( (DEBOUNCE_ON == debounce) || (DEBOUNCE_OFF == debounce) )

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                              PUBLIC FUNCTIONS                                */
/*                                                                              */
/*------------------------------------------------------------------------------*/

ERROR_t BUTTON_Init(void) {
    return ERROR_OK;
}

ERROR_t BUTTON_Read(const BUTTON_t button, STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    if(NULL == ptrToState) {
        return ERROR_NULL_POINTER;
    }
    
    error |= BUTTON_ReadIndex(button, &i);
    if(i < 0) {
        return ERROR_INVALID_PARAMETER;
    }

    if(DEBOUNCE_ON == buttonsConfigs[i].debounce) {
        error |= BUTTON_Debounce(i, ptrToState);
    }else {
        error |= DIO_ReadPin(buttonsConfigs[i].pin, buttonsConfigs[i].port, ptrToState);
    }

    if(ACTIVE_LOW == buttonsConfigs[i].ActiveHighOrLow) {
        *ptrToState = !(*ptrToState);
    }

    return error;
}

ERROR_t BUTTON_SetClrPullup(const BUTTON_t button, const DIO_PULLUP_t pullup) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= BUTTON_ReadIndex(button, &i);
    if(i < 0) {
        return ERROR_INVALID_PARAMETER;
    }

    if( ASSERT_PULLUP(pullup) ) {
        error |= DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){buttonsConfigs[i].pin, buttonsConfigs[i].port, DIO_INPUT, pullup});
    }else {
        error |= ERROR_INVALID_PARAMETER;
    }    

    return error;
}

ERROR_t BUTTON_SetClrDebounce(const BUTTON_t button, const DEBOUNCE_t debounce) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= BUTTON_ReadIndex(button, &i);
    if(i < 0) {
        return ERROR_INVALID_PARAMETER;
    }

    if( ASSERT_DEBOUNCE(debounce) ) {
        buttonsConfigs[i].debounce = debounce;
    }else {
        error |= ERROR_INVALID_PARAMETER;
    }    

    return error;
}




/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                              PRIVATE FUNCTIONS                               */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/******************************************************************************
 * @brief       Get the index of the button in the buttonsConfigs array
 * 
 * @param[in]   button      The button to get the index of
 * @param[in]   ptr_s8Index The pointer to the index of the button. 
 *                  Options:
 *                    -1: The button is not in the buttonsConfigs array or
 *                        the button is not valid (button >= NUM_OF_BUTTONS)
 *                  >= 0: The index of the button in the buttonsConfigs array
 * PROTECTION:  This function protects the user from:
 *              - Passing NULL pointer to the ptr_s8Index
 *              - Passing an invalid button to the button parameter
 * @return      ERROR_t: The error status of the function.
 ******************************************************************************/
static ERROR_t BUTTON_ReadIndex(const BUTTON_t button, s8_t * const ptr_s8Index) {
    u8_t i = 0;

    if(NULL == ptr_s8Index) {
        return ERROR_NULL_POINTER;
    } 
    
    *ptr_s8Index = -1;
    
    if( ASSERT_BUTTON(button) ) {
        for(i = 0; i < countButtonsConfigured; ++i) {
            if(button == buttonsConfigs[i].button) {
                *ptr_s8Index = i;
            }
        }
    }
    
    return ERROR_OK;
}

/******************************************************************************
 * @brief       Read the button with debounce algorithm
 * 
 * @param[in]   index:      The index of the button in the buttonsConfigs array
 * @param[in]   ptrToState: The pointer to the state of the button. It will be 
 *                          set to HIGH or LOW.
 * @return      ERROR_t:    error code. See \ref ERROR_t for more information.
 ******************************************************************************/
static ERROR_t BUTTON_Debounce(const u8_t index, STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
    
    if(NULL == ptrToState) {
        return ERROR_NULL_POINTER;
    }

    if(index >= countButtonsConfigured) {
        return ERROR_INVALID_PARAMETER;
    }

    error |= DIO_ReadPin(buttonsConfigs[index].pin, buttonsConfigs[index].port, ptrToState);

    if(buttonsConfigs[index].ActiveHighOrLow == *ptrToState) {
        _delay_ms(DEBOUNCE_TIME_MS);
        error |= DIO_ReadPin(buttonsConfigs[index].pin, buttonsConfigs[index].port, ptrToState);
    }

    if(ACTIVE_LOW == buttonsConfigs[index].ActiveHighOrLow) {
        *ptrToState = !(*ptrToState);
    }

    return error;
}
