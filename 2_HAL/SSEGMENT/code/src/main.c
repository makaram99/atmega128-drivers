#include <util/delay.h>
#include "STD_TYPES.h"
#include "DIO.h"
#include "SSEGMENT.h"

int main (void){   
	u8_t idx = 0;
	u8_t idx2 = 0;

	/* Initializations	*/
	DIO_Init();

	while (1){
		#if 0
		for(idx = 0; idx < 16; idx++){
			SSEGMENT_WriteDigit(SEGMENT0, idx);
			_delay_ms(700);
		}
		#elif 0
			SSEGMENT_WriteDigit(SEGMENT0, 0);
			_delay_ms(10);
			SSEGMENT_WriteDigit(SEGMENT1, 1);
			_delay_ms(10);
		#elif 1

			SSEGMENT_WriteNumber(12);
			_delay_ms(5000);

			/* Count from A to F	*/
			for(idx = 'A'; idx <= 'F'; idx++){
				
				/* delay between each count	*/
				for(idx2 = 0; idx2 < 50; idx2++){
					/* ones number on first segment	*/
					SSEGMENT_WriteChar(SEGMENT0, idx);
					_delay_ms(10);
					/* tens number on seconf segment	*/
					SSEGMENT_WriteChar(SEGMENT1, idx);
					_delay_ms(10);
				}
			}

			for(idx = 0; idx < 99; idx++){
				
				/* delay between each count	*/
				for(idx2 = 0; idx2 < 50; idx2++){
					/* ones number on first segment	*/
					SSEGMENT_WriteDigit(SEGMENT0, idx % 10);
					_delay_ms(10);
					/* tens number on seconf segment	*/
					SSEGMENT_WriteDigit(SEGMENT1, idx / 10);
					_delay_ms(10);
				}
			}
			
		#endif
	}
	
	return 0;                   
}                               
