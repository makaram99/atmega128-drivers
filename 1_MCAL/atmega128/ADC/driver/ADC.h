/******************************************************************************
 * @file            ADC.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file for Digital Input Output (ADC) module for 
 *                  Atmega128 microcontroller (\ref ADC.c)
 * @version         1.0.0
 * @date            2022-06-26
 * PRECONDITIONS:   - ADC.c must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef ADC_H
#define ADC_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    ADC_CHANNEL_TEMP,
} ADC_CHANNEL_t;

typedef enum {
    ADC_REFERENCE_AREF,           /*!< AREF, Internal Vref turned off */
    ADC_REFERENCE_AVCC,           /*!< AVCC, Internal Vref turned off */
    ADC_REFERENCE_INTERNAL,       /*!< Internal 2.56V Voltage Reference */
} ADC_REFERENCE_t;

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initialize ADC configurations based on user configurations in 
 *              ADC_cfg.h and ADC_cfg.c
 ******************************************************************************/
ERROR_t ADC_Init(void);
ERROR_t ADC_Read(const ADC_CHANNEL_t channel, u16_t * const ptrToValue);
ERROR_t ADC_ReadAsync(const ADC_CHANNEL_t channel, u16_t * const ptrToValue, void (* const ADC_Callback) (void));
ERROR_t ADC_Enable(void);  
ERROR_t ADC_Disable(void);  
ERROR_t ADC_SetReferenceVoltage(const ADC_CHANNEL_t channel, const ADC_REFERENCE_t reference);
ERROR_t ADC_EnableInterrupt(void);
ERROR_t ADC_DisableInterrupt(void);
ERROR_t ADC_SetCallback(void (* const ptrToCallback)(void));



#endif      /* ADC_H */