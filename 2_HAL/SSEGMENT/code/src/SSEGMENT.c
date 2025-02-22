#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "SSEGMENT.h"
#include "SSEGMENT_cfg.h"

ERROR_t SSEGMENT_Init(void) {
    return ERROR_OK;
}

ERROR_t SSEGMENT_WriteDigit(const SSEGMENT_t segment, const u8_t digit) {
    ERROR_t error = ERROR_OK;
    u8_t i = 0, j = 0;

    /* Check if the segment is valid */
    for(i = 0; i < countSegments; i++){
        if(segment == segmentsConfigs[i].segment){
            break;
        }
    }

    if( (i >= countSegments) || (digit >= countDigits) ) {
        return ERROR_INVALID_PARAMETER;
    }
    
    #if POV_ENABLE
    /* Turn off enable pins of all segments    */
    for(j = 0; j < countSegments; ++j) {
        error |= DIO_SetPinValue(segmentsConfigs[j].enable.pin, segmentsConfigs[j].enable.port, LOW);
    }
    #else
    /* Turn off enable pin of the selected segment */
    error |= DIO_SetPinValue(segmentsConfigs[i].enable.pin, segmentsConfigs[i].enable.port, LOW);
    #endif

    /* Write the output value on segment port   */
    if(COMMON_ANODE == segmentsConfigs[i].anodeOrCathode) {
        DIO_SetPortValue(segmentsConfigs[i].port, ~digitsConfigs[digit]);
    } else if(COMMON_CATHODE == segmentsConfigs[i].anodeOrCathode) {
        DIO_SetPortValue(segmentsConfigs[i].port, digitsConfigs[digit]);
    } else {
        error |= ERROR_OUT_OF_RANGE;
    }

    /* Set enable pin of the segment    */
    DIO_SetPinValue(segmentsConfigs[i].enable.pin, segmentsConfigs[i].enable.port, HIGH);

    return error;
}

ERROR_t SSEGMENT_WriteChar(const SSEGMENT_t segment, const char ch) {
    ERROR_t error = ERROR_OK;

    error |= SSEGMENT_WriteDigit(segment, ch - 'A' + 10);

    return error;
}

ERROR_t SSEGMENT_WriteNumber(const u32_t number){
    ERROR_t error = ERROR_OK;
    u32_t temp = number;
    u8_t i = 0, j = 0;
	u8_t countDigits = 0;

    /* Check if the number is valid */
    if(number > 9999999) {
        return ERROR_INVALID_PARAMETER;
    }

    /* Count the number of digits in the number */
    while(temp > 0) {
        temp /= 10;
        ++countDigits;
    }

    #if POV_ENABLE
	/* delay between each count	*/
	for(j = 0; j < (1000 / (countDigits * 10)); ++j){
        temp = number;
        for(i = 0; i < countDigits; ++i){
            error |= SSEGMENT_WriteDigit(segmentsConfigs[i].segment, temp % 10);
            temp /= 10;
            _delay_ms(10);
        }
	}

    /* Turn off enable pins of all segments    */
    for(j = 0; j < countSegments; ++j) {
        error |= DIO_SetPinValue(segmentsConfigs[j].enable.pin, segmentsConfigs[j].enable.port, LOW);
    }
    #else
    for(i = 0; i < countDigits; ++i){
        error |= SSEGMENT_WriteDigit(segmentsConfigs[i].segment, temp % 10);
        temp /= 10;
    }
    #endif

    return error;
}

