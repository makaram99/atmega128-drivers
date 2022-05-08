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
 *           of the ports in the enum \ref PORT_t 
 ******************************************************************************/
static volatile u8_t * PORT_reg[NUM_OF_PORTS] = {
    &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG
};

/*******************************************************************************
 *  @brief Array of pointers to the DDR registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref PORT_t 
 ******************************************************************************/
static volatile u8_t * DDR_reg[NUM_OF_PORTS] = { 
    &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF, &DDRG
};

/*******************************************************************************
 *  @brief Array of pointers to the PIN registers
 *  @warning: The order of the ports in the array must be the same as the order
 *           of the ports in the enum \ref PORT_t 
 ******************************************************************************/
static volatile u8_t * PIN_reg[NUM_OF_PORTS] = {
    &PINA, &PINB, &PINC, &PIND, &PINE, &PINF, &PING
};


/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                              PUBLIC FUNCTIONS                               */
/*                                                                             */
/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * @details Initialize DIO pins to a specific direction (input or output), pullup 
 *          or not according to the configuration in the DIO_cfg.h file.  
 ******************************************************************************/
void DIO_Init(void) {
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if(INPUT == pinConfigs[i].direction) {                            
            CLR_BIT(*DDR_reg[pinConfigs[i].port], pinConfigs[i].pin);                    
                                                            
            if(PULLUP_TRUE == pinConfigs[i].pullup) {                     
                SET_BIT(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin);                         
            } else {                                          
                CLR_BIT(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin);                         
            }                                               
        } else if(OUTPUT == pinConfigs[i].direction) {                      
            SET_BIT(*DDR_reg[pinConfigs[i].port], pinConfigs[i].pin);                    
            CLR_BIT(*PORT_reg[pinConfigs[i].port], pinConfigs[i].pin);                             
        } else {     
            /* DEBUG: Invalid direction */                 
        }
    }
}

/*******************************************************************************
 * @details If:
 *          * DIO pin is not configured in the DIO_cfg.h file
 *          * Or the pin is configurations need to be modified
 *          Then, this function will be called to modify the pin configuration.
 ******************************************************************************/
void DIO_InitPin(const PIN_t pin, const PORT_t port, const DIR_t direction, const PULLUP_t pullup) {
    
    if(INPUT == direction) {                            
        CLR_BIT(*DDR_reg[port], pin);                    
                                                        
        if(PULLUP_TRUE == pullup) {                     
            SET_BIT(*PORT_reg[port], pin);                         
        } else {                                          
            CLR_BIT(*PORT_reg[port], pin);                         
        }                                               
    } else if(OUTPUT == direction) {                      
        SET_BIT(*DDR_reg[port], pin);                    
        CLR_BIT(*PORT_reg[port], pin);                             
    } else {     
        /* DEBUG: Invalid Direction    */            
    }
}

void DIO_SetPinPullup(const PIN_t pin, const PORT_t port, const PULLUP_t pullup) {
                                                 
    if(PULLUP_TRUE == pullup) {                     
        SET_BIT(*PORT_reg[port], pin);                         
    } else {                                          
        CLR_BIT(*PORT_reg[port], pin);                         
    }
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function 
 *          can be called to write to the pin (1 or 0).
 ******************************************************************************/
void DIO_WritePin(const PIN_t pin, const PORT_t port, const STATE_t state) {
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            if(LOW == state) {                                  
                CLR_BIT(*PORT_reg[port], pin);                             
            }else if(HIGH == state) {                           
                SET_BIT(*PORT_reg[port], pin);                             
            }else {     
                /* DEBUG: Invalid State */             
            }
        }
    }

    if(i == countPinsConfigured) {
        /* DEBUG: Invalid Pin */
    } else {
        /* Do nothing: pin exists */
    }
}

/*******************************************************************************
 * @details This function can be called to toggle the state of the pin. If the 
 *          pins state is HIGH, then it will be set to LOW, and vice versa.
 ******************************************************************************/
void DIO_TogglePin(const PIN_t pin, const PORT_t port) {
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            TOG_BIT(*PORT_reg[port], pin);
        } else {
            /* Do nothing: Check next pin */
        }
    }

    if(i == countPinsConfigured) {
        /* DEBUG: Invalid Pin */
    } else {
        /* Do nothing: pin exists */
    }
}

/*******************************************************************************
 * @details If the pin is configured in the DIO_cfg.h file, then this function
 *         can be called to read the pin (1 or 0).
 ******************************************************************************/
STATE_t DIO_ReadPin(const PIN_t pin, const PORT_t port) {
    STATE_t state = LOW;
    u8_t i = 0;

    for(i = 0; i < countPinsConfigured; ++i) {
        if( (pin == pinConfigs[i].pin) && (port == pinConfigs[i].port) ) {
            state = GET_BIT(*PIN_reg[port], pin);
        } else {
            /* Do nothing: Check next pin */
        }
    }

    if(i == countPinsConfigured) {
        /* DEBUG: Invalid Pin */
    } else {
        /* Do nothing: pin exists */
    }

    return state;
}

