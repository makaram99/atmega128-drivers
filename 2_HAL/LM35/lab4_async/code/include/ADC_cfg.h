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
    ADC_AUTO_TRIGGER_OFF,         /*!< Auto Trigger Disabled */
    ADC_AUTO_TRIGGER_ON,          /*!< Auto Trigger Enabled */
} ADC_AUTO_TRIGGER_t;

typedef enum {
    ADC_PRESCALER_2,        /*!< ADC clock = CPU clock / 2 */
    ADC_PRESCALER_4,        /*!< ADC clock = CPU clock / 4 */
    ADC_PRESCALER_8,        /*!< ADC clock = CPU clock / 8 */
    ADC_PRESCALER_16,       /*!< ADC clock = CPU clock / 16 */
    ADC_PRESCALER_32,       /*!< ADC clock = CPU clock / 32 */
    ADC_PRESCALER_64,       /*!< ADC clock = CPU clock / 64 */
    ADC_PRESCALER_128,      /*!< ADC clock = CPU clock / 128 */
} ADC_PRESCALER_t;

typedef enum {
    ADC_ADJUST_RIGHT,       /*!< Right adjust result */
    ADC_ADJUST_LEFT,        /*!< Left adjust result */
} ADC_ADJUST_t;


/******************************************************************************
 * @brief   This struct is used to pass the configuration of a channel to the 
 *          APIs of the ADC module.
 * @note    Members:
 *          - ADC_t name: The name of the ADC channel.
 *          - ADC_PRESCALER_t prescaler: The prescaler of the ADC.
 *          - ADC_REF_t reference: The reference voltage of the ADC.
 *          - ADC_AUTO_TRIGGER_t autoTrigger: The auto trigger of the ADC.
 *          - ADC_ADJUST_t adjust: The adjust of the ADC.
 *****************************************************************************/
typedef struct{
    ADC_CHANNEL_t       channel;
    ADC_t               adc;
    ADC_PRESCALER_t     prescaler;
    ADC_REFERENCE_t     reference;
    ADC_AUTO_TRIGGER_t  autoTrigger;
    ADC_ADJUST_t        adjust;
} ADC_CONFIGS_t;

/********************************************************************************
 * @note pins a of SSegment connected to MSB and dot point to LSB if no BCD is used 
 ********************************************************************************/

extern ADC_CONFIGS_t  adcConfigs[];
extern const u8_t countChannelsConfigured;

#endif    /* ADC_CFG_H */