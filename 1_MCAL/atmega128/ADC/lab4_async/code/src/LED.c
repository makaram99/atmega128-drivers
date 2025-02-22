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

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                            PRIVATE FUNCTIONS PROTOTYPES                      */
/*                                                                              */
/*------------------------------------------------------------------------------*/
static ERROR_t LED_ReadIndex(const LED_t led, s8_t * const ptr_s8Index);

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                            MACRO LIKE FUNCTIONS                              */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#define ASSERT_LED(led)         ( led < NUM_OF_LEDS )

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                              PUBLIC FUNCTIONS                                */
/*                                                                              */
/*------------------------------------------------------------------------------*/

ERROR_t LED_Init(void) {
    return ERROR_OK;
}

ERROR_t LED_SetClr(const LED_t led, const STATE_t state) { 
    ERROR_t error = ERROR_OK;
    s8_t i = 0;
    
    error |= LED_ReadIndex(led, &i);
    if(i >= 0) {
        error |= DIO_SetPinValue(ledConfigs[i].pin, state);
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t LED_Toggle(const LED_t led) {
    ERROR_t error = ERROR_OK;
    STATE_t state = LOW;
    s8_t i = 0;
    
    error |= LED_ReadIndex(led, &i);
    if(i < 0) {
        return ERROR_INVALID_PARAMETER;
    }

    error |= DIO_ReadPin(ledConfigs[i].pin, &state);

    /* Toggle the LED */
    DIO_SetPinValue(ledConfigs[i].pin, !state);

    return error;
}

ERROR_t LED_Read(const LED_t led, STATE_t * const ptrToState) { 
    ERROR_t error = ERROR_OK;
    s8_t i = 0;
    
    if(NULL == ptrToState) {
        return ERROR_NULL_POINTER;
    } 

    error |= LED_ReadIndex(led, &i);
    if(i >= 0) {
        error |= DIO_ReadPin(ledConfigs[i].pin, ptrToState);
    } else {
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
 * @brief Get the index of the led in the ledConfigs array
 * 
 * @param[in] led: The led to get the index of
 * @param[in] ptr_s8Index: The pointer to the index of the led. 
 *              Options:
 *                    -1: The led is not in the buttonsConfigs array
 *                  >= 0: The index of the led in the buttonsConfigs array
 * @return ERROR_t: The error status of the function.
 ******************************************************************************/
static ERROR_t LED_ReadIndex(const LED_t led, s8_t * const ptr_s8Index) {
    u8_t i = 0;

    if(NULL == ptr_s8Index) {
        return ERROR_NULL_POINTER;
    }

    *ptr_s8Index = -1;

    if( !ASSERT_LED(led) ) {
        return ERROR_INVALID_PARAMETER;
    }

    for(i = 0; i < countLedsConfigured; ++i) {
        if(led == ledConfigs[i].led) {
            *ptr_s8Index = i;
        }
    }

    return ERROR_OK;
}

