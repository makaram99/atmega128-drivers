/******************************************************************************
 * @file        ADC_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref ADC.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "ADC.h"
#include "ADC_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Configuration of the ADC channels.
 * @details This array contains the configuration of the used ADC channels.
 *          Configurations are:
 *          - ADC_t name: The name of the ADC channel.
 *          - ADC_PRESCALER_t prescaler: The prescaler of the ADC. The ADC 
 *            freqquency is: fADC = fCLK / prescaler. And it must be
 *            between 50kHz and 200kHz.
 *          - ADC_REF_t reference: The reference voltage of the ADC.
 *          - ADC_AUTO_TRIGGER_t autoTrigger: The auto trigger of the ADC.
 *          - ADC_ADJUST_t adjust: The adjust of the ADC.
 ******************************************************************************/
ADC_CONFIGS_t  adcConfigs[] = {
    {ADC_CHANNEL_GAS,       ADC_0, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_LEFT, NULL},
    {ADC_CHANNEL_TEMP,      ADC_1, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_RIGHT, NULL},
    {ADC_CHANNEL_HUMIDITY,  ADC_2, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_LEFT, NULL},
    {ADC_CHANNEL_PRESSURE,  ADC_3, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_RIGHT, NULL},
    {ADC_CHANNEL_WATTER,    ADC_4, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_LEFT, NULL},
    {ADC_CHANNEL_LIGHT,     ADC_5, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_RIGHT, NULL},
    {ADC_CHANNEL_CAMERA,    ADC_6, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_LEFT, NULL},
    {ADC_CHANNEL_MICROPHONE,ADC_7, ADC_PRESCALER_128, ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_OFF, ADC_ADJUST_RIGHT, NULL},
};


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Number of used ADC pins.
 * @details This variable counts the number of used ADC pins which is equal to
 *          the number of elements in the \ref adcConfigs array. 
 ******************************************************************************/
const u8_t countChannelsConfigured = sizeof(adcConfigs) / sizeof(adcConfigs[0]);

