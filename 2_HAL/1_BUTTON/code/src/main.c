#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "LED.h"
#include "BUTTON.h"


int main (void){   
	/* Initializations	*/
	DIO_Init();
	LED_Init();
	BUTTON_Init();

	STATE_t state;
	while(1) {
		#if 0	/* Testing BUTTON_Read() */
			BUTTON_Read(BUTTON_0, &state);
			if(state == HIGH) {
				LED_Set(LED_0);
			} else {
				LED_Clr(LED_0);
			}

			BUTTON_Read(BUTTON_1, &state);
			if(state == HIGH) {
				LED_Set(LED_1);
			} else {
				LED_Clr(LED_1);
			}

		#elif 0	/* Testing SetClrPullup	*/
			BUTTON_SetClrPullup(BUTTON_2, DIO_PULLUP_ON);
			BUTTON_SetClrPullup(BUTTON_3, DIO_PULLUP_OFF);
			_delay_ms(1000);
			BUTTON_SetClrPullup(BUTTON_2, DIO_PULLUP_OFF);
			BUTTON_SetClrPullup(BUTTON_3, DIO_PULLUP_ON);
			_delay_ms(1000);
			BUTTON_SetClrPullup(BUTTON_2, DIO_PULLUP_ON);
			BUTTON_SetClrPullup(BUTTON_3, DIO_PULLUP_ON);
			_delay_ms(1000);
			BUTTON_SetClrPullup(BUTTON_2, DIO_PULLUP_OFF);
			BUTTON_SetClrPullup(BUTTON_3, DIO_PULLUP_OFF);
			_delay_ms(1000);
		
		#elif 1	/* Testing SetPullup and ClrPullup	*/
			BUTTON_ClrPullup(BUTTON_2);
			BUTTON_ClrPullup(BUTTON_3);
			_delay_ms(1000);
			BUTTON_SetPullup(BUTTON_2);
			BUTTON_ClrPullup(BUTTON_3);
			_delay_ms(1000);
			BUTTON_ClrPullup(BUTTON_2);
			BUTTON_SetPullup(BUTTON_3);
			_delay_ms(1000);
			BUTTON_SetPullup(BUTTON_2);
			BUTTON_SetPullup(BUTTON_3);
			_delay_ms(1000);
		#endif
	}
	
	return 0;                   
}