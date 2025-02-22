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
} DIO_PINS_t;

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
#define DIO_InitPin(pin, direction, pullup)                               \
        (                                                                       \
          DIO_SetPinDirection(pin, direction) | \
          DIO_SetClrPinPullup(pin, pullup)   \
        )

ERROR_t DIO_SetPinDirection(const DIO_PINS_t name, const DIO_DIR_t direction);

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
ERROR_t DIO_SetPinValue(const DIO_PINS_t name, const STATE_t state);

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
#define DIO_SetPin(pin)   ( DIO_SetPinValue(pin, HIGH) )

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
#define DIO_ClrPin(pin)   ( DIO_SetPinValue(pin, LOW) )

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
ERROR_t DIO_ReadPin(const DIO_PINS_t pin, STATE_t *ptrToState);

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
ERROR_t DIO_TogglePin(const DIO_PINS_t pin);

ERROR_t DIO_SetNibbleValue(const DIO_PINS_t startPin, const u8_t value);

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
ERROR_t DIO_SetClrPinPullup(const DIO_PINS_t pin, const DIO_PULLUP_t pullup);

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
#define DIO_SetPinPullup(pin)     \
        DIO_SetClrPinPullup(pin, DIO_PULLUP_ON)

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
#define DIO_ClrPinPullup(pin) \
        DIO_SetClrPinPullup(pin, DIO_PULLUP_OFF)

#endif      /* DIO_H */