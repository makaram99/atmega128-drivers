/******************************************************************************
 * @file        ADC_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref ADC.c
 * @version     1.0.0
 * @date        2022-06-26
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef ADC_CFG_H
#define ADC_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef void (*ADC_CALLBACK_t)(void);

typedef enum {
    ADC_0,
    ADC_1,
    ADC_2,
    ADC_3,
    ADC_4,
    ADC_5,
    ADC_6,
    ADC_7,
    NUM_OF_ADC_CHANNELS
} ADC_t;

typedef enum {
    ADC_REFERENCE_AREF,           /*!< AREF, Internal Vref turned off */
    ADC_REFERENCE_AVCC,           /*!< AVCC, Internal Vref turned off */
    ADC_REFERENCE_INTERNAL,       /*!< Internal 2.56V Voltage Reference */
} ADC_REFERENCE_t;

typedef enum {
    ADC_AUTO_TRIGGER_OFF,         /*!< Auto Trigger Disabled */
    ADC_AUTO_TRIGGER_ON,          /*!< Auto Trigger Enabled */
} ADC_AUTO_TRIGGER_t;

typedef enum {
    ADC_PRESCALER_2,        /*!< ADC clock = CPU clock / 2 */