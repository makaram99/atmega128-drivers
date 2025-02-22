/**************************************************************************
 * @file        DIO_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       DIO Registers of ATmega32 microcontroller.
 * @version     1.0.0
 * @date        2022-06-16
 * @copyright   Copyright (c) 2022
 **************************************************************************/
#ifndef DIO_REG_H
#define DIO_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#define PINA        (* ((volatile u8_t *) 0x39) )     /*!< Port A Input Pins */
#define DDRA        (* ((volatile u8_t *) 0x3A) )     /*!< Port A Data Direction Register */
#define PORTA       (* ((volatile u8_t *) 0x3B) )     /*!< Port A Data Register */

#define PINB        (* ((volatile u8_t *) 0x36) )     /*!< Port B Input Pins */
#define DDRB        (* ((volatile u8_t *) 0x37) )     /*!< Port B Data Direction Register */
#define PORTB       (* ((volatile u8_t *) 0x38) )     /*!< Port B Data Register */

#define PINC        (* ((volatile u8_t *) 0x33) )     /*!< Port C Input Pins */
#define DDRC        (* ((volatile u8_t *) 0x34) )     /*!< Port C Data Direction Register */
#define PORTC       (* ((volatile u8_t *) 0x35) )     /*!< Port C Data Register */

#define PIND        (* ((volatile u8_t *) 0x30) )     /*!< Port D Input Pins */
#define DDRD        (* ((volatile u8_t *) 0x31) )     /*!< Port D Data Direction Register */
#define PORTD       (* ((volatile u8_t *) 0x32) )     /*!< Port D Data Register */

#endif    /* DIO_REG_H */