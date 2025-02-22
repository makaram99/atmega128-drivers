#include "util/delay.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "KEYPAD.h"

/*----------------------------------------------------------------*/
/* Test Functions                                                 */
/*----------------------------------------------------------------*/
void UpdateKeypad(void);
void TestKeypadInit(void);


/*----------------------------------------------------------------*/
/* Tasks Functions                                                */
/*----------------------------------------------------------------*/
void taskKeyPad(void*pv);

/*----------------------------------------------------------------*/
/* Keypad Global Variables                                        */
/*----------------------------------------------------------------*/
#define MAX  4
u8_t PASSWORD[MAX] = {'1','2','3','4'};
u8_t PASSWORD_FLAG = 0;
u8_t BUZZER_FLAG = 0;

int main (void){   
	/* Initializations	*/
	DIO_Init();
	KEYPAD_Init();

	TestKeypadInit();

	while(1) {
		UpdateKeypad();
	}
	
	return 0;                   
}                               

/*----------------------------------------------------------------*/
/* Keypad Functions                                               */
/*----------------------------------------------------------------*/

void TestKeypadInit(void) {
	DIO_SetPinValue(DIO_PIN_3, DIO_PORT_C, HIGH);
	_delay_ms(1000);
	DIO_TogglePin(DIO_PIN_3, DIO_PORT_C);
}

void UpdateKeypad(void) {
	taskKeyPad(NULL);

	DIO_SetPinValue(DIO_PIN_3, DIO_PORT_C, PASSWORD_FLAG);
}

void taskKeyPad(void*pv)
{
	static u8_t i = 0, val = 0;
	static u8_t password [MAX] = {0};

	KEYPAD_Read(&val);

	if(val) {
		password[i] = val;
		++i;

		if(MAX == i) {
			for(i = 0; i < MAX; ++i) {
				if(password[i] != PASSWORD[i]) {
					break;
				}
			}

			if(i == MAX) {
				PASSWORD_FLAG = 1;
			} else {
				BUZZER_FLAG = 1;
				PASSWORD_FLAG = 0;
			}

			i = 0;
		}
	}
}
