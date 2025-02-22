/******************************************************************************
 * @file        SPI_service.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       This file contains the prototypes of the SPI_service.c file
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef SPI_SERVICE_H       
#define SPI_SERVICE_H       

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS PROTOTYPES                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Sends a string through the SPI module
 * @param[in]   str: The string to be sent
 * @param[in]   length: The length of the string
 * @return      Error status: \ref ERROR_t
 * @note        The function blocks until the string is sent
 * @note        The function is blocking because the SPI module is not designed 
 *              to be used in interrupt mode and the function blocks until the 
 *              string is sent and received from the SPI module.
 ******************************************************************************/
ERROR_t SPI_SendString(const u8_t *str, const u8_t length);

/*******************************************************************************
 * @brief       Receives a string through the SPI module
 * @param[in]   str: The string to be received
 * @param[in]   length: The length of the string
 * @return      Error status: \ref ERROR_t
 * @note        The function blocks until the string is received
 * @note        The function is blocking because the SPI module is not designed 
 *              to be used in interrupt mode and the function blocks until the 
 *              string is sent and received from the SPI module.
 ******************************************************************************/
ERROR_t SPI_ReceiveString(u8_t * const str, const u8_t length);

#endif      /* SPI_SERVICE_H */
