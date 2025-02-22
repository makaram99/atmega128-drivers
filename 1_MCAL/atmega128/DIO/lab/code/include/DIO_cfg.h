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

extern DIO_PIN_CONFIGS_t  pinConfigs[];
extern const u8_t countPinsConfigured;

#endif    /* DIO_CFG_H */