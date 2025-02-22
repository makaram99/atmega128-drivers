/**
 * @file    main.c
 * @author  your name (you@domain.com)
 * @brief   Simple LED flashing program
 * @version 0.1
 * @date    2021-07-31
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "DIO_reg.h"
#include <util/delay.h>

int main(void) {
    STATE_t state = LOW;
    ERROR_t error = ERROR_OK;

    DIO_Init();

    while (1){
        #if 0   /* Flash LED    */
        /* Turn on LED  */
        DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, HIGH);   
        _delay_ms(100);

        /* Turn off LED  */
        DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, LOW);
        _delay_ms(100);

        #elif 1 /* Testing button with LED */

        error |= DIO_ReadPin(DIO_PIN_3, DIO_PORT_G, &state);

        if(state){
            DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, -50);
        }
        else{
            DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, LOW);
        }

        #elif 0 /* Testing pullup   */

        DIO_SetPinPullup(DIO_PIN_2, DIO_PORT_G);
        _delay_ms(100);
        DIO_ClrPullup(DIO_PIN_2, DIO_PORT_G);
        _delay_ms(100);

        #elif 1 /* Testing passing invalid parameters */

        error |= DIO_SetPinValue(10, DIO_PORT_G, HIGH);
        _delay_ms(100);
        error |= DIO_SetPinValue(10, DIO_PORT_G, LOW);
        _delay_ms(100);
        
        if(error == ERROR_INVALID_PARAMETER){
            DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, HIGH);
        }
        else{
            DIO_SetPinValue(DIO_PIN_4, DIO_PORT_G, LOW);
        }

        #endif
    }

    return 0;
}