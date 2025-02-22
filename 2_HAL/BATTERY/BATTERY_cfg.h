/******************************************************************************
 * @file        BATTERY_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref BATTERY.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef BATTERY_CFG_H
#define BATTERY_CFG_H

#define BATTERY_CAPACITY        18.0f      /* 18 AH    */
#define BATTERY_VOLTAGE         12.0f      /* 12 V     */
#define BATTERY_FULL_VOLTAGE    12.0f      /* 12 V     */
#define BATTERY_EMPTY_VOLTAGE   6.0f       /* 6 V      */

/* if the battery voltage rating is higher than the logic voltage of the microcontroller, use 
    a voltage divider to convert the battery voltage to the logic voltage */
#define BATTERY_VOLTAGE_DIVIDER_RATIO    (12 / 4.0f)    /* 12V : 4V    */

typedef struct{
    DIO_PIN_t       pin;
    DIO_PORT_t      port;
    f32_t         minVoltage;
    f32_t         maxVoltage;
}BatteryConfigs_t;

extern BatteryConfigs_t BatteryConfigs;

#endif
