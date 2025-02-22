/**************************************************************************************
 * @file        IR_Library.ino
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref IR.c
 * @version     1.0.0
 * @date        2022-03-20
 *************************************************************************************/
#include "STD_TYPES.h"
#include "MATH.h"
#include "DIO.h"
#include "IR.h"
#include "IR_cfg.h"

/**************************************************************************************
 * @note    ACTIVE_LOW means that the pin is:
 *              * LOW when the sensor is detecting an object (white)
 *              * HIGH when the sensor is not detecting an object (black)
 *          ACTIVE_HIGH means that the pin is:
 *              * HIGH when the sensor is detecting an object (white)
 *              * LOW when the sensor is not detecting an object (black)
 *************************************************************************************/
IR_CONFIG_t IR_configs[] = {
    {IR_0, DIO_PIN_2, DIO_PORT_E, ACTIVE_LOW}, /* Right */
    {IR_1, DIO_PIN_3, DIO_PORT_E, ACTIVE_LOW}, /* Center */
    {IR_2, DIO_PIN_4, DIO_PORT_E, ACTIVE_LOW}  /* Left */
};

const u8_t countIRSensorsConfigured = sizeof(IR_configs) / sizeof(IR_configs[0]);
