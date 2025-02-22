#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "CLCD.h"

int main (void){   
	/* Initializations	*/
	DIO_Init();
	CLCD_Init();

	while(1) {

		CLCD_WriteString("Hello World");
		_delay_ms(1000);

		CLCD_WriteStringInXY("Hello World", CLCD_LINE_2, 0);
		_delay_ms(1000);
		CLCD_Clr();
	}
	
	return 0;                   
}