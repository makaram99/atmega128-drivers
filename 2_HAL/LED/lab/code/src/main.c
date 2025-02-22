#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "LED.h"


int main (void){   
	/* Initializations	*/
	DIO_Init();
	LED_Init();

	while(1) {
		#if 1	/* Testing Toggle function */
		LED_Toggle(LED_0);
		_delay_ms(500);

		#elif 1	/* Testing Read function */
		STATE_t state = LOW;
		LED_SetClr(LED_0, HIGH);
		LED_Read(LED_0, &state);
		if(state == HIGH) {
			LED_Toggle(LED_1);
			_delay_ms(1000);
		}

		#elif 1	/* Testing Write function */
		LED_Set(LED_0);
		_delay_ms(500);
		LED_Clr(LED_0);
		_delay_ms(500);

		#elif 1	/* Testing SetClr function */
		LED_SetClr(LED_0, HIGH);
		_delay_ms(500);
		LED_SetClr(LED_0, LOW);
		_delay_ms(500);
		#endif
	}
	
	return 0;                   
}