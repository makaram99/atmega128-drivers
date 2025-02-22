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
#include "CLCD.h"

int main (void){   
	u16_t voltage = 0;
	/* Initializations	*/
	DIO_Init();
	ADC_Init();
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

        CLCD_WriteStringInXY("Voltage: ", CLCD_LINE_2, 0);
		CLCD_WriteFloat((voltage * 5.0f) / 1024, 2);
        CLCD_WriteString(" V");
        _delay_ms(400);
	}

	return 0;
}