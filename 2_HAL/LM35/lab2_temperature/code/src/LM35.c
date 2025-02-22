/******************************************************************************
 * @file        LM35.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Driver for LM35 temperature sensor
 * @version     1.0.0
 * @date        2022-07-02
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC.h"
#include "LM35.h"
#include "LM35_cfg.h"

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                          PRIVATE FUNCTIONS PROTOTYPES                       */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
static ERROR_t LM35_InitSensor(const LM35_t channel);
static ERROR_t LM35_GetChannelIndex(const LM35_t channel, s8_t * const index);



/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PUBLIC FUNCTIONS                               */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

ERROR_t LM35_Init(void) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countSensorsConfigured; ++i) {
        error |= LM35_InitSensor(lm35Configs[i].lm35);

        if(error != ERROR_OK) {
            break;
        }
    }

    error |= LM35_Enable();

    return error;
}

ERROR_t LM35_Read(const LM35_t channel, u16_t * const ptrToValue) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= LM35_GetChannelIndex(channel, &i);

    if( (i >= 0) && (NULL != ptrToValue) ) {
        error |= ADC_Read(lm35Configs[i].adc, ptrToValue);
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t LM35_ReadAsync(const LM35_t channel, u16_t * const ptrToValue, void (* const callback) (void)) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= LM35_GetChannelIndex(channel, &i);

    if( (i >= 0) && (NULL != callback)) {
        error |= ADC_ReadAsync(lm35Configs[i].adc, ptrToValue, callback);
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PRIVATE FUNCTIONS                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

static ERROR_t LM35_InitSensor(const LM35_t channel) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;
    
    /*!< Get the index of the channel in the array, -1 if not found */
    error |= LM35_GetChannelIndex(channel, &i);

    if(error || (i < 0)) {
        if(i < 0) {
            error |= ERROR_INVALID_PARAMETER;
        }

        return error;
    }

    error |= ADC_SetReferenceVoltage(lm35Configs[i].adc, lm35Configs[i].reference);  

    return error;
}

static ERROR_t LM35_GetChannelIndex(const LM35_t lm35, s8_t * const index) {
    u8_t i = 0;

    if(NULL == index) {
        return ERROR_NULL_POINTER;
    } else {
        *index = -1;
    }

    for(i = 0; i < countSensorsConfigured; ++i) {
        if(lm35Configs[i].lm35 == lm35) {
            *index = i;
            break;
        }
    }

    return ERROR_OK;
}

