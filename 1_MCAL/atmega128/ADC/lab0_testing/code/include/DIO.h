/******************************************************************************
 * @file            DIO.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interface file for Digital Input Output (DIO) module for Atmega128 
 *                  microcontroller (\ref DIO.c)
 * @version         1.1.0
 * @date            2022-01-23
 * PRECONDITIONS:   - DIO.c must be included in the project
 *                  - DIO.h must be included in the project
 * @copyright       Copyright (c) 2022
 ******************************************************************************/
#ifndef DIO_H
#define DIO_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    /* CLCD pins */
    DIO_PINS_CLCD_D0,    
    DIO_PINS_CLCD_D1,
    DIO_PINS_CLCD_D2,
    DIO_PINS_CLCD_D3,
    DIO_PINS_CLCD_D4,
    DIO_PINS_CLCD_D5,
    DIO_PINS_CLCD_D6,
    DIO_PINS_CLCD_D7,
    DIO_PINS_CLCD_RS,
    DIO_PINS_CLCD_E,
    DIO_PINS_CLCD_RW,

    /* LED  pins */
    DIO_PINS_LED,
} DIO_PINS_t;

/******************************************************************************
 * @brief   Enum for the directions of the pins.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 * @warning Values of each directions depends on the value written to the
 *          DDR register when configuring the pin as input or output.  
 *****************************************************************************/
typedef enum{
    DIO_INPUT   = 0,  /*!< Input direction: Value depends on the input value in DDR register */
    DIO_OUTPUT  = 1
}DIO_DIR_t;

/******************************************************************************
 * @brief   Enum for the pullup states of the pins.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 * @warning Values of each pullup states depends on the value written to the
 *          PORT register when configuring the pin as input or output.
 *****************************************************************************/
typedef enum{
    DIO_PULLUP_OFF  = 0,
    DIO_PULLUP_ON   = 1
}DIO_PULLUP_t;




/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief       Initialize DIO configurations based on user configurations in 
 *              DIO_cfg.h and DIO_cfg.c
 ******************************************************************************/
ERROR_t DIO_Init(void);

/*******************************************************************************
 * @brief       Initialize a pin as input or output.
 * 
 * @param[in]   pin   : The pin to be initialized. See \ref DIO_PINS_t for 
 *                      more information.
 * @param[in]   dir   : The direction of the pin. See \ref DIO_DIR_t for more
 *                      information.
 * @param[in]   pullup: The pullup state of the pin. See \ref DIO_PULLUP_t for more
 *                      information.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              // Configure LED 0 as output
 *              DIO_Init(LED_0, DIO_OUTPUT, DIO_PULLUP_OFF);
 *  
 *              // Configure BUTTON 1 as input with pullup off
 *              DIO_Init(BUTTON_1, DIO_INPUT, DIO_PULLUP_OFF);
 *  
 *              // Configure BUTTON 2 as input with pullup on
 *              DIO_Init(BUTTON_2, DIO_INPUT, DIO_PULLUP_ON);   
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_InitPin(const DIO_PINS_t pin, const DIO_DIR_t direction, const DIO_PULLUP_t pullup);

/*******************************************************************************
 * @brief       Set the direction of a pin.
 * 
 * @param[in]   pin         : The pin to be configured. See \ref DIO_PINS_t for
 *                            more information.
 * @param[in]   direction   : The direction of the pin. See \ref DIO_DIR_t for more
 *                            information.
 * @return      ERROR_t     : Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code 
 *              // Configure LED 0 as output
 *              DIO_SetPinDirection(LED_0, DIO_OUTPUT);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetPinDirection(const DIO_PINS_t name, const DIO_DIR_t direction);

/*******************************************************************************
 * @brief       Write HIGH OR LOW on the output pin, LOW to set set LOW, HIGH or
 *              any number to set HIGH.
 * @param[in]   pin   : The pin to be configured. See \ref DIO_PINS_t for
 *                      options.
 * @param[in]   state : The state of the pin to be set. See \ref STATE_t for 
 *                      options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code 
 *              // Set LED 0 to HIGH
 *              DIO_SetPinState(LED_0, HIGH);
 *              
 *              // Set LED 0 to LOW
 *              DIO_SetPinState(LED_0, LOW); 
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PINS_t name, const STATE_t state);

/*******************************************************************************
 * @brief       Write HIGH on the output pin.
 * @param[in]   pin:    The pin to be set HIGH. See \ref DIO_PINS_t for options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Set LED 0 to HIGH
 *              DIO_SetPin(LED_0);
 *              @endcode
 ******************************************************************************/
#define DIO_SetPin(pin)   ( DIO_SetPinValue(pin, HIGH) )

/*******************************************************************************
 * @brief       Write LOW on the output pin.
 * @param[in]   pin:    The pin to be set LOW. See \ref DIO_PINS_t for options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Set LED 0 to LOW
 *              DIO_ClrPin(LED_0);
 *              @endcode
 ******************************************************************************/
#define DIO_ClrPin(pin)   ( DIO_SetPinValue(pin, LOW) )

/*******************************************************************************
 * @brief       Read the state of a pin
 * @param[in]   pin         the pin to be read. See \ref DIO_PINS_t for options.
 * @param[out]  ptrToState  the state of the pin. See \ref STATE_t for options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 *              - ptrToState is NULL.
 * @par         Example:
 *              @code 
 *              // Read the state of BUTTON 1
 *              DIO_ReadPin(BUTTON_1, &state); 
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_ReadPin(const DIO_PINS_t pin, STATE_t *ptrToState);

/*******************************************************************************
 * @brief       Toggle the state of a pin
 * @param[in]   pin      The pin to be toggled. See \ref DIO_PINS_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Toggle LED 0
 *              DIO_TogglePin(LED_0);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PINS_t pin);

/*******************************************************************************
 * @brief       Set or clear the pull-up resistor of a pin  
 * @param[in]   pin         The pin to be configured. See \ref DIO_PINS_t for
 * @param[in]   pullup      The pullup state of the pin. See \ref DIO_PULLUP_t for 
 *                          options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 *              - pullup is not a valid value.
 * @par         Example:
 *              @code 
 *              // Set pullup of BUTTON 1 to ON
 *              DIO_SetPinPullup(BUTTON_1, DIO_PULLUP_ON);
 * 
 *              // Set pullup of BUTTON 1 to OFF
 *              DIO_SetPinPullup(BUTTON_1, DIO_PULLUP_OFF);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetClrPinPullup(const DIO_PINS_t pin, const DIO_PULLUP_t pullup);

/*******************************************************************************
 * @brief       Enable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to enable its pullup resistor. 
 *                      See \ref DIO_PINS_t for options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Enable pullup of BUTTON 1
 *              DIO_SetPinPullup(BUTTON_1);
 *              @endcode
 ******************************************************************************/
#define DIO_SetPinPullup(pin)     ( DIO_SetClrPinPullup(pin, DIO_PULLUP_ON) )

/*******************************************************************************
 * @brief       Disable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to disable its pullup resistor. 
 *                      See \ref DIO_PINS_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Disable pullup of BUTTON 1
 *              DIO_ClrPinPullup(BUTTON_1);
 *              @endcode
 ******************************************************************************/
#define DIO_ClrPinPullup(pin)   ( DIO_SetClrPinPullup(pin, DIO_PULLUP_OFF) )

/*******************************************************************************
 * @brief       Write a value on a specific port (value of 8-bits ranges from 0 
 *              to 255)
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @param[in]   value: value to set on the port (8 bits --> 0-255)
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code 
 *              // Set port A to 0xFF. port A contains the LED_0 and MOTOR_0 pins
 *              DIO_SetPort(LED_0, 0xFF);  
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetPortValue(const DIO_PINS_t pinInThePort, const u8_t value);

/*******************************************************************************
 * @brief       Toggle the state of a port
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              // Toggle port A. port A contains the LED_0 and MOTOR_0 pins
 *              DIO_TogglePort(LED_0);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePort(const DIO_PINS_t pinInThePort);

/*******************************************************************************
 * @brief       Read the state of the port (8 bits --> 0-255)
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @param[out]  ptrToValue the value of the port (8 bits --> 0-255)
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 *              - The pointer is NULL      
 * @par         Example:
 *              @code 
 *              // Read the state of port A. port A contains the BUTTON_0 to 
 *              // BUTTON_7 pins
 *              DIO_ReadPort(BUTTON_0, &value);     // reads port A
 *              DIO_ReadPort(BUTTON_1, &value);     // reads port A
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_ReadPort(const DIO_PINS_t pinInThePort, u8_t * const ptrToValue);

/*******************************************************************************
 * @brief       Set or clear the pull-up resistor of a port
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @param[in]   pullup: The pullup state of the port. See \ref DIO_PULLUP_t for
 *                     options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 *              - pullup is not a valid value.
 * @par         Example:
 *              @code
 *              // Set pullup of port A to ON
 *              DIO_SetPortPullup(BUTTON_0, DIO_PULLUP_ON);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetClrPortPullup(const DIO_PINS_t pinInThePort, const DIO_PULLUP_t pullup);

/*******************************************************************************
 * @brief       Enable the internal pullup of a port
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Enable pullup of port A
 *              DIO_SetPortPullup(BUTTON_0);
 *              @endcode
 ******************************************************************************/
#define DIO_SetPortPullup(port)     ( DIO_SetClrPortPullup(pinInThePort, DIO_PULLUP_ON) )

/*******************************************************************************
 * @brief       Disable the internal pullup of a port
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Disable pullup of port A
 *              DIO_ClrPortPullup(BUTTON_0);
 *              @endcode
 ******************************************************************************/
#define DIO_ClrPortPullup(port)     ( DIO_SetClrPortPullup(pinInThePort, DIO_PULLUP_OFF) )

/*******************************************************************************
 * @brief       Set the direction of a port
 * @param[in]   pinInThePort: Any pin in the port. See \ref DIO_PINS_t for options.
 * @param[in]   direction: The direction of the port. See \ref DIO_DIR_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 *              - direction is not a valid value.
 * @par         Example:
 *              @code
 *              // Set direction of port A to DIO_INPUT
 *              DIO_SetPortDirection(BUTTON_0, DIO_INPUT);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetClrPortDirection(const DIO_PINS_t pinInThePort, const DIO_DIR_t direction);

/*******************************************************************************
 * @brief       Set a value on a nibble of a port
 * @param[in]   startPin: The first pin of the nibble. See \ref DIO_PINS_t for
 *              options.
 * @param[in]   value: The value to set on the nibble. The first 4 bits of the
 *                     value will be set on the nibble.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not configured in the configuration file.
 * @par         Example:
 *              @code
 *              // Set port A to 0xFF. port A contains LED_0 to LED_7 pins
 *              DIO_SetNibbleValue(LED_0, 0xF); // the first 4 bits of port A
 *              DIO_SetNibbleValue(LED_4, 0xF); // the last 4 bits of port A
 *              @endcode 
 ******************************************************************************/ 
ERROR_t DIO_SetNibbleValue(const DIO_PINS_t startPin, const u8_t value);

#endif      /* DIO_H */