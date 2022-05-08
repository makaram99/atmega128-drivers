/*/*****************************************************************************
 * @file            DIO.h
 * @author          Mahmoud Karam (ma.karam272@gmail.com)
 * @brief           Interace file for Digital Input Output (DIO) module for Atmega128 
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
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    NUM_OF_PINS
}PIN_t;

typedef enum{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_G,
    NUM_OF_PORTS
}PORT_t;

typedef enum{
    INPUT,
    OUTPUT
}DIR_t;

typedef enum{
    PULLUP_TRUE,
    PULLUP_FALSE
}PULLUP_t;

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                             API FUNCTIONS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 * @brief Initialize DIO configurations based on user configurations in DIO_cfg.h
 *        and DIO_cfg.c
 ******************************************************************************/
void DIO_Init();

/*******************************************************************************
 * @brief Initialize a pin as input or output.
 * @param[in] pin: The pin to be initialized: PIN_0 ... PIN_7
 * @param[in] port: The port of the pin: PORT_A ... PORT_G.
 * @param[in] direction: The direction of the pin: INPUT or OUTPUT.
 * @param[in] pullup: The pullup of the pin: PULLUP_TRUE or PULLUP_FALSE.
 ******************************************************************************/
void DIO_InitPin(const PIN_t pin, const PORT_t port, const DIR_t direction, 
                 const PULLUP_t pullup);

/*******************************************************************************
 * @brief Write a value on the output pins, options are defined in STD_TYPES.h 
 *        in the enum STATE_t
 * @param[in] pin: the pin to be initialized, PIN_0, PIN_1, ..., PIN_7
 * @param[in] port: the port of the pin to be initialized, PORT_A to PORT_G
 * @param[in] pinState: state of the pin, high or low, options are defined in 
 *            STD_TYPES.h in the enum STATE_t
 * @par Example:
 *  @code 
 *  DIO_WritePin(PIN_0, PORT_A, HIGH);     // turns on pin 0 of port A
 *  DIO_WritePin(PIN_0, PORT_A, LOW);      // turns off pin 0 of port A        
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this 
 *          function will do nothing.
 ******************************************************************************/
void DIO_WritePin(const PIN_t pin, const PORT_t port, const STATE_t pinState);

/*******************************************************************************
 * @brief Read the state of a pin
 * @param[in] pin the pin to be initialized, PIN_0, PIN_1, ..., PIN_7
 * @param[in] port the port of the pin to be initialized, PORT_A to PORT_G
 * @return state of the pin, HIGH or LOW
 * @par Example:
 *  @code 
 *  DIO_ReadPin(PIN_0, PORT_A);    // return the state of PIN_0 on PORT A       
 *  DIO_ReadPin(PIN6, PORT_B);    // return the state of PIN6 on PORT B       
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this function will do nothing.
 ******************************************************************************/
STATE_t DIO_ReadPin(const PIN_t pin, const PORT_t port);

/*******************************************************************************
 * @brief Toggle the state of a pin
 * @param[in] pin the pin to be toggled, PIN_0, PIN_1, ..., PIN_7
 * @param[in] port the port of the pin to be toggled, PORT_A to PORT_G
 * @par Example:
 *  @code
 *  DIO_TogglePin(PIN_0, PORT_A); // toggle the state of PIN_0 on PORT A
 *  DIO_TogglePin(PIN_0, PORT_A); // toggle the state of PIN_0 on PORT A
 *  @endcode
 * @warning If the pin is not configured in the DIO_cfg.h file, then this 
 *          function will do nothing.
 ******************************************************************************/
void DIO_TogglePin(const PIN_t pin, const PORT_t port);

#endif      /* DIO_H */