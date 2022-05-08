/**************************************************************************
 * @file        UART.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref UART.c
 * @version     1.0.0
 * @date        2022-03-03
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef UART_H
#define UART_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS PROTOTYPES                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/******************************************************************************
 * @brief Initialize UART module 0 as configured in UART_cfg.h and UART_cfg.c
 * @par   It configure UART module 0 accorfing to UART_cfg.h and UART_cfg.c
 *        and then enable UART module 0
 ******************************************************************************/
void UART0_Init(void);

/******************************************************************************
 * @brief Initialize UART module 1 as configured in UART_cfg.h and UART_cfg.c
 * @par   It configure UART module 1 accorfing to UART_cfg.h and UART_cfg.c
 *        and then enable UART module 1
 ******************************************************************************/
void UART1_Init(void);

/******************************************************************************
 * @brief Disable UART module 0 if it is enabled
 ******************************************************************************/
void UART0_Disable(void);

/******************************************************************************
 * @brief Disable UART module 1 if it is enabled
 ******************************************************************************/
void UART1_Disable(void);

/******************************************************************************
 * @brief Enable UART module 0 if it is disabled previously by UART0_Disable()
 ******************************************************************************/
void UART0_Enable(void);

/******************************************************************************
 * @brief Enable UART module 1 if it is disabled previously by UART1_Disable()
 * @par   It enable UART module 1 if it is disabled previously by UART1_Disable()
 ******************************************************************************/
void UART1_Enable(void);

/******************************************************************************
 * @brief Send a byte using UART module 0 Synchronously
 * @par   For Example: UART0_SendByte('a'); will send character 'a' to UART module 0
 ******************************************************************************/
void UART0_SendByte(const u8_t data);

/******************************************************************************
 * @brief Send a byte using UART module 0 Asynchronously
 * @par   For Example: UART0_SendByte_NoBlock('a'); will send character 'a' to UART module 0
 *        without blocking the calling thread
 ******************************************************************************/
void UART0_SendByte_NoBlock(const u8_t data);

/******************************************************************************
 * @brief Send a byte using UART module 1
 * @par   For Example: UART1_SendByte('y'); will send character 'y' to UART module 1
 ******************************************************************************/
void UART1_SendByte(const u8_t data);

/******************************************************************************
 * @brief Send a byte using UART module 1 Asynchronously
 * @par   For Example: UART1_SendByte_NoBlock('a'); will send character 'a' to UART module 1
 *        without blocking the calling thread
 ******************************************************************************/
void UART1_SendByte_NoBlock(const u8_t data);

/******************************************************************************
 * @brief Send 9 bits using UART module 0
 * @par   For Example: UART0_Send9Bits(0x123); will send 9 bits 0x123 to UART module 0
 ******************************************************************************/
void UART0_Send9BitData(const u16_t data);

/******************************************************************************
 * @brief Send 9 bits using UART module 0 Asynchronously
 * @par   For Example: UART0_Send9Bits_NoBlock(0x123); will send 9 bits 0x123 to UART module 0
 *        without blocking the calling thread
 ******************************************************************************/
void UART0_Send9BitData_NoBlock(const u16_t data);

/******************************************************************************
 * @brief Send 9 bits using UART module 1
 * @param[in] data: 9 bits data to be sent. Should be between 0 and 0x1FF
 * @note Size of data should be 2 Bytes to be able to send 9 bits data
 * @par  For Example: UART1_Send9Bits(0x123); will send 9 bits 0x123 to UART module 1
 ******************************************************************************/
void UART1_Send9BitData(const u16_t data);

/******************************************************************************
 * @brief Send 9 bits using UART module 1 Asynchronously
 * @param[in] data: 9 bits data to be sent. Should be between 0 and 0x1FF
 * @note Size of data should be 2 Bytes to be able to send 9 bits data
 * @par  For Example: UART1_Send9Bits_NoBlock(0x123); will send 9 bits 0x123 to UART module 1
 *        without blocking the calling thread
 ******************************************************************************/
void UART1_Send9BitData_NoBlock(const u16_t data);

/******************************************************************************
 * @brief Check if there is a byte available in UART module 0
 * @return HIGH if there is a byte available, LOW otherwise
 ******************************************************************************/
STATE_t UART0_Available(void);

/******************************************************************************
 * @brief Check if there is a byte available in UART module 1
 * @return HIGH if there is a byte available, LOW otherwise
 ******************************************************************************/
STATE_t UART1_Available(void);

/******************************************************************************
 * @brief Receive a byte using UART module 0
 * @par   For Example: UART0_ReceiveByte(&data); will receive a byte from UART module 0
 *       and store it in variable <data>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART0_ReceiveByte(u8_t *data);

/******************************************************************************
 * @brief Receive a byte using UART module 0 Asynchronously
 * @par   For Example: UART0_ReceiveByte(&data); will receive a byte from UART module 0
 *        and store it in variable <data> without checking receive complete flag 
 *        and without blocking the calling thread
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART0_ReceiveByte_NoBlock(u8_t *data);

/******************************************************************************
 * @brief Receive a byte using UART module 1
 * @par   For Example: UART1_ReceiveByte(&data); will receive a byte from UART module 1
 *        and store it in variable <data>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART1_ReceiveByte(u8_t *data);

/******************************************************************************
 * @brief Receive a byte using UART module 1 Asynchronously
 * @par   For Example: UART1_ReceiveByte(&data); will receive a byte from UART module 1
 *        and store it in variable <data> without checking receive complete flag 
 *        and without blocking the calling thread
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART1_ReceiveByte_NoBlock(u8_t *data);

/******************************************************************************
 * @brief Receive a string of 16 bits using UART module 0 (9 bits data)
 * @par   For Example: UART0_Receive9BitString(string); will receive a string of 16 bits
 *        from UART module 0 and store it in variable <string>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART0_Receive9BitData(u16_t *data);

/******************************************************************************
 * @brief Receive a string of 16 bits using UART module 1 (9 bits data)
 * @par   For Example: UART1_Receive9BitString(string); will receive a string of 16 bits
 *        from UART module 1 and store it in variable <string>
 * @return The error code: ERROR_NO if no error, ERROR_YES if error
 ******************************************************************************/
ERROR_t UART1_Receive9BitData(u16_t *data);

/******************************************************************************
 * @brief Flush the receive buffer of UART module 0
 * @par   For Example: UART0_Flush(); will flush the receive buffer of UART module 0
 ******************************************************************************/
void UART0_Flush(void);

/******************************************************************************
 * @brief Flush the receive buffer of UART module 1
 * @par   For Example: UART1_Flush(); will flush the receive buffer of UART module 1
 ******************************************************************************/
void UART1_Flush(void);

/******************************************************************************
 * @brief Enable the receive interrupt of UART module 0 with passing the function
 *        pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The interrupt is triggered when a byte is received
 ******************************************************************************/ 
void UART0_RX_InterruptEnable(void(* const ptrCallback)(void));    

/********************************************************************************
 * @brief Enable the receive interrupt of UART module 1 with passing the function
 *       pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The interrupt is triggered when a byte is received
 ********************************************************************************/
void UART1_RX_InterruptEnable(void(* const ptrCallback)(void));    

/******************************************************************************
 * @brief Disable the receive interrupt of UART module 0
 * @par   For Example: UART0_RX_InterruptDisable(); will disable the receive interrupt
 *        of UART module 0
 ******************************************************************************/
void UART0_RX_InterruptDisable(void);

/********************************************************************************
 * @brief Disable the receive interrupt of UART module 1
 * @par   For Example: UART1_RX_InterruptDisable(); will disable the receive interrupt
 *       of UART module 1
 ********************************************************************************/
void UART1_RX_InterruptDisable(void);

/******************************************************************************
 * @brief Enable the transmit interrupt of UART module 0 with passing the function
 *       pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The transmit interrupt will be triggered after transmission complete.
 ******************************************************************************/
void UART1_TX_InterruptEnable(void(* const ptrCallback)(void));

/********************************************************************************
 * @brief Enable the transmit interrupt of UART module 1 with passing the function
 *      pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The transmit interrupt will be triggered after transmission complete.
 ********************************************************************************/
void UART0_TX_InterruptEnable(void(* const ptrCallback)(void));

/********************************************************************************
 * @brief Disable the transmit interrupt of UART module 0
 * @par   For Example: UART0_TX_InterruptDisable(); will disable the transmit interrupt
 *      of UART module 0
 ********************************************************************************/
void UART0_TX_InterruptDisable(void);

/********************************************************************************
 * @brief Disable the transmit interrupt of UART module 1
 * @par   For Example: UART1_TX_InterruptDisable(); will disable the transmit interrupt
 *     of UART module 1
 ********************************************************************************/
void UART1_TX_InterruptDisable(void);

/******************************************************************************
 * @brief Enable the interrupt of Data Register Empty of UART module 0 with 
 *        passing the function pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The interrupt is triggered when the data register is empty
 ******************************************************************************/
void UART0_UDRE_InterruptEnable(void(* const ptrCallback)(void));

/********************************************************************************
 * @brief Enable the interrupt of Data Register Empty of UART module 1 with
 *       passing the function pointer to the interrupt service routine.
 * @param[in] ptrCallback: Pointer to the interrupt service routine
 * @note The interrupt is triggered when the data register is empty
 ********************************************************************************/
void UART1_UDRE_InterruptEnable(void(* const ptrCallback)(void));

/********************************************************************************
 * @brief Disable the interrupt of Data Register Empty of UART module 0
 * @par   For Example: UART0_UDRE_InterruptDisable(); will disable the interrupt
 *        of Data Register Empty of UART module 0
 ********************************************************************************/
void UART0_UDRE_InterruptDisable(void);

/********************************************************************************
 * @brief Disable the interrupt of Data Register Empty of UART module 1
 * @par   For Example: UART1_UDRE_InterruptDisable(); will disable the interrupt
 *      of Data Register Empty of UART module 1
 ********************************************************************************/
void UART1_UDRE_InterruptDisable(void);


#endif                  
