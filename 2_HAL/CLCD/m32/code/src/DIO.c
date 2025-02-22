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
    &PORTA, &PORTB, &PORTC, &PORTD,
};

/*******************************************************************************
 *  @brief Array of pointers to the DDR registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref DIO_PORT_t 
 ******************************************************************************/
static volatile u8_t * DDR_reg[NUM_OF_PORTS] = { 
    &DDRA, &DDRB, &DDRC, &DDRD,
};

/*******************************************************************************
 *  @brief Array of pointers to the PIN registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref DIO_PORT_t 
 ******************************************************************************/
static volatile u8_t * PIN_reg[NUM_OF_PORTS] = {
    &PINA, &PINB, &PINC, &PIND,
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
        error |= DIO_InitPin(pinConfigs[i].pin, pinConfigs[i].port, pinConfigs[i].direction, pinConfigs[i].pullup);
    }

    return error;
}

ERROR_t DIO_SetPinDirection(const DIR_CONFIGS_t * const dirConfigs) {

    if( ( ASSERT_PIN(dirConfigs->pin))         &&
        ( ASSERT_PORT(dirConfigs->port))       &&
        ( ASSERT_PULLUP(dirConfigs->direction))        
      ) {
        BIT_CTRL(*DDR_reg[dirConfigs->port], dirConfigs->pin, dirConfigs->direction);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function 
 *          can be called to write to the pin (1 or 0).
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PIN_t pin, const DIO_PORT_t port, const STATE_t state) {   

    if( ASSERT_PIN(pin) && ASSERT_PORT(port) ) {
        BIT_CTRL(*PORT_reg[port], pin, state);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

/*******************************************************************************
 * @details This function can be called to toggle the state of the pin. If the 
 *          pins state is HIGH, then it will be set to LOW, and vice versa.
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PIN_t pin, const DIO_PORT_t port) {

    if( ASSERT_PIN(pin) && ASSERT_PORT(port) ) {
        BIT_TOGGLE(*PORT_reg[port], pin);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_ReadPin(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const ptrToState) {

    if( ASSERT_PIN(pin) && ASSERT_PORT(port) && (ptrToState != NULL) ) {
        *ptrToState = BIT_READ(*PIN_reg[port], pin);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetPortValue(const DIO_PORT_t port, const u8_t value) {

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] = value;
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_TogglePort(const DIO_PORT_t port) {

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] = ~(*PORT_reg[port]);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetLowNibbleValue(const DIO_PORT_t port, const u8_t value) {
    u8_t temp = 0;

    if(ASSERT_PORT(port)) {
        temp = *PORT_reg[port] & (~(0xf));
        *PORT_reg[port] = temp | (value & 0xf);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetHighNibbleValue(const DIO_PORT_t port, const u8_t value) {
    u8_t temp = 0;

    if(ASSERT_PORT(port)) {
        temp = *PORT_reg[port] & (~(0xf0));
        *PORT_reg[port] = temp | ((value << 4) & 0xf0);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetNibbleValue(const DIO_PIN_t startPin, const DIO_PORT_t port, const u8_t value) {
    u8_t temp = 0;

    if(ASSERT_PORT(port) && ASSERT_PIN(startPin)) {
        temp = *PORT_reg[port] & (~(0xf << startPin));
        *PORT_reg[port] = temp | ((value & 0x0f) << startPin);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_ReadPort(const DIO_PORT_t port, u8_t *const ptrValue) {

    if((NULL == ptrValue)) {
        return ERROR_NULL_POINTER;
    } 
    
    if(ASSERT_PORT(port)) {
        *ptrValue = *PIN_reg[port];
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetClrPortPullup(const DIO_PORT_t port, const DIO_PULLUP_t pullup) {

    if(ASSERT_PORT(port) && ASSERT_PULLUP(pullup)) {
        *PORT_reg[port] = (pullup ? 0xff : 0);
    } else {
        return ERROR_ILLEGAL_PARAM;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetClrPortDirection(const DIO_PORT_t port, const DIO_DIR_t direction) {

    if(ASSERT_PORT(port) && ASSERT_DIR(direction)) {
        *DDR_reg[port] = (direction ? 0xff : 0);
    } else {
        return ERROR_ILLEGAL_PARAM;
    }

    return ERROR_OK;
}

ERROR_t DIO_SetClrPinPullup(const PUD_CONFIGS_t * const pullupConfigs) {

    /*!< Asserting parameters   */
    if( ( ASSERT_PIN(pullupConfigs->pin))         &&
        ( ASSERT_PORT(pullupConfigs->port))       &&
        ( ASSERT_PULLUP(pullupConfigs->pullup))        
      ) {
        BIT_CTRL(*PORT_reg[pullupConfigs->port], pullupConfigs->pin, pullupConfigs->pullup);
    } else {
        return ERROR_INVALID_PARAMETER;
    }

    return ERROR_OK;
}

