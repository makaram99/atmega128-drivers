/***************************************************************************
 * @file 	main.c
 * @author 	Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief 	CLCD Lab1: Embedded Systems Foundation Diploma
 * @details Write a program to display a counter value, The counter shall 
 * 			increase with every press on a push button, If the counter
 * 			reaches 30, CLCD shall clear and start counting from zero.
 * @version 1.0.0
 * @date 	2022-06-22
 * @copyright Mahmoud Karam Emara 2022, MIT License
 ***************************************************************************/

#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "CLCD.h"
#include "BUTTON.h"

int main (void){   
	STATE_t buttonState = LOW;
	u8_t counter = 0;

	DIO_Init();
	CLCD_Init();
	BUTTON_Init();


	CLCD_WriteString("Counter: ");
	CLCD_WriteInteger(counter);
		
	while(1) {
		BUTTON_Read(BUTTON_0, &buttonState);

		if(HIGH == buttonState) {
			do {
				BUTTON_Read(BUTTON_0, &buttonState);
			} while(HIGH == buttonState);
	
			++counter;

			if(counter > 30) {
				counter = 0;
				CLCD_WriteStringInXY("  ", CLCD_LINE_1, 9);
			}
	
			CLCD_WriteIntegerInXY(counter, CLCD_LINE_1, 9);

			buttonState = LOW;
		}

	}

	return 0;
}