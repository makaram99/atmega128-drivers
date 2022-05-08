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

/********************************************************************************
 * @note pins a of SSegment connected to MSB and dot point to LSB if no BCD is used 
 ********************************************************************************/
/* Pins Configurations      */
typedef struct{
    PIN_t       pin;
    PORT_t      port;
    DIR_t       direction;
    PULLUP_t    pullup;

}PinConfig_t;

extern PinConfig_t  pinConfigs[];
extern const u8_t countPinsConfigured;

#endif    /* DIO_CFG_H */