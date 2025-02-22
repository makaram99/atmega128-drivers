/******************************************************************************
 * @file        DIO.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Digital Input Output (DIO) driver for Atmega128 microcontroller.
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_reg.h"
#include "DIO.h"
#include "DIO_cfg.h"



/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                      CHANGE THIS PART WITH NEW DEVICES                      */   
/*                                                                             */
/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 *  @brief Array of pointers to the port registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref DIO_PORT_t 
 ******************************************************************************/
static volatile u8_t * PORT_reg[NUM_OF_PORTS] = {
    &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG, 
};

/*******************************************************************************
 *  @brief Array of pointers to the DDR registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref DIO_PORT_t 
 ******************************************************************************/
static volatile u8_t * DDR_reg[NUM_OF_PORTS] = { 
    &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG,
};

/*******************************************************************************
 *  @brief Array of pointers to the PIN registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref DIO_PORT_t 
 ******************************************************************************/
static volatile u8_t * PIN_reg[NUM_OF_PORTS] = {
    &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING,
};

/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              MACRO LIKE FUNCTIONS                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
#define ASSERT_PIN(pin)          ((pin) < NUM_OF_PINS )
#define ASSERT_PORT(port)        ((port) < NUM_OF_PORTS )
#define ASSERT_DIR(direction)    ((direction == DIO_INPUT) || (direction == DIO_OUTPUT))
#define ASSERT_PULLUP(pullup)    ((pullup == DIO_PULLUP_ON) || (pullup == DIO_PULLUP_OFF))


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PUBLIC FUNCTIONS                               */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * @details Initialize DIO pins to a specific direction (input or output), pullup 
 *          or not according to the configuration in the DIO_cfg.h file.  
 ******************************************************************************/
ERROR_t DIO_Init(void) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        error |= DIO_InitPin(pinConfigs[i].name, pinConfigs[i].direction, pinConfigs[i].pullup);
    }

    return error;
}

ERROR_t DIO_SetPinDirection(const DIO_PINS_t name, const DIO_DIR_t direction) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == name) {
            if( ( ASSERT_PIN(pinConfigs[i].pin))         &&
                ( ASSERT_PORT(pinConfigs[i].port))       &&
                ( ASSERT_DIR(direction))        
            ) {
                BIT_CTRL(*DDR_reg[pinConfigs[i].port], pinConfigs[i].pin, direction);
                break;
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
        }
    }

    if(i == countPinsConfigured) {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function 
 *          can be called to write to the pin (1 or 0).
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PINS_t name, const STATE_t state) {  
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == name) {
            if( ( ASSERT_PIN(pinConfigs[i].pin))         &&
                ( ASSERT_PORT(pinConfigs[i].port))       &&
                ( ASSERT_DIR(pinConfigs[i].direction))        
            ) {
                BIT_CTRL(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin, state);
                break;
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
        }
    }


    return error;
}

/*******************************************************************************
 * @details This function can be called to toggle the state of the pin. If the 
 *          pins state is HIGH, then it will be set to LOW, and vice versa.
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PINS_t name) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == name) {
            if( ( ASSERT_PIN(pinConfigs[i].pin))         &&
                ( ASSERT_PORT(pinConfigs[i].port))       &&
                ( ASSERT_DIR(pinConfigs[i].direction))        
            ) {
                BIT_TOGGLE(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin);
                break;
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
        }
    }

    if(i == countPinsConfigured) {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_ReadPin(const DIO_PINS_t name, STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == name) {
            if( ( ASSERT_PIN(pinConfigs[i].pin)) && ( ASSERT_PORT(pinConfigs[i].port)) ) {
                *ptrToState = BIT_READ(*PIN_reg[pinConfigs[i].port], pinConfigs[i].pin);
                break;
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
        }
    }

    if(i == countPinsConfigured) {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_SetNibbleValue(const DIO_PINS_t startPinName, const u8_t value) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0, temp = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == startPinName) {
            if( ( ASSERT_PIN(pinConfigs[i].pin)) && ( ASSERT_PORT(pinConfigs[i].port)) ) {
                temp = *PORT_reg[pinConfigs[i].port] & (~(0xf << startPinName));
                *PORT_reg[pinConfigs[i].port] = temp | ((value & 0x0f) << startPinName);
                break;
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
        }
    }

    if(i == countPinsConfigured) {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_SetClrPinPullup(const DIO_PINS_t pin, const DIO_PULLUP_t pullup) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(pinConfigs[i].name == pin) {
            if( ( ASSERT_PIN(pinConfigs[i].pin))         &&
                ( ASSERT_PORT(pinConfigs[i].port))       &&
                ( ASSERT_PULLUP(pullup))        
            ) {
                BIT_CTRL(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin, pullup);
            } else {
                error |= ERROR_INVALID_PARAMETER;
            }
            break;
        }
    }

    if(i == countPinsConfigured) {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

