/******************************************************************************
 * @file        ADC.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Digital Input Output (ADC) driver for Atmega128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE.h"
#include "ADC_reg.h"
#include "ADC.h"
#include "ADC_cfg.h"

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                          PRIVATE FUNCTIONS PROTOTYPES                       */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
static ERROR_t ADC_InitChannel(const ADC_CHANNEL_t channel);
static ERROR_t ADC_SetReferenceVoltage(const ADC_REFERENCE_t reference);
static ERROR_t ADC_SetAdjustment(const ADC_ADJUST_t adjustment);
static ERROR_t ADC_SetChannel(const ADC_CHANNEL_t channel);
static ERROR_t ADC_ControlAutoTrigger(const ADC_AUTO_TRIGGER_t autoTrigger);
static ERROR_t ADC_SetPrescaler(ADC_PRESCALER_t prescaler);
static ERROR_t ADC_GetChannelIndex(const ADC_CHANNEL_t channel, s8_t * const index);
static ERROR_t ADC_StartConversion(void);


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PRIVATE VARIABLES                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
static void (*ADC_Callback)(void) = NULL;
static ADC_t ADC_CurrentRunningADC = 0;
static u16_t * ADC_AsyncResult = NULL;


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              MACRO LIKE FUNCTIONS                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
#define ASSERT_VALID_ADC(channel)                 ((channel) < NUM_OF_ADC_CHANNELS )

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PUBLIC FUNCTIONS                               */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

ERROR_t ADC_Init(void) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countChannelsConfigured; ++i) {
        error |= ADC_InitChannel(adcConfigs[i].channel);

        if(error != ERROR_OK) {
            break;
        }
    }

    error |= ADC_Enable();

    return error;
}

ERROR_t ADC_Read(const ADC_CHANNEL_t channel, u16_t * const ptrToValue) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= ADC_GetChannelIndex(channel, &i);

    if( ASSERT_VALID_ADC(adcConfigs[i].adc)) {

        if(ADC_CurrentRunningADC != adcConfigs[i].adc) {
            error = ADC_InitChannel(channel);
            if(error != ERROR_OK) {
                return error;
            }
        }

        ADC_DisableInterrupt();
        error |= ADC_StartConversion();
        while(BIT_IS_CLEAR(ADC->ADCSRA, ADIF)) {
            /*!< Wait for conversion to finish */
        };

        BIT_SET(ADC->ADCSRA, ADIF);

        if(BIT_IS_SET(ADC->ADMUX, ADLAR)) {
            *ptrToValue  = ( (ADC->ADCL) >> 6) & 0x3;
            *ptrToValue |= (u16_t)(ADC->ADCH) << 2;
        } else {       
            *ptrToValue  = (u8_t)(ADC->ADCL);
            *ptrToValue |= ((u16_t)(ADC->ADCH) & 0x3) << 8;
        }
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t ADC_ReadAsync(const ADC_CHANNEL_t channel, u16_t * const ptrToValue, void (* const ADC_Callback) (void)) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= ADC_GetChannelIndex(channel, &i);

    if( ASSERT_VALID_ADC(adcConfigs[i].adc)) {

        if(ADC_CurrentRunningADC != adcConfigs[i].adc) {
            error = ADC_InitChannel(channel);
            if(error != ERROR_OK) {
                return error;
            }
        }

        ADC_SetCallback(ADC_Callback);
        ADC_AsyncResult = ptrToValue;
        error |= ADC_EnableInterrupt();
        error |= ADC_StartConversion();
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}


ERROR_t ADC_Enable(void) {  
    BIT_SET(ADC->ADCSRA, ADEN);
    return ERROR_OK;
}

ERROR_t ADC_Disable(void) {  
    BIT_CLR(ADC->ADCSRA, ADEN);
    return ERROR_OK;
}

ERROR_t ADC_EnableInterrupt(void) {
    BIT_SET(ADC->ADCSRA, ADIE);
    GIE_Enable();
    return ERROR_OK;
}

ERROR_t ADC_DisableInterrupt(void) {
    BIT_CLR(ADC->ADCSRA, ADIE);
    return ERROR_OK;
}

ERROR_t ADC_SetCallback(void (* const ptrToCallback)(void)) {
    ERROR_t error = ERROR_OK;

    if(NULL != ptrToCallback) {
        ADC_Callback = ptrToCallback;
    } else {
        error |= ERROR_NULL_POINTER;
    }
    
    return error;
}

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PRIVATE FUNCTIONS                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

static ERROR_t ADC_InitChannel(const ADC_CHANNEL_t channel) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;
    
    /*!< Get the index of the channel in the array, -1 if not found */
    error |= ADC_GetChannelIndex(channel, &i);

    if(error || (i < 0)) {
        if(i < 0) {
            error |= ERROR_INVALID_PARAMETER;
        }

        return error;
    }

    /*!< Disable ADC interrupt */
    ADC_DisableInterrupt();
    BIT_SET(ADC->ADCSRA, ADIF);

    error |= ADC_SetChannel(channel);
    error |= ADC_SetPrescaler(adcConfigs[i].prescaler);
    error |= ADC_ControlAutoTrigger(adcConfigs[i].autoTrigger);
    error |= ADC_SetAdjustment(adcConfigs[i].adjust);
    error |= ADC_SetReferenceVoltage(adcConfigs[i].reference);  

    return error;
}

static ERROR_t ADC_SetReferenceVoltage(const ADC_REFERENCE_t reference) {
    ERROR_t error = ERROR_OK;
    
    switch(reference) {
        case ADC_REFERENCE_AREF:
            BIT_CLR(ADC->ADMUX, REFS1);
            BIT_CLR(ADC->ADMUX, REFS0);
            break;
        case ADC_REFERENCE_AVCC:
            BIT_CLR(ADC->ADMUX, REFS1);
            BIT_SET(ADC->ADMUX, REFS0);
            break;
        case ADC_REFERENCE_INTERNAL:
            BIT_SET(ADC->ADMUX, REFS1);
            BIT_SET(ADC->ADMUX, REFS0);
            break;
        default:
            error |= ERROR_INVALID_PARAMETER;
            break;
    }

    return error;
}

static ERROR_t ADC_SetAdjustment(const ADC_ADJUST_t adjustment) {
    ERROR_t error = ERROR_OK;
    
    switch(adjustment) {
        case ADC_ADJUST_LEFT:
            BIT_SET(ADC->ADMUX, ADLAR);
            break;
        case ADC_ADJUST_RIGHT:
            BIT_CLR(ADC->ADMUX, ADLAR);
            break;
        default:
            error |= ERROR_INVALID_PARAMETER;
            break;
    }

    return error;
}

static ERROR_t ADC_SetChannel(const ADC_CHANNEL_t channel) {
    ERROR_t error = ERROR_OK;
    s8_t i = 0;

    error |= ADC_GetChannelIndex(channel, &i);

    if(error || (i < 0) || ( !ASSERT_VALID_ADC(adcConfigs[i].adc) )) {
        return error;
    }

    if(ADC_CurrentRunningADC != adcConfigs[i].adc) {
        ADC->ADMUX &= ~(0x1F << MUX0);                  /*!< Clear the channel bits */
        ADC->ADMUX |= (adcConfigs[i].adc << MUX0);      /*!< Set the channel bits */ 
        ADC_CurrentRunningADC = adcConfigs[i].adc;      /*!< Set the current channel */
    } else {
        /* Do nothing */
    }
         
    return error;
}

static ERROR_t ADC_ControlAutoTrigger(const ADC_AUTO_TRIGGER_t autoTrigger) {
    ERROR_t error = ERROR_OK;
    
    switch(autoTrigger) {
        case ADC_AUTO_TRIGGER_OFF:
            BIT_CLR(ADC->ADCSRA, ADFR);
            break;
        case ADC_AUTO_TRIGGER_ON:
            BIT_SET(ADC->ADCSRA, ADFR);
            break;
        default:
            error |= ERROR_INVALID_PARAMETER;
            break;
    }

    return error;
}

static ERROR_t ADC_SetPrescaler(ADC_PRESCALER_t prescaler) {
    ERROR_t error = ERROR_OK;
    u8_t prescalerOldValue = 0;

    /*!< Get the old prescaler value, then clear the prescaler bits */
    prescalerOldValue = (ADC->ADCSRA >> ADPS0) & 0x07;
    ADC->ADCSRA &= ~(0x07 << ADPS0);

    /*!< Set the new prescaler value */
    switch(prescaler) {
        case ADC_PRESCALER_2:
            ADC->ADCSRA |= (0x01 << ADPS0);
            break;
        case ADC_PRESCALER_4:
            ADC->ADCSRA |= (0x02 << ADPS0);
            break;
        case ADC_PRESCALER_8:
            ADC->ADCSRA |= (0x03 << ADPS0);
            break;
        case ADC_PRESCALER_16:
            ADC->ADCSRA |= (0x04 << ADPS0);
            break;
        case ADC_PRESCALER_32:
            ADC->ADCSRA |= (0x05 << ADPS0);
            break;
        case ADC_PRESCALER_64:
            ADC->ADCSRA |= (0x06 << ADPS0);
            break;
        case ADC_PRESCALER_128:
            ADC->ADCSRA |= (0x07 << ADPS0);
            break;
        default:
            error |= ERROR_INVALID_PARAMETER;
            break;
    }

    /*!< If an error occurred, restore the old prescaler value */
    if(error) {
        ADC->ADCSRA &= ~(0x07 << ADPS0);
        ADC->ADCSRA |= (prescalerOldValue << ADPS0);
    }

    return error;
}

static ERROR_t ADC_GetChannelIndex(const ADC_CHANNEL_t channel, s8_t * const index) {
    u8_t i = 0;

    if(NULL == index) {
        return ERROR_NULL_POINTER;
    } else {
        *index = -1;
    }

    for(i = 0; i < countChannelsConfigured; ++i) {
        if(adcConfigs[i].channel == channel) {
            *index = i;
            break;
        }
    }

    return ERROR_OK;
}

static ERROR_t ADC_StartConversion(void) {  
    BIT_SET(ADC->ADCSRA, ADSC);
    return ERROR_OK;
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                                  ISR                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*!< ADC Conversion Complete Interrupt */
void __vector_21(void) __attribute__((signal));
void __vector_21(void) {
    GIE_Disable();
    ADC_DisableInterrupt();

    if(NULL != ADC_AsyncResult) {
        if(BIT_IS_SET(ADC->ADMUX, ADLAR)) {
            *ADC_AsyncResult  = ( (ADC->ADCL) >> 6) & 0x3;
            *ADC_AsyncResult |= (u16_t)(ADC->ADCH) << 2;
        } else {       
            *ADC_AsyncResult  = (u8_t)(ADC->ADCL);
            *ADC_AsyncResult |= ((u16_t)(ADC->ADCH) & 0x3) << 8;
        }

        ADC_AsyncResult = NULL;
    }

    if(NULL != ADC_Callback) {
        ADC_Callback();

        ADC_Callback = NULL;
    }

    BIT_SET(ADC->ADCSRA, ADIF);     /*!< Clear ADC interrupt flag */
    GIE_Enable();
}
