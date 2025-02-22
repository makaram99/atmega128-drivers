/*******************************************************************************
 * @file    ADC_reg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   ADC Registers of ATmega128 microcontroller.
 * @version 1.0.0
 * @warning When changing the microcontroller, make sure to:
 *          1. Add the new registers with their addresses to the ADC_reg.h file.
 *          3. Update the \ref ADC_CHANNEL_t in \ref ADC.h
 * @date    2022-06-26
 ******************************************************************************/
#ifndef ADC_REG_H
#define ADC_REG_H

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*              CHANGE THIS PART ONLY FOR NEW DEVICES                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

typedef struct {
    u8_t ADCL;
    u8_t ADCH;
    u8_t ADCSRA;
    u8_t ADMUX;
} ADC_REG_t;

volatile ADC_REG_t * ADC = (ADC_REG_t *)0x24;
#define SREG    (*(volatile u8_t *)0x5F)
#define I_BIT   (7U)

enum {
    MUX0,
    MUX1,
    MUX2,
    MUX3,
    MUX4,
    ADLAR,
    REFS0,
    REFS1,
};      /* ADMUX: ADC multiplexer select bits */

enum {
    ADPS0,
    ADPS1,
    ADPS2,
    ADIE,
    ADIF,
    ADFR,
    ADSC,
    ADEN,
};      /* ADCSRA: ADC control and status register A */

#endif    /* ADC_REG_H */