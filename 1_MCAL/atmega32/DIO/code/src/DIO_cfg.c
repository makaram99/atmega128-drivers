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

/******************************************************************************
 * @brief   Configuration of the DIO pins.
 * @details This array contains the configuration of the used DIO pins.
 *          Configurations are:
 *          - Pin
 *          - Port
 *          - Direction   
 *          - Pullup     (if applicable)
 ******************************************************************************/
DIO_PIN_CONFIGS_t  pinConfigs[] = {
    /* LEDs   */
    {DIO_PIN_3, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},
    {DIO_PIN_5, DIO_PORT_B, DIO_OUTPUT, DIO_PULLUP_OFF},

    /* Button   */
    {DIO_PIN_4, DIO_PORT_B, DIO_INPUT, DIO_PULLUP_OFF},
};


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Number of used DIO pins.
 * @details This variable counts the number of used DIO pins which is equal to
 *          the number of elements in the \ref pinConfigs array. 
 ******************************************************************************/
const u8_t countPinsConfigured = sizeof(pinConfigs) / sizeof(pinConfigs[0]);

