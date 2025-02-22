/**************************************************************************
 * @file        BATTERY.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Battery Management Module
 * @version     1.0.0
 * @date        2022-02-08
 * @copyright   Copyright (c) 2022
 **************************************************************************/

#if 0   /* Until im[plementing ADC */

#include "STD_TYPES.h"
#include "DIO.h"
#include "ADC.h"
#include "BATTERY.h"
#include "BATTERY_cfg.h"

/**************************************************************************
 * @brief  Initialize the Battery Management Module
 *************************************************************************/
void BATTERY_Init() {
    /* Initialize the Battery Management Module */
}

/**************************************************************************
 * @brief Get the state of the battery
 * @return STATE_t HIGH if the battery is full, LOW if the battery is empty, 
 *         NORMAL if the battery is in between the two thresholds
 *************************************************************************/
STATE_t BATTERY_GetState() {
    f32_t batteryVoltage = 0.0f;
    STATE_t state = HIGH;
    
    /* Get the battery voltage */
    batteryVoltage = ADC_ReadVoltage(BatteryConfigs.pin, BatteryConfigs.port);
    batteryVoltage = batteryVoltage * BATTERY_VOLTAGE_DIVIDER_RATIO;
    
    /* Check the range of the battery */
    if(batteryVoltage > BatteryConfigs.maxVoltage) {
        state = HIGH;
    }else if(batteryVoltage < BatteryConfigs.minVoltage) {
        state = LOW;
    }else {
        state = NORMAL;
    }

    return state;
}

#endif