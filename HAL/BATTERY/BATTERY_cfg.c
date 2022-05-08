/******************************************************************************
 * @file        BATTERY_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref BATTERY.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "DIO.h"
#include "BATTERY.h"
#include "BATTERY_cfg.h"

/**************************************************************************
 * @brief       Configurations for the Battery Management Module.
 * @details This is the configuration for the Battery Management Module.
 *          The configuration is done by the user. The user can change the
 *          configuration according to his needs. 
 * @note    The configuration is done in the BATTERY_cfg.h and BATTERY_cfg.c files. 
 *************************************************************************/
BatteryConfigs_t BatteryConfigs = {
    .pin        = PIN_0, 
    .port       = PORT_C, 
    .minVoltage = 11.2f, 
    .maxVoltage = 12.8f
};