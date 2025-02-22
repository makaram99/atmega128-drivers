/******************************************************************************
 * @file        DIO_cfg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration header file for \ref DIO.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              DO NOT CHANGE ANYTHING BELOW THIS COMMENT                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @brief   Enum for the pins.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 *          The enum is used as a parameter for almost all APIs
 *****************************************************************************/
typedef enum{
    DIO_PIN_0,    
    DIO_PIN_1,
    DIO_PIN_2,
    DIO_PIN_3,
    DIO_PIN_4,
    DIO_PIN_5,
    DIO_PIN_6,
    DIO_PIN_7,
    NUM_OF_PINS     /*!< Number of pins of each port: used for debugging */
}DIO_PIN_t;

/******************************************************************************
 * @brief   Enum for the ports numbers.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 *          The enum is used as a parameter for almost all APIs
 *****************************************************************************/
typedef enum{
    DIO_PORT_A,
    DIO_PORT_B,
    DIO_PORT_C,
    DIO_PORT_D,
    DIO_PORT_E,
    DIO_PORT_F,
    DIO_PORT_G,
    NUM_OF_PORTS    /*!< Number of ports: used for debugging */
}DIO_PORT_t;

/******************************************************************************
 * @brief   This struct is used to pass the configuration of a pin to the APIs
 *          of the DIO module.
 * @note    Members:
 *          - pin: The pin number.
 *          - port: The port number. 
 *          - dir: The direction of the pin.
 *          - pullup: The pullup state of the pin.
 *****************************************************************************/
typedef struct{
    DIO_PINS_t      name;
    DIO_PIN_t       pin;
    DIO_PORT_t      port;
    DIO_DIR_t       direction;
    DIO_PULLUP_t    pullup;
} DIO_PIN_CONFIGS_t;

/********************************************************************************
 * @note pins a of SSegment connected to MSB and dot point to LSB if no BCD is used 
 ********************************************************************************/

extern DIO_PIN_CONFIGS_t  pinConfigs[];
extern const u8_t countPinsConfigured;

#endif    /* DIO_CFG_H */