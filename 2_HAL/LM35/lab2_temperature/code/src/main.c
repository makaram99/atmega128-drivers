/***************************************************************************
 * @file 	main.c
 * @author 	Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief 	Display the pressed key on the CLCD.
 * @details Write a program to display the pressed key from the keypad on the
 * 			CLCD. And also print the ASCII code of the pressed key on the CLCD.
 * 			For example, if the user presses the key 'A', the CLCD should display
 * 			the following:	
 * 				Key: A
 * 				ASCII: 65
 * @version 1.0.0
 * @date 	2022-06-22
 * @copyright Mahmoud Karam Emara 2022, MIT License
 ***************************************************************************/
#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "ADC.h"
#include "LM35.h"
#include "CLCD.h"

int main (void){   
	u16_t temperatureInBinary = 0;
    u8_t temperatureInCelsius = 0;
	/* Initializations	*/
	DIO_Init();
	ADC_Init();
    CLCD_Init();
    LM35_Init();

    CLCD_Clr();
    CLCD_ReturnHome();
    
	while(1) {
        CLCD_ReturnHome();
		
        LM35_Read(LM35_0, &temperatureInBinary);
        CLCD_WriteStringInXY("Binary: ", CLCD_LINE_1, 0);
        CLCD_WriteInteger(temperatureInBinary);

        if(temperatureInBinary < 10) {
            CLCD_WriteString("   ");
        } else if(temperatureInBinary < 100) {
            CLCD_WriteString("  ");
        } else if(temperatureInBinary < 1000) {
            CLCD_WriteString(" ");
        }

        temperatureInCelsius = (u8_t)( ((temperatureInBinary * 5.0f) / 1024) * 100 );
        CLCD_WriteStringInXY("Temp: ", CLCD_LINE_2, 0);
		CLCD_WriteInteger((s64_t)temperatureInCelsius);
        CLCD_WriteString(" C");
        if(temperatureInCelsius < 10) {
            CLCD_WriteString("  ");
        } else if(temperatureInCelsius < 100) {
            CLCD_WriteString(" ");
        }

        _delay_ms(400);
	}

	return 0;
}