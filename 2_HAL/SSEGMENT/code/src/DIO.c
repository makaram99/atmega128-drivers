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
/*                              PRIVATE DATA                                   */
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
/*                         PRIVATE FUNCTIONS PROTOTYPES                        */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
static ERROR_t DIO_SetClrPinPullup(const DIO_PIN_CONFIGS_t * const pinConfigs);
static STATE_t isPinConfigured(const DIO_PIN_t pin, const DIO_PORT_t port);

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
        error |= DIO_InitPin(&pinConfigs[i]);
    }

    return error;
}

/*******************************************************************************
 * @details If:
 *          * DIO pin is not configured in the DIO_cfg.h file
 *          * Or the pin is configurations need to be modified
 *          Then, this function will be called to modify the pin configuration.
 ******************************************************************************/
ERROR_t DIO_InitPin(const DIO_PIN_CONFIGS_t * const pinConfigs) {
    ERROR_t error = ERROR_OK;

    if( ( ASSERT_PIN(pinConfigs->pin))         && 
        ( ASSERT_PORT(pinConfigs->port))       && 
        ( ASSERT_DIR(pinConfigs->direction))   && 
        ( ASSERT_PULLUP(pinConfigs->pullup))        
      ) {

        /*!< Set direction  */
        BIT_CTRL(*DDR_reg[pinConfigs->port], pinConfigs->pin, pinConfigs->direction);

        /*!< Set pullup in case of input, or value in case of output    */
        BIT_CTRL(*PORT_reg[pinConfigs->port], pinConfigs->pin, pinConfigs->pullup);

    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_InitPort(const DIO_PORT_t port, const DIO_DIR_t direction, const DIO_PULLUP_t pullup) {
    ERROR_t error = ERROR_OK;

        /*!< Asserting parameters   */
    if( ( ASSERT_PORT(pinConfigs->port))       && 
        ( ASSERT_DIR(pinConfigs->direction))   && 
        ( ASSERT_PULLUP(pinConfigs->pullup))        
      ) {

        /*!< Set direction  */
        *DDR_reg[port] = direction * 0xff;

        /*!< Set pullup in case of input, or value in case of output    */
        *PORT_reg[port] = pullup * 0xff;
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function 
 *          can be called to write to the pin (1 or 0).
 ******************************************************************************/
ERROR_t DIO_SetPinValue(const DIO_PIN_t pin, const DIO_PORT_t port, const STATE_t state) {   
    ERROR_t error = ERROR_OK;

    if( ! isPinConfigured(pin, port)) {
        error |= ERROR_INVALID_PARAMETER;
    } else {
        BIT_CTRL(*PORT_reg[port], pin, state);
    }

    return error;
}

/*******************************************************************************
 * @details This function can be called to toggle the state of the pin. If the 
 *          pins state is HIGH, then it will be set to LOW, and vice versa.
 ******************************************************************************/
ERROR_t DIO_TogglePin(const DIO_PIN_t pin, const DIO_PORT_t port) {
    ERROR_t error = ERROR_OK;

    if( ! isPinConfigured(pin, port)) {
        error |= ERROR_INVALID_PARAMETER;
    } else {
        BIT_TOGGLE(*PORT_reg[port], pin);
    }

    return error;
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function
 *         can be called to read the pin (1 or 0).
 ******************************************************************************/
ERROR_t DIO_ReadPin(const DIO_PIN_t pin, const DIO_PORT_t port, STATE_t * const ptrToState) {
    ERROR_t error = ERROR_OK;

    if( ! isPinConfigured(pin, port)) {
        error |= ERROR_INVALID_PARAMETER;
    } else {
        *ptrToState = BIT_READ(*PIN_reg[port], pin);
    }

    return error;
}

ERROR_t DIO_SetPinPullup(const DIO_PIN_t pin, const DIO_PORT_t port) {
    ERROR_t error = ERROR_OK;
    
    error |= DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){pin, port, DIO_INPUT, DIO_PULLUP_ON});

    return error;
}

ERROR_t DIO_ClrPullup(const DIO_PIN_t pin, const DIO_PORT_t port) {
    ERROR_t error = ERROR_OK;
    
    error |= DIO_SetClrPinPullup(&(DIO_PIN_CONFIGS_t){pin, port, DIO_INPUT, DIO_PULLUP_OFF});

    return error;
}

ERROR_t DIO_SetPortValue(const DIO_PORT_t port, const u8_t value) {
    ERROR_t error = ERROR_OK;

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] = value;
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_TogglePort(const DIO_PORT_t port) {
    ERROR_t error = ERROR_OK;

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] = ~(*PORT_reg[port]);
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_SetLowNibbleValue(const DIO_PORT_t port, const u8_t value) {
    ERROR_t error = ERROR_OK;

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] |= (value & 0x0f);
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_SetHighNibbleValue(const DIO_PORT_t port, const u8_t value) {
    ERROR_t error = ERROR_OK;

    if(ASSERT_PORT(port)) {
        *PORT_reg[port] |= ( (value & 0x0f) << 4 );
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_ReadPort(const DIO_PORT_t port, u8_t *const ptrValue) {
    ERROR_t error = ERROR_OK;

    if((NULL == ptrValue)) {
        error |= ERROR_NULL_POINTER;
    } else if(ASSERT_PORT(port)) {
        *ptrValue = *PIN_reg[port];
    } else {
        error |= ERROR_INVALID_PARAMETER;
    }

    return error;
}

ERROR_t DIO_SetClrPortPullup(const DIO_PORT_t port, const DIO_PULLUP_t pullup) {
    ERROR_t error = ERROR_OK;

    if(ASSERT_PORT(port) && ASSERT_PULLUP(pullup)) {
        *PORT_reg[port] = (pullup ? 0xff : 0);
    } else {
        error |= ERROR_ILLEGAL_PARAM;
    }

    return error;
}

/*-----------------------------------------------------------------------------*/
/*                              PRIVATE FUNCTIONS                              */
/*-----------------------------------------------------------------------------*/
static ERROR_t DIO_SetClrPinPullup(const DIO_PIN_CONFIGS_t * const pinConfigs) {
    ERROR_t error = ERROR_OK;

    /*!< Asserting parameters   */
    if( ( !ASSERT_PIN(pinConfigs->pin))         || 
        ( !ASSERT_PORT(pinConfigs->port))       || 
        ( !ASSERT_PULLUP(pinConfigs->pullup))        
      ) {

        error |= ERROR_INVALID_PARAMETER;
    } else {
        BIT_CTRL(*PORT_reg[pinConfigs->port], pinConfigs->pin, pinConfigs->pullup);
    }

    return error;
}

static STATE_t isPinConfigured(const DIO_PIN_t pin, const DIO_PORT_t port) {
    u8_t i = 0;

    if( ( !ASSERT_PIN(pin)) || ( !ASSERT_PORT(port)) ) {
        return LOW;
    }

    for(i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            return HIGH;
        }
    }

    return LOW;
}




