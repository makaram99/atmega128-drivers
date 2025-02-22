#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "CLCD_commands.h"
#include "CLCD_cfg.h"
#include "CLCD.h"

CLCD_PINS_t CLCD_Pins = {
    .RS = DIO_PINS_CLCD_RS,
    #if CLCD_RW_PIN_USED
    .RW = DIO_PINS_CLCD_RW,
    #endif
    .E = DIO_PINS_CLCD_E,

    #if (!MODE_4_BITS_USED)
    .D0 = DIO_PINS_CLCD_D0,
    .D1 = DIO_PINS_CLCD_D1,
    .D2 = DIO_PINS_CLCD_D2,
    .D3 = DIO_PINS_CLCD_D3,
    #endif
    .D4 = DIO_PINS_CLCD_D4,
    .D5 = DIO_PINS_CLCD_D5,
    .D6 = DIO_PINS_CLCD_D6,
    .D7 = DIO_PINS_CLCD_D7
};


