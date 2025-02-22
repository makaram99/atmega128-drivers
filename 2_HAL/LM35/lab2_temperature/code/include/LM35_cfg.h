/******************************************************************************
 * @file        LM35_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref LM35.c
 * @version     1.0.0
 * @date        2022-06-26
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef LM35_CFG_H
#define LM35_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef void (*LM35_CALLBACK_t)(void);

typedef enum {
    LM35_REFERENCE_AREF,           /*!< AREF, Internal Vref turned off */
    LM35_REFERENCE_AVCC,           /*!< AVCC, Internal Vref turned off */
    LM35_REFERENCE_INTERNAL,       /*!< Internal 2.56V Voltage Reference */
} LM35_REFERENCE_t;

typedef enum {
    LM35_AUTO_TRIGGER_OFF,         /*!< Auto Trigger Disabled */
    LM35_AUTO_TRIGGER_ON,          /*!< Auto Trigger Enabled */
} LM35_AUTO_TRIGGER_t;

typedef enum {
    LM35_PRESCALER_2,        /*!< LM35 clock = CPU clock / 2 */
    LM35_PRESCALER_4,        /*!< LM35 clock = CPU clock / 4 */
    LM35_PRESCALER_8,        /*!< LM35 clock = CPU clock / 8 */
    LM35_PRESCALER_16,       /*!< LM35 clock = CPU clock / 16 */
    LM35_PRESCALER_32,       /*!< LM35 clock = CPU clock / 32 */
    LM35_PRESCALER_64,       /*!< LM35 clock = CPU clock / 64 */
    LM35_PRESCALER_128,      /*!< LM35 clock = CPU clock / 128 */
} LM35_PRESCALER_t;

typedef enum {
    LM35_ADJUST_RIGHT,       /*!< Right adjust result */
    LM35_ADJUST_LEFT,        /*!< Left adjust result */
} LM35_ADJUST_t;


/******************************************************************************
 * @brief   This struct is used to pass the configuration of a channel to the 
 *          APIs of the LM35 module.
 * @note    Members:
 *          - LM35_t name: The name of the LM35 channel.
 *          - LM35_PRESCALER_t prescaler: The prescaler of the LM35.
 *          - LM35_REF_t reference: The reference voltage of the LM35.
 *          - LM35_AUTO_TRIGGER_t autoTrigger: The auto trigger of the LM35.
 *          - LM35_ADJUST_t adjust: The adjust of the LM35.
 *****************************************************************************/
typedef struct{
    LM35_t              lm35;
    ADC_CHANNEL_t       adc;
    ADC_REFERENCE_t     reference;
} LM35_CONFIGS_t;

/********************************************************************************
 * @note pins a of SSegment connected to MSB and dot point to LSB if no BCD is used 
 ********************************************************************************/

extern LM35_CONFIGS_t  lm35Configs[];
extern const u8_t countSensorsConfigured;

#endif    /* LM35_CFG_H */