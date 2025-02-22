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
/*                                  TYPEDEFS                                    */
/*------------------------------------------------------------------------------*/

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
    NUM_OF_PORTS    /*!< Number of ports: used for debugging */
}DIO_PORT_t;

/******************************************************************************
 * @brief   Enum for the directions of the pins.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 * @warning Values of each directions depends on the value written to the
 *          DDR register when configuring the pin as input or output.  
 *****************************************************************************/
typedef enum{
    DIO_INPUT = 0,  /*!< Input direction: Value depends on the input value in DDR register */
    DIO_OUTPUT = 1
}DIO_DIR_t;

/******************************************************************************
 * @brief   Enum for the pullup states of the pins.
 * @details This enum is used to be readable for the user instead of using 
 *          numbers while calling the functions.
 * @warning Values of each pullup states depends on the value written to the
 *          PORT register when configuring the pin as input or output.
 *****************************************************************************/
typedef enum{
    DIO_PULLUP_OFF = 0,
    DIO_PULLUP_ON = 1
}DIO_PULLUP_t;

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
    DIO_PIN_t       pin;
    DIO_PORT_t      port;
    DIO_DIR_t       direction;
    DIO_PULLUP_t    pullup;
}DIO_PIN_CONFIGS_t;

/******************************************************************************
 * @brief   This struct is used to pass the configuration of a port to the APIs
 *          of the DIO module.
 * @note    Members:
 *          - port: The port number. 
 *          - dir: The direction of the port.
 *          - pullup: The pullup state of the port.
 *****************************************************************************/
typedef struct{
    DIO_PORT_t      port;
    DIO_DIR_t       direction;
    DIO_PULLUP_t    pullup;
}PORT_CONFIGS_t;




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
 * 
 * @param[in]   pin   : The pin number. See \ref DIO_PIN_t for more information.
 * @param[in]   port  : The port number. See \ref DIO_PORT_t for more information.
 * @param[in]   dir   : The direction of the pin. See \ref DIO_DIR_t for more
 *                      information.
 * @param[in]   pullup: The pullup state of the pin. See \ref DIO_PULLUP_t for more
 *                      information.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              // Configure pin 0 of port A as output
 *              DIO_Init(DIO_PORT_A, DIO_PIN_0, DIO_OUTPUT, DIO_PULLUP_OFF);
 *  
 *              // Configure pin 1 of port A as input with pullup off
 *              DIO_Init(DIO_PORT_A, DIO_PIN_1, DIO_INPUT, DIO_PULLUP_OFF);
 *  
 *              // Configure pin 2 of port B as input with pullup on
 *              DIO_Init(DIO_PORT_B, DIO_PIN_2, DIO_INPUT, DIO_PULLUP_ON);   
 *              @endcode
 ******************************************************************************/
#define DIO_InitPin(pin, port, direction, pullup)                               \
        (                                                                       \
          DIO_SetPinDirection(&(DIO_PIN_CONFIGS_t){pin, port, direction, pullup}) | \
          DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){pin, port, direction, pullup})   \
        )

/*******************************************************************************
 * @brief       Initialize full port as input or output.
 * 
 * @param[in]   port: The port to be initialized: DIO_PORT_A ... DIO_PORT_G.
 * @param[in]   direction: The direction of the port: DIO_INPUT or DIO_OUTPUT.
 * @param[in]   pullup: The pullup of the port: DIO_PULLUP_ON or DIO_PULLUP_OFF.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              // Configure port A as output with pullup off
 *              PORT_CONFIGS_t portConfigs = {DIO_PORT_A, DIO_OUTPUT, DIO_PULLUP_ON };
 *              DIO_InitPort(&portConfigs);
 *
 *              // Configure port B as input with pullup off
 *              portConfigs.port = DIO_PORT_B;
 *              portConfigs.dir = DIO_INPUT;
 *              portConfigs.pullup = DIO_PULLUP_OFF;
 *              DIO_InitPort(&portConfigs);
 *
 *              // Configure port C as input with pullup on
 *              portConfigs.port = DIO_PORT_C;
 *              portConfigs.dir = DIO_INPUT;
 *              portConfigs.pullup = DIO_PULLUP_ON;
 *              DIO_InitPort(&portConfigs);
 *              @endcode
 ******************************************************************************/
#define DIO_InitPort(port, direction, pullup)           \
        (                                               \
          DIO_SetClrPortDirection(port, direction) |    \
          DIO_SetClrPortPullup(port, pullup)            \
        )

ERROR_t DIO_SetPinDirection(const DIO_PIN_CONFIGS_t * const pinConfigs);

ERROR_t DIO_SetClrPortDirection(const DIO_PORT_t port, const DIO_DIR_t direction);

/*******************************************************************************
 * @brief       Write HIGH OR LOW on the output pin, LOW to set set LOW, HIGH or
 *              any number to set HIGH.
 * @param[in]   pin:    The pin to be set LOW. See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to be set LOW. See \ref DIO_PORT_t for 
 *                      options.
 * @param[in]   state:  The state of the pin to be set. See \ref STATE_t for 
 *                      options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS) 
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code 
 *              // Set pin 0 of port A to HIGH
 *              DIO_SetPinValue(DIO_PIN_0, DIO_PORT_A, HIGH);   
 * 
 *              // Set pin 1 of port A to LOW
 *              DIO_SetPinValue(DIO_PIN_1, DIO_PORT_A, LOW);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PIN_t pin, const DIO_PORT_t port, const STATE_t state);

/*******************************************************************************
 * @brief       Write HIGH on the output pin.
 * @param[in]   pin:    The pin to be set HIGH. See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to be set HIGH. See \ref DIO_PORT_t for
 *                      options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code
 *              // Set pin 0 of port A to HIGH
 *              DIO_SetPinHigh(DIO_PIN_0, DIO_PORT_A);
 *              @endcode
 ******************************************************************************/
#define DIO_SetPin(pin, port)   ( DIO_SetPinValue(pin, port, HIGH) )

/*******************************************************************************
 * @brief       Write LOW on the output pin.
 * @param[in]   pin:    The pin to be set LOW. See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to be set LOW. See \ref DIO_PORT_t for
 *                      options.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code
 *              // Set pin 0 of port A to LOW
 *              DIO_ClrPin(DIO_PIN_0, DIO_PORT_A);
 *              @endcode
 ******************************************************************************/
#define DIO_ClrPin(pin, port)   ( DIO_SetPinValue(pin, port, LOW) )

/*******************************************************************************
 * @brief       Write a value on a specific port (value of 8-bits ranges from 0 
 *              to 255)
 * @param[in]   port: The port to be modified, DIO_PORT_A to DIO_PORT_G
 * @param[in]   value: value to set on the port (8 bits --> 0-255)
 * @par         Example:
 *              @code 
 *              // sets all pins of port A to high   (0xFF)
 *              DIO_SetPortValue(DIO_PORT_A, 0xFF); 
 * 
 *              // sets all pins of port A to low    (0x00)        
 *              DIO_SetPortValue(DIO_PORT_A, 0x00);            
 *              
 *              // sets pins 4, 5, 6, 7 of port A to high (0xF0)
 *              DIO_SetPortValue(DIO_PORT_A, 0xF0);     
 *              @endcode
 * @warning     If the pin is not configured in the DIO_cfg.h file, then this 
 *              function will do nothing.
 ******************************************************************************/
ERROR_t DIO_SetPortValue(const DIO_PORT_t port, const u8_t value);

/*******************************************************************************
 * @brief       Read the state of a pin
 * @param[in]   pin         the pin to be read. See \ref DIO_PIN_t for options.
 * @param[in]   port        the port of the pin to be read. See \ref DIO_PORT_t for 
 *                          options.
 * @param[out]  ptrToState    the state of the pin. See \ref STATE_t for options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 *              - The pointer is NULL
 * @par         Example:
 *              @code 
 *              // return the state of DIO_PIN_0 on PORT A
 *              DIO_ReadPin(DIO_PIN_0, DIO_PORT_A);            
 *              
 *              // return the state of PIN6 on PORT B 
 *              DIO_ReadPin(PIN6, DIO_PORT_B);            
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_ReadPin(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const ptrToState);

/*******************************************************************************
 * @brief       Read the state of the port (8 bits --> 0-255)
 * @param[in]   port the port to be read, DIO_PORT_A to DIO_PORT_G
 * @param[out]  ptrValue the value of the port (8 bits --> 0-255)
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The port is not exist (port >= NUM_OF_PORTS)
 *              - The pointer is NULL      
 * @par         Example:
 *              @code 
 *              // return 0xFF when all pins of PORT A are high
 *              DIO_ReadPort(DIO_PORT_A);         
 *              
 *              // return 0x00 when all pins of PORT A are low
 *              DIO_ReadPort(DIO_PORT_A);       
 *              
 *              // return 0xF0 when pins (4~7) of PORT A are high
 *              DIO_ReadPort(DIO_PORT_A);    
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_ReadPort(const DIO_PORT_t port, u8_t *const ptrValue);

/*******************************************************************************
 * @brief       Toggle the state of a pin
 * @param[in]   pin     The pin to be toggled. See \ref DIO_PIN_t for options.
 * @param[in]   port    The port of the pin to be toggled. See \ref DIO_PORT_t for
 *                      options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code
 *              // Toggle the state of DIO_PIN_0 on PORT A
 *              DIO_TogglePin(DIO_PIN_0, DIO_PORT_A); 
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PIN_t pin, const DIO_PORT_t port);

/*******************************************************************************
 * @brief       Toggle the state of a port
 * @param[in]   port the port to be toggled, DIO_PORT_A to DIO_PORT_G
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * @par         Example:
 *              @code
 *              DIO_TogglePort(DIO_PORT_A); // toggle the state of DIO_PORT_A
 *              DIO_TogglePort(DIO_PORT_A); // toggle the state of DIO_PORT_A
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_TogglePort(const DIO_PORT_t port);

/*******************************************************************************
 * @brief       Set the value of the low nibble of a port
 * @param[in]   port        The port to be modified. See \ref DIO_PORT_t for options.
 * @param[out]  value       The value of the port (8 bits --> 0-255)
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code 
 *              PORTA = 0xDC;
 *              // sets the low nibble of PORT A to 0xF
 *              DIO_SetLowNibble(DIO_PORT_A, 0xF);      // PORT A = 0xDF
 * 
 *              // sets the low nibble of PORT A to 0x0
 *              DIO_SetLowNibble(DIO_PORT_A, 0x0);      // PORT A = 0xD0
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetLowNibbleValue(const DIO_PORT_t port, const u8_t value);

/*******************************************************************************
 * @brief       Set the value of the high nibble of a port
 * @param[in]   port        The port to be modified. See \ref DIO_PORT_t for options.
 * @param[out]  value       The value of the port (8 bits --> 0-255)
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code 
 *              PORTA = 0xDC;
 *              // sets the high nibble of PORT A to 0xF
 *              DIO_SetHighNibble(DIO_PORT_A, 0xF);      // PORT A = 0xFC
 * 
 *              // sets the high nibble of PORT A to 0x0
 *              DIO_SetHighNibble(DIO_PORT_A, 0x0);      // PORT A = 0x0C
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetHighNibbleValue(const DIO_PORT_t port, const u8_t value);

/*******************************************************************************
 * @brief       Set the pull-up resistor of a port  
 * @param[in]   port        The port to be modified. See \ref DIO_PORT_t for options.
 * @param[in]   pullup      The pullup state of the port. See \ref DIO_PULLUP_t for 
 *                          options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The port is not exist (port >= NUM_OF_PORTS)
 *              - The pullup is not exist (not exist in the enum)
 * @par         Example:
 *              @code 
 *              // Enable the pull-up resistor of PORT A
 *              DIO_SetPinPullup(DIO_PORT_A, DIO_PULLUP_ON);
 *              
 *              // Disable the pull-up resistor of PORT A
 *              DIO_SetPinPullup(DIO_PORT_A, DIO_PULLUP_OFF);
 * 
 *              // Error: The pullup is not exist (not exist in the enum)
 *              DIO_SetPinPullup(DIO_PORT_A, DUMMY_VALUE);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetClrPinPullup(const DIO_PIN_CONFIGS_t * const pinConfigs);

ERROR_t DIO_SetClrPortPullup(const DIO_PORT_t port, const DIO_PULLUP_t pullup);

#define DIO_SetPortPullup(port)     ( DIO_SetClrPortPullup(port, DIO_PULLUP_ON) )

#define DIO_ClrPortPullup(port)     ( DIO_SetClrPortPullup(port, DIO_PULLUP_OFF) )

/*******************************************************************************
 * @brief       Set the pull-up resistor of a pin
 * @param[in]   pin         The pin to be modified. See \ref DIO_PIN_t for options.
 * @param[in]   port        The port of the pin to be modified. See \ref DIO_PORT_t 
 *                          for options.
 * @param[in]   pullup      The pullup state of the pin. See \ref DIO_PULLUP_t for 
 *                          options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 *              - The pullup is not exist (not exist in the enum)
 * @par         Example:
 *              @code 
 *              DIO_PIN_CONFIGS_t pinConfigs = {DIO_PIN_0, DIO_PORT_A, DIO_INPUT, DIO_PULLUP_ON };
 * 
 *              // Enable the pull-up resistor of DIO_PIN_0 on PORT A
 *              DIO_SetPinPullup(&pinConfigs);
 *              
 *              // Disable the pull-up resistor of DIO_PIN_0 on PORT A
 *              pinConfigs.pullup = DIO_PULLUP_OFF;
 *              DIO_SetPinPullup(DIO_PIN_0, DIO_PORT_A, DIO_PULLUP_OFF);
 * 
 *              // Error: The pullup is not exist (not exist in the enum)
 *              pinConfigs.pullup = DUMMY_VALUE;
 *              DIO_SetPinPullup(&pinConfigs);
 *              @endcode
 ******************************************************************************/
ERROR_t DIO_SetClrPinPullup(const DIO_PIN_CONFIGS_t * const pinConfigs);

/*******************************************************************************
 * @brief       Enable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to enable its pullup resistor. 
 *                      See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to enable its pullup resistor. 
 *                      See \ref DIO_PORT_t for options.
 * @return      ERROR_t:    Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code
 *              // Enable the pull-up resistor of DIO_PIN_0 on PORT A
 *              DIO_EnablePinPullup(DIO_PIN_0, DIO_PORT_A);
 *              @endcode
 ******************************************************************************/
#define DIO_SetPinPullup(pin, port)     \
        DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){pin, port, DIO_INPUT, DIO_PULLUP_ON})

/*******************************************************************************
 * @brief       Disable the internal pullup of a pin.
 * 
 * @param[in]   pin:    The pin to disable its pullup resistor. 
 *                      See \ref DIO_PIN_t for options.
 * @param[in]   port:   The port of the pin to disable its pullup resistor. 
 *                      See \ref DIO_PORT_t for options.
 * @return      ERROR_t: Error code. See \ref ERROR_t for more information.
 * PROTECTION:  This function will do nothing if:
 *              - The pin is not exist (pin >= NUM_OF_PINS)
 *              - The port is not exist (port >= NUM_OF_PORTS)
 * @par         Example:
 *              @code
 *              // Disable the pull-up resistor of DIO_PIN_0 on PORT A
 *              DIO_DisablePinPullup(DIO_PIN_0, DIO_PORT_A);
 *              @endcode
 ******************************************************************************/
#define DIO_ClrPinPullup(pin, port) \
        DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){pin, port, DIO_INPUT, DIO_PULLUP_OFF})

#endif      /* DIO_H */