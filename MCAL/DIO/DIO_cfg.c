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

PinConfig_t  pinConfigs[] = {
    /* IR pins  */
    {PIN_2, PORT_E, INPUT, PULLUP_FALSE},
    {PIN_3, PORT_E, INPUT, PULLUP_FALSE},
    {PIN_4, PORT_E, INPUT, PULLUP_FALSE},
    {PIN_5, PORT_E, INPUT, PULLUP_FALSE},

    /* NRF24 DIO pins   */
    {PIN_7, PORT_E, OUTPUT, PULLUP_FALSE},    /* CE pin   */
    {PIN_0, PORT_B, OUTPUT, PULLUP_FALSE},    /* CSN(SPI --> SS) pin  */

    /* Wheels Enable pins   */
    {PIN_3, PORT_G, OUTPUT, PULLUP_FALSE},    /* ENA pin   */
    {PIN_4, PORT_G, OUTPUT, PULLUP_FALSE},    /* ENB pin  */

    /* Ultrasonic pins  */
    {PIN_0, PORT_D, OUTPUT, PULLUP_FALSE},    /* ECHO pin   */
    {PIN_1, PORT_D, OUTPUT, PULLUP_FALSE},    /* TRIG pin  */

    /* Lifter Steppper pins  */
    {PIN_4, PORT_D, OUTPUT, PULLUP_FALSE},    /* DIR pin   */
    {PIN_5, PORT_D, OUTPUT, PULLUP_FALSE},    /* PUL pin  */

    /* Buttons Pins Configurations  */
    {PIN_6, PORT_D, INPUT, PULLUP_TRUE},    /* Automatic/Manual button  */
    {PIN_7, PORT_D, INPUT, PULLUP_TRUE},    /* Return button  */

    /* Battery pins     */
    {PIN_1, PORT_F, OUTPUT, PULLUP_FALSE},    /* Battery Charge Enable  */
    {PIN_5, PORT_F, OUTPUT, PULLUP_FALSE},    /* Battery Indicator  */

    /* Alarm    */
    {PIN_7, PORT_F, OUTPUT, PULLUP_FALSE},

    /* LEDs Pins Configurations  */
    {PIN_6, PORT_F, OUTPUT, PULLUP_FALSE},    /* NEON lamp    */

};

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

const u8_t countPinsConfigured = SIZE_OF_ARRAY(pinConfigs);

