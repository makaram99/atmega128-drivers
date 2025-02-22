/******************************************************************************
 * @file            DIO.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file for Digital Input Output (DIO) module for Atmega128 
 *                  microcontroller (\ref DIO.c)
 * @version         1.1.0
 * @date            2022-01-23
 * @preconditions   - DIO.c must be included in the project
 *                  - DIO.h must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef DIO_H
#define DIO_H

/*------------------------------------------------------------------------------*/
/*                                  TYPEDEFS                                    */
/*------------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
typedef enum{
    DIO_PIN_0,    
    DIO_PIN_1,
    DIO_PIN_2,
    DIO_PIN_3,
    DIO_PIN_4,
    DIO_PIN_5,
    DIO_PIN_6,
    DIO_PIN_7,
    NUM_OF_PINS
}DIO_PIN_t;

typedef enum{
    DIO_PORT_A,
    DIO_PORT_B,
    DIO_PORT_C,
    DIO_PORT_D,
    NUM_OF_PORTS
}DIO_PORT_t;

typedef enum{
    DIO_INPUT = 0,
    DIO_OUTPUT = 1
}DIO_DIR_t;

typedef enum{
    DIO_PULLUP_OFF,
    DIO_PULLUP_ON
}DIO_PULLUP_t;

/**
 * @brief 
 * 
 */
typedef struct{
    DIO_PIN_t       pin;
    DIO_PORT_t      port;
    DIO_DIR_t       direction;
    DIO_PULLUP_t    pullup;

}DIO_PIN_CONFIGS_t;




/*------------------------------------------------------------------------------*/
/*                             API FUNCTIONS                                    */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initialize DIO configurations based on user configurations in 
 *              DIO_cfg.h and DIO_cfg.c
 ******************************************************************************/
ERROR_t DIO_Init(void);

/*******************************************************************************
 * @brief       Initialize a pin as input or output.
 * @param[in]   pinConfigs: Configurations of the pin. See \ref DIO_PIN_CONFIGS_t
 *                          to know which elements and options to pass.
 * @note        PinConfigs consists of:
 *                  pin:        The pin to be initialized: DIO_PIN_0 ... DIO_PIN_7
 *                  port:       The port of the pin: see \ref DIO_PORT_t for options 
 *                              to pass
 *                  direction:  The direction of the pin: DIO_INPUT or DIO_OUTPUT.
 *                  pullup:     The pullup of the pin: DIO_PULLUP_ON or DIO_PULLUP_OFF.
 * @return      ERROR_t:    error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t DIO_InitPin(const DIO_PIN_CONFIGS_t * const pinConfigs);

/*******************************************************************************
 * @brief Initialize full port as input or output.
 * @param[in] port: The port to be initialized: DIO_PORT_A ... DIO_PORT_G.
 * @param[in] direction: The direction of the port: DIO_INPUT or DIO_OUTPUT.
 * @param[in] pullup: The pullup of the port: DIO_PULLUP_ON or DIO_PULLUP_OFF.
 ******************************************************************************/
ERROR_t DIO_InitPort(const DIO_PORT_t port, const DIO_DIR_t direction, const DIO_PULLUP_t pullup);

/*******************************************************************************
 * @brief       Write HIGH OR LOW on the output pin, LOW to set set LOW, HIGH or
 *              any number to set HIGH.
 * @param[in]   pin:    The pin to be set LOW. See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to be set LOW. See \ref DIO_PORT_t for 
 *                      options.
 * @param[in]   state:  The state of the pin to be set. See \ref STATE_t for 
 *                      options.
 * @warning     If the pin is not configured in the DIO_cfg.h file, then this 
 *              function will do nothing.
 * @par Example:
 *  @code 
 *      DIO_ClrPin(DIO_PIN_0, DIO_PORT_A);     // turns off pin 0 of port A
 *  @endcode
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PIN_t pin, const DIO_PORT_t port, const STATE_t state);

/*******************************************************************************
 * @brief write a value on a specific port (value of 8-bits ranges from 0 to 255)
 * @param[in] port: The port to be modified, DIO_PORT_A to DIO_PORT_G
 * @param[in] value: value to set on the port (8 bits --> 0-255)
 * @par Example:
 *  @code 
 *  DIO_SetPortValue(DIO_PORT_A, 0xFF);  // sets all pins of port A to high          
 *  DIO_SetPortValue(DIO_PORT_A, 0x00);  // sets all pins of port A to low           
 *  DIO_SetPortValue(DIO_PORT_A, 0xF0);  // sets pins 4, 5, 6, 7 of port A to high   
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
ERROR_t DIO_SetPortValue(const DIO_PORT_t port, const u8_t value);

/*******************************************************************************
 * @brief       Read the state of a pin
 * @param[in]   pin         the pin to be read. See \ref DIO_PIN_t for options.
 * @param[in]   port        the port of the pin to be read. See \ref DIO_PORT_t for 
 *                          options.
 * @param[out]  ptrToState    the state of the pin. See \ref STATE_t for options.
 * @return      ERROR_t:    error code. See \ref ERROR_t for more information.
 * @warning     If the pin is not configured in the DIO_cfg.h file, then this 
 *              function will do nothing.
 * @par Example:
 *  @code 
 *      DIO_ReadPin(DIO_PIN_0, DIO_PORT_A);     // return the state of DIO_PIN_0 on PORT A       
 *      DIO_ReadPin(PIN6, DIO_PORT_B);      // return the state of PIN6 on PORT B       
 *  @endcode
 ******************************************************************************/
ERROR_t DIO_ReadPin(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const ptrToState);

/*******************************************************************************
 * @brief Read the state of the port (8 bits --> 0-255)
 * @param[in] port the port to be read, DIO_PORT_A to DIO_PORT_G
 * @return value of the port (8 bits --> 0-255)
 * @par Example:
 *  @code 
 *  DIO_ReadPort(DIO_PORT_A);  // return 0xFF when all pins of PORT A are high       
 *  DIO_ReadPort(DIO_PORT_A);  // return 0x00 when all pins of PORT A are low     
 *  DIO_ReadPort(DIO_PORT_A);  // return 0xF0 when pins (4~7) of PORT A are high  
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function return LOW.
 ******************************************************************************/
ERROR_t DIO_ReadPort(const DIO_PORT_t port, u8_t *const ptrValue);

/*******************************************************************************
 * @brief       Toggle the state of a pin
 * @param[in]   pin     The pin to be toggled. See \ref DIO_PIN_t for options.
 * @param[in]   port    The port of the pin to be toggled. See \ref DIO_PORT_t for
 *                      options.
 * @warning     If the pin is not configured in the DIO_cfg.h file, then this 
 *              function will do nothing.
 * @par Example:
 *  @code
 *      DIO_TogglePin(DIO_PIN_0, DIO_PORT_A); // toggle the state of DIO_PIN_0 on PORT A
 *  @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PIN_t pin, const DIO_PORT_t port);

/*******************************************************************************
 * @brief Toggle the state of a port
 * @param[in] port the port to be toggled, DIO_PORT_A to DIO_PORT_G
 * @par Example:
 *  @code
 *  DIO_TogglePort(DIO_PORT_A); // toggle the state of DIO_PORT_A
 *  DIO_TogglePort(DIO_PORT_A); // toggle the state of DIO_PORT_A
 *  @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePort(const DIO_PORT_t port);

ERROR_t DIO_SetLowNibbleValue(const DIO_PORT_t port, const u8_t value);

ERROR_t DIO_SetHighNibbleValue(const DIO_PORT_t port, const u8_t value);

ERROR_t DIO_SetClrPortPullup(const DIO_PORT_t port, const DIO_PULLUP_t pullup);

/*******************************************************************************
 * @brief       Enable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to enable its pullup resistor. 
 *                      See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to enable its pullup resistor. 
 *                      See \ref DIO_PORT_t for options.
 * @return      ERROR_t: error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t DIO_SetPinPullup(const DIO_PIN_t pin, const DIO_PORT_t port);

/*******************************************************************************
 * @brief       Disable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to disable its pullup resistor. 
 *                      See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to disable its pullup resistor. 
 *                      See \ref DIO_PORT_t for options.
 * @return      ERROR_t: error code. See \ref ERROR_t for more information.
 ******************************************************************************/
ERROR_t DIO_ClrPullup(const DIO_PIN_t pin, const DIO_PORT_t port);

#endif      /* DIO_H */