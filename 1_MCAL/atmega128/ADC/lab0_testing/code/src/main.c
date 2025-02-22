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
	u16_t analogValue = 0;
	/* Initializations	*/
	DIO_Init();
	ADC_Init();
    CLCD_Init();
	
	while(1) {
		CLCD_Clr();
		/* Read Pot 1	*/
        ADC_Read(ADC_CHANNEL_GAS, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_1, 0);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 2	*/
		ADC_Read(ADC_CHANNEL_TEMP, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_1, 4);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 3	*/
		ADC_Read(ADC_CHANNEL_HUMIDITY, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_1, 8);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 4	*/
		ADC_Read(ADC_CHANNEL_PRESSURE, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_1, 12);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 5	*/
		ADC_Read(ADC_CHANNEL_WATTER, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_2, 0);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 6	*/
		ADC_Read(ADC_CHANNEL_LIGHT, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_2, 4);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 7	*/
		ADC_Read(ADC_CHANNEL_CAMERA, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_2, 8);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

		/* Read Pot 8	*/
		ADC_Read(ADC_CHANNEL_MICROPHONE, &analogValue);
		CLCD_SetCursorPosition(CLCD_LINE_2, 12);
		CLCD_WriteInteger(analogValue * (u32_t)100 / 1024);

        _delay_ms(200);
	}

	return 0;
}