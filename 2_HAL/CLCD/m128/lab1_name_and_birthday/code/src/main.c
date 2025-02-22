/***************************************************************************
 * @file 	main.c
 * @author 	Mahmoud Karam Emara (ma.karam272@gmail.com)
 * @brief 	CLCD Lab1: Embedded Systems Foundation Diploma
 * @details Write a program to display your name on row 1, and birth date on 
 * 			row 2.
 * @version 1.0.0
 * @date 	2022-06-22
 * @copyright Mahmoud Karam Emara 2022, MIT License
 ***************************************************************************/

#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "CLCD.h"

int main (void){   
	DIO_Init();
	CLCD_Init();

	CLCD_WriteStringInXY("Mahmoud Karam", CLCD_LINE_1, 0);
	CLCD_WriteStringInXY("27 Feb 1999", CLCD_LINE_2, 0);
		
	while(1) {

	}

	return 0;
}