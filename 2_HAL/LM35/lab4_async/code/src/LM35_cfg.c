/******************************************************************************
 * @file        LM35_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref LM35.c
 * @version     1.0.0
 * @date        2022-07-02
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "ADC.h"
#include "LM35.h"
#include "LM35_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Configuration of the LM35 channels.
 * @details This array contains the configuration of the used LM35 channels.
 *          Configurations are:
 *          - LM35_t lm35: The name of the LM35 channel.
 *          - ADC_CHANNEL_t adc: The ADC channel that the LM35 channel is 
 *            connected to.
 *          - ADC_REFERENCE_t reference: The reference voltage that the LM35
 *            channel is connected to.
 ******************************************************************************/
LM35_CONFIGS_t  lm35Configs[] = {
    {LM35_0, ADC_CHANNEL_TEMP, ADC_REFERENCE_AVCC},
};


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Number of used LM35 pins.
 * @details This variable counts the number of used LM35 pins which is equal to
 *          the number of elements in the \ref lm35Configs array. 
 ******************************************************************************/
const u8_t countSensorsConfigured = sizeof(lm35Configs) / sizeof(lm35Configs[0]);

