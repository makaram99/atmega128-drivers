/******************************************************************************
 * @file        SPI.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref SPI.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef SPI_H       
#define SPI_H       

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS PROTOTYPES                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initializes the SPI module
 ******************************************************************************/
void SPI_Init(void);

/*******************************************************************************
 * @brief       Sends a byte through the SPI module
 * @param[in]   data: The byte to be sent
 * @return      Error status: \ref ERROR_t
 * @note        The function blocks until the byte is sent
 * @note        The function is blocking because the SPI module is not designed 
 *              to be used in interrupt mode and the function blocks until the 
 *              byte is sent and received from the SPI module.
 ******************************************************************************/
ERROR_t SPI_SendByte(const u8_t data);

/*******************************************************************************
 * @brief       Check if the Receive buffer received a byte (Slave mode)
 * @param[out]  ptrState: Pointer to the return value
 * @return      Error status: \ref ERROR_t
 * @note        The function does not block
 ******************************************************************************/
ERROR_t SPI_Available(STATE_t * const ptrState);

/*******************************************************************************
 * @brief       Receives a byte through the SPI module
 * @param[out]  The byte received from the SPI module
 * @return      Error status: \ref ERROR_t
 * @note        The function blocks until the byte is received
 * @note        The function is blocking because the SPI module is not designed to
 *              be used in interrupt mode and the function blocks until the byte is
 *              sent and received from the SPI module.
 ******************************************************************************/
ERROR_t SPI_ReceiveByte(u8_t * const data);

/*******************************************************************************
 * @brief       Reads the SPI Data Register without any communication
 * @param[out]  data: poiter to the return value containing the value of the SPDR
 * @return      Error status: \ref ERROR_t
 * @note        The function does not block the CPU
 * @note		This function can be used in Slave mode to read the received 
 *				data from the master. In this case, you should call 
 *				SPI_Available() before Reading the SPI Data Register to cheeck 
 *				if the master has sent data or not.
 ******************************************************************************/
ERROR_t SPI_Read(u8_t * const data);

/*******************************************************************************
 * @brief       Sends and receives a byte through the SPI module
 * @param[in]   dataToSend: The byte to be sent
 * @param[out]  dataReceived: The byte received from the SPI module
 * @note        The function blocks until the byte is sent and received
 * @note        The function is blocking because the SPI module is not designed 
 *              to be used in interrupt mode and the function blocks until the 
 *              byte is sent and received from the SPI module.
 ******************************************************************************/
void SPI_TrancieveByte(const u8_t dataToSend, u8_t * const dataReceived);

/*******************************************************************************
 * @brief       Enables the Interrupts for the SPI module
 ******************************************************************************/
void SPI_EnableInterrupt(void(*ptrCallback)(void));

/*******************************************************************************
 * @brief       Disables the Interrupts for the SPI module
 ******************************************************************************/
void SPI_DisableInterrupt(void);

#endif      /* SPI_H */
