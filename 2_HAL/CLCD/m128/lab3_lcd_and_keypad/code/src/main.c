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
#include "CLCD.h"
#include "KEYPAD.h"

int main (void){   
	u8_t u8_keypad_value = 0;
	/* Initializations	*/
	DIO_Init();
	CLCD_Init();
	KEYPAD_Init();

	CLCD_Clr();
	CLCD_ReturnHome();

	CLCD_WriteString("Welcome to");
	CLCD_WriteFloat(3.1400, 2);

	CLCD_CursorBlinkOn();
	
	while(1) {
		KEYPAD_Read(KEYPAD_0, &u8_keypad_value);

		if(u8_keypad_value != 0) {
			CLCD_Clr();
			CLCD_ReturnHome();
			CLCD_WriteStringInXY("Key: ", CLCD_LINE_1, 0);
			CLCD_WriteChar(u8_keypad_value);

			CLCD_WriteStringInXY("ASCII: ", CLCD_LINE_2, 0);
			CLCD_WriteInteger(u8_keypad_value);

			u8_keypad_value = 0;

			CLCD_CursorBlinkOff();
		}
	}

	return 0;
}