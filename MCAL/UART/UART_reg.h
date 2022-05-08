/**************************************************************************
 * @file        UART_reg.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Registers of UART of ATmega328p MCU
 * @version     1.0.0
 * @date        2021-07-31
 **************************************************************************/
#ifndef UART_REG_H
#define UART_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/**************************************************************************
 *                                 UART0 Registers
 **************************************************************************/
#define UDR0        (* ((volatile u8_t *) 0x2C) )
#define UCSR0A      (* ((volatile u8_t *) 0x2B) )
#define UCSR0B      (* ((volatile u8_t *) 0x2A) )
#define UCSR0C      (* ((volatile u8_t *) 0x95) )
#define UBRR0L      (* ((volatile u8_t *) 0x29) )
#define UBRR0H      (* ((volatile u8_t *) 0x90) )

/**************************************************************************
 *                                UART1 Registers
 **************************************************************************/
#define UDR1        (* ((volatile u8_t *) 0x9C) )
#define UCSR1A      (* ((volatile u8_t *) 0x9B) )
#define UCSR1B      (* ((volatile u8_t *) 0x9A) )
#define UCSR1C      (* ((volatile u8_t *) 0x9D) )
#define UBRR1L      (* ((volatile u8_t *) 0x99) )
#define UBRR1H      (* ((volatile u8_t *) 0x98) )

/**************************************************************************
 *                                  Registers' Bits
 **************************************************************************/
enum {
    MPCM,  /* Multi-processor Communication Mode */
    U2X,   /* Double the UART transmission speed */
    UPE,   /* Parity Error */
    DOR,   /* Data OverRun */
    FE,    /* Framing Error */
    UDRE,  /* UART Data Register Empty */
    TXC,   /* UART Transmit Complete */
    RXC,   /* UART Receive Complete */
};  /* UCSRA: UART Control and Status Register A    */

enum {
    TXB8,  /* Transmit Data Bit 8 */
    RXB8,  /* Receive Data Bit 8 */
    UCSZ2, /* Character Size */
    TXEN,  /* Transmitter Enable */
    RXEN,  /* Receiver Enable */
    UDRIE, /* UART Data Register Empty Interrupt Enable */
    TXCIE, /* UART Transmit Complete Interrupt Enable */
    RXCIE, /* UART Receive Complete Interrupt Enable */
};  /* UCSRB: UART Control and Status Register B    */

enum {
    UCPOL, /* Clock Polarity */
    UCSZ0, /* Character Size */
    UCSZ1, /* Character Size */
    USBS,  /* Stop Bit Select */
    UPM0,  /* Parity Mode */
    UPM1,  /* Parity Mode */
    UMSEL, /* UART Mode Select */
};  /* UCSRC: UART Control and Status Register C    */

#endif    /* UART_REG_H */