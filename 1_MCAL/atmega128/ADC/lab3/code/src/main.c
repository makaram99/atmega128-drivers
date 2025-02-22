/***************************************************************************
 * @file 	main.c
 * @author 	Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief 	Lab3: ADC - Embedded Systems Foundation Diploma
 * @details Write a program the indicate the voltage level using 3 LEDs and 
 *          a potentiometer:
 *          * If the reading (0> x < 300) 1 LED is turned on, 
 *          * If the reading (300> x < 600) 2 LEDs are turned on, 
 *          * If the reading (x > 600) 3 LEDs are turned on.
 * @version 1.0.0
 * @date 	2022-06-27
 * @copyright Mahmoud Karam Emara 2022, MIT License
 ***************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "ADC.h"
#include "LED.h"
#include "CLCD.h"

int main (void){   
	u16_t voltage = 0;
	/* Initializations	*/
	DIO_Init();
	ADC_Init();
    LED_Init();
    CLCD_Init();

    CLCD_Clr();
    CLCD_ReturnHome();
    
	while(1) {
        CLCD_ReturnHome();
		
        ADC_Read(ADC_CHANNEL_POTENTIOMETER, &voltage);
        CLCD_WriteStringInXY("Binary: ", CLCD_LINE_1, 0);
        CLCD_WriteIntegerInXY(voltage, CLCD_LINE_1, 8);
        if(voltage < 10) {
            CLCD_WriteString("   ");
        } else if(voltage < 10) {
            CLCD_WriteString("  ");
        } else if(voltage < 1000) {
            CLCD_WriteString(" ");
        }

        if(voltage < 300) {
            LED_Set(LED_0);
            LED_Clr(LED_1);
            LED_Clr(LED_2);
        } else if(voltage < 600) {
            LED_Set(LED_0);
            LED_Set(LED_1);
            LED_Clr(LED_2);
        } else {
            LED_Set(LED_0);
            LED_Set(LED_1);
            LED_Set(LED_2);
        }
        
        _delay_ms(100);
	}

	return 0;
}