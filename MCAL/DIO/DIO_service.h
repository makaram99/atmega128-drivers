/*/*****************************************************************************
 * @file        DIO_service.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Provides the interface for Digital Input Output (DIO) service file
 *              \ref DIO_service.c
 * @version     1.1.0
 * @date        2022-01-23
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef DIO_SERVICE_H
#define DIO_SERVICE_H


/*******************************************************************************
 * @brief Initialize full port as input or output.
 * @param[in] port: The port to be initialized: PORT_A ... PORT_G.
 * @param[in] direction: The direction of the port: INPUT or OUTPUT.
 * @param[in] pullup: The pullup of the port: PULLUP_TRUE or PULLUP_FALSE.
 ******************************************************************************/
void DIO_InitPort(const PORT_t port, const DIR_t direction, const PULLUP_t pullup);

/*******************************************************************************
 * @brief write a value on a specific port (value of 8-bits ranges from 0 to 255)
 * @param[in] port: The port to be modified, PORT_A to PORT_G
 * @param[in] value: value to set on the port (8 bits --> 0-255)
 * @par Example:
 *  @code 
 *  DIO_WritePort(PORT_A, 0xFF);  // sets all pins of port A to high          
 *  DIO_WritePort(PORT_A, 0x00);  // sets all pins of port A to low           
 *  DIO_WritePort(PORT_A, 0xF0);  // sets pins 4, 5, 6, 7 of port A to high   
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
void DIO_WritePort(const PORT_t port, const u8_t value);

/*******************************************************************************
 * @brief Read the state of the port (8 bits --> 0-255)
 * @param[in] port the port to be read, PORT_A to PORT_G
 * @return value of the port (8 bits --> 0-255)
 * @par Example:
 *  @code 
 *  DIO_ReadPort(PORT_A);  // return 0xFF when all pins of PORT A are high       
 *  DIO_ReadPort(PORT_A);  // return 0x00 when all pins of PORT A are low     
 *  DIO_ReadPort(PORT_A);  // return 0xF0 when pins (4~7) of PORT A are high  
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function return LOW.
 ******************************************************************************/
u8_t DIO_ReadPort(const PORT_t port);

/*******************************************************************************
 * @brief Toggle the state of a port
 * @param[in] port the port to be toggled, PORT_A to PORT_G
 * @par Example:
 *  @code
 *  DIO_TogglePort(PORT_A); // toggle the state of PORT_A
 *  DIO_TogglePort(PORT_A); // toggle the state of PORT_A
 *  @endcode
 ******************************************************************************/
void DIO_TogglePort(const PORT_t port);

#endif      /* DIO_SERVICE_H */