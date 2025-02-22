#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "SSEGMENT.h"
#include "SSEGMENT_cfg.h"

/**********************************************************************************
 * @brief   Equivalent codes for segment common cathode connection 
 * @note    This is used when no BCD IC is used 
 *********************************************************************************/
u8_t digitsConfigs[] = {
    0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100,             /* 0 ~ 4    */
    0b11011010, 0b11111010, 0b00001110, 0b11111110, 0b11011110,             /* 5 ~ 9    */
    0b11101110, 0b11111000, 0b10110000, 0b10111100, 0b11110011, 0b11100011  /* A ~ F    */
};

SSEGMENT_CONFIGS_t segmentsConfigs[] = {
    {SEGMENT0, DIO_PORT_A, COMMON_CATHODE, {DIO_PIN_6,DIO_PORT_C}},
    {SEGMENT1, DIO_PORT_A, COMMON_CATHODE, {DIO_PIN_7,DIO_PORT_C}},
};

u8_t countSegments = sizeof(segmentsConfigs) / sizeof(SSEGMENT_CONFIGS_t);
u8_t countDigits = sizeof(digitsConfigs) / sizeof(digitsConfigs[0]);
