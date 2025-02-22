/***************************************************************************
 * @file 	main.c
 * @author 	Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief 	Lab3: LM35 - Embedded Systems Foundation Diploma
 * @details Write a program the indicate the temperature using LCD and 3 LEDs:
 *          * If the reading (0> x < 50) 1 LED is turned on, 
 *          * If the reading (50> x < 100) 2 LEDs are turned on, 
 *          * If the reading (x > 100) 3 LEDs are turned on.
 * @version 1.0.0
 * @date 	2022-07-02
 * @copyright Mahmoud Karam Emara 2022, MIT License
 ***************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "ADC.h"
#include "LED.h"
#include "LM35.h"
#include "CLCD.h"

u8_t temperatureInCelsius = 0;

/**
 * "Read the potentiometer voltage, and when you're done, read it again."
 * 
 * The LM35_ReadAsync() function is a non-blocking function. It starts the LM35 conversion and returns
 * immediately. When the conversion is complete, the LM35_Notification() function is called
 */
void LM35_Notification(void) {
    LM35_ReadAsync(LM35_0, &temperatureInCelsius, LM35_Notification);
}

int main (void){       
	/* Initializations	*/
	DIO_Init();
    ADC_Init();
	LM35_Init();
    LED_Init();
    CLCD_Init();

    CLCD_Clr();
    CLCD_ReturnHome();

    LM35_ReadAsync(LM35_0, &temperatureInCelsius, LM35_Notification);
    
	/* The main loop of the program. It is responsible for updating the LCD and LEDs. */
    while(1) {
        CLCD_ReturnHome();
		
        CLCD_WriteStringInXY("Temp: ", CLCD_LINE_1, 0);
		CLCD_WriteInteger((s64_t)temperatureInCelsius);
        CLCD_WriteString(" C");
        if(temperatureInCelsius < 10) {
            CLCD_WriteString("  ");
        } else if(temperatureInCelsius < 100) {
            CLCD_WriteString(" ");
        }


        if(temperatureInCelsius < 50) {
            LED_Set(LED_0);
            LED_Clr(LED_1);
            LED_Clr(LED_2);
        } else if(temperatureInCelsius < 100) {
            LED_Set(LED_0);
            LED_Set(LED_1);
            LED_Clr(LED_2);
        } else {
            LED_Set(LED_0);
            LED_Set(LED_1);
            LED_Set(LED_2);
        }
	}

	return 0;
}

