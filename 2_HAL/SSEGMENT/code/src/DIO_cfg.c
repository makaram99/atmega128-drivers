/******************************************************************************
 * @file        DIO_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref DIO.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "MATH.h"
#include "DIO.h"
#include "DIO_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   CHANGE THIS PART TO YOUR NEEDS                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

DIO_PIN_CONFIGS_t  pinConfigs[] = {
    /* 7 Segment pins   */
    {DIO_PIN_1, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_2, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_3, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_4, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_5, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_6, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_7, DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_OFF},

    {DIO_PIN_0, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},    /* Dot pin  */

    /* Enable pins  */
    {DIO_PIN_6, DIO_PORT_C, DIO_OUTPUT, DIO_PULLUP_OFF},    /* Enable 0 */
    {DIO_PIN_7, DIO_PORT_C, DIO_OUTPUT, DIO_PULLUP_OFF},    /* Enable 1 */

};

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

const u8_t countPinsConfigured = sizeof(pinConfigs) / sizeof(pinConfigs[0]);

