/****************************************************************************************
 * @file        EXTI.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       External Interrupts (EXTI) driver for Atmega128 microcontroller.
 * @version     1.0.0
 * @date        2022-02-05
 * @details There are two types of interrupts:
 *             1. Interrupts that are generated by the peripheral (HW interrupt).
 *             2. Interrupts that are generated by the application (SW interrupt).
 *             The application can generate interrupts by calling the function
 *              EXTI_GenerateSWInterrupt().
 *            The peripheral can generate interrupts by calling the function
 *             EXTI_GenerateHWInterrupt().
 *           The application can clear the interrupt by calling the function
 *            EXTI_ClearSWInterrupt().
 *           
 *          There are 4 modes of interrupt generation:
 *              1. Interrupt on falling edge.
 *              2. Interrupt on rising edge.
 *              3. Interrupt on both edges (On Change).
 *              4. Interrupt on active level.
 *          When edge triggered, the interrupt is triggered only once when a 
 *          falling edge from high logic level to low logic level happens. 
 *          Only once even if the signal stays low, or goes high again.
 *          But when level triggered, the interrupt is triggered repeatedly while 
 *          the logic level is low, continuously, until the logic level goes high again.
 *          So you really don't want to re-enable interrupts in a ISR which is 
 *          triggered on low level. And if the level is low, not much mainline code 
 *          gets chance to run, because the ISR is run repeatedly.
 *          So yes, basically low level and falling edge types of interrupts are 
 *          both triggered when signal goes from high to low. Difference is that 
 *          other gets triggered only once at the falling edge, the other triggers 
 *          constantly while the level is low.
 * @note    INT0 to INT3 do not have (On Change mode)
 * @note    INT4 to INT7 need IO clock if configured as edge triggered.
 * @note    INT0 to INT3 use Asynchronous clock. So, they can wake up the MCU from 
 *          sleep mode at any mode.
 * @todo    Debug configuration of INT4 to INT7 as edge triggered not working.
 * 
 * @copyright   Copyright (c) 2022
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_reg.h"
#include "SREG.h"
#include "GIE.h"
#include "EXTI.h"
#include "EXTI_cfg.h"

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                      PRIVATE FUNCTIONS PROTOTYPES                          */
/*                                                                            */                              
/*----------------------------------------------------------------------------*/
static void EXTI_SetSensitivity(EXTI_t extiNumber, EXTI_SENSITIVITY_t sensitivity);
static void EXTI_SetCallback(EXTI_t extiNumber, void (* callbackPtr)(void));
static void ISR_Generic(EXTI_t extiNumber);

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                              CALLBACKS                                   */
/*                                                                          */
/*--------------------------------------------------------------------------*/
static void (* ( EXTI_callbackPtr[NUM_OF_EXTI_CHANNELS] ))(void);

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                          PUBLIC FUNCTIONS                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/******************************************************************************
 * @details Initialize an external interrupt pin as input pin and set the 
 *****************************************************************************/
void EXTI_Init(const EXTI_t extiNumber, const EXTI_SENSITIVITY_t  sensitivity, void (* const callbackPtr)(void)) {
    /* Disabling global interrupt flag  */
    GIE_Disable();       /* cli()    */

    EXTI_SetSensitivity(extiNumber, sensitivity);

    /* Enabling interrupt   */
    EXTI_EnableExternalInterrupt(extiNumber);

    /* Setting callback function   */
    EXTI_SetCallback(extiNumber, callbackPtr);

    /* Enabling global interrupt flag  */
    GIE_Enable();    /* sei  */
}

/******************************************************************************
 * @details Enable external interrupt pin
 *****************************************************************************/
void EXTI_EnableExternalInterrupt(const EXTI_t extiNumber) {
    GIE_Disable();
    
    if(NUM_OF_EXTI_CHANNELS > extiNumber) {
        /*!< Clear interrupt flag */
        BIT_SET(EIFR, extiNumber);      /*!< BIT = INTF0, INTF1, ..., INTF7 */

        /*!< Enable interrupt */
        BIT_SET(EIMSK, extiNumber);     /*!< BIT = INT0, INT1, ..., INT7 */
    } else {
        /* DEBUG    */
    }

    GIE_Enable();
}

void EXTI_DisableExternalInterrupt(const EXTI_t extiNumber) {
    GIE_Disable();

    if(NUM_OF_EXTI_CHANNELS > extiNumber) {
        BIT_CLR(EIMSK, extiNumber);     /*!< BIT = INT0, INT1, ..., INT7 */
    } else {
        /* DEBUG    */
    }

    GIE_Enable();
}


/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                           PRIVATE FUNCTIONS                                */
/*                                                                            */                              
/*----------------------------------------------------------------------------*/

static void EXTI_SetSensitivity(const EXTI_t extiNumber, const EXTI_SENSITIVITY_t sensitivity) {
    u8_t ISCx0 = 0, ISCx1 = 0;    
    u8_t eimsk = EIMSK;

    EIMSK = 0;                      /*!< Disable interrupts */

    ISCx0 = (extiNumber % 4) * 2;   /*!< ISCx0 = ISC00, ISC10, ISC20, ISC30, ISC40, ISC50, ISC60, ISC70 */
    ISCx1 = ISCx0 + 1;              /*!< ISCx1 = ISC01, ISC11, ISC21, ISC31, ISC41, ISC51, ISC61, ISC71 */

    switch(extiNumber) {
        case EXTI_0:
        case EXTI_1:
        case EXTI_2:
        case EXTI_3:
        {
            if(LOW_LEVEL_DETECT == sensitivity) {
                BIT_CLR(EICRA, ISCx0);
                BIT_CLR(EICRA, ISCx1);
            }else if(RISING_EDGE == sensitivity) {
                BIT_SET(EICRA, ISCx0);
                BIT_SET(EICRA, ISCx1);
            }else if(FALLING_EDGE == sensitivity) {
                BIT_CLR(EICRA, ISCx0);
                BIT_SET(EICRA, ISCx1);
            }else {
                /* DEBUG    */
            }
            break;
        }

        case EXTI_4: 
        case EXTI_5: 
        case EXTI_6: 
        case EXTI_7:
        {
            if(LOW_LEVEL_DETECT == sensitivity) {
                BIT_CLR(EICRB, ISCx0);
                BIT_CLR(EICRB, ISCx1);

            }else if(LOGIC_CHANGE == sensitivity) {
                BIT_SET(EICRB, ISCx0);
                BIT_CLR(EICRB, ISCx1);

            }else if(RISING_EDGE == sensitivity) {
                BIT_SET(EICRB, ISCx0);
                BIT_SET(EICRB, ISCx1);

            }else if(FALLING_EDGE == sensitivity) {
                BIT_CLR(EICRB, ISCx0);
                BIT_SET(EICRB, ISCx1);

            }else {
                /* DEBUG    */
            }
            break;
        }
        default:
            /* DEBUG    */
            break;
    }

    (EIMSK) |= eimsk;           /*!< Enable interrupts */
}

static void EXTI_SetCallback(const EXTI_t extiNumber, void (* const const callbackPtr)(void)) {
    
    if( (NULL != callbackPtr) && (NUM_OF_EXTI_CHANNELS > extiNumber) ) {
        EXTI_callbackPtr[extiNumber] = callbackPtr;
    } else {
        /* DEBUG    */
    }
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                            ISR FUNCTIONS                                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/

static void ISR_Generic(const EXTI_t extiNumber) {

    #if(NESTING == NESTING_DISABLED)
    GIE_Disable();
    #endif

    BIT_SET(EIFR, extiNumber);      /*!< Clear interrupt flag */

    if( (NUM_OF_EXTI_CHANNELS > extiNumber) && (NULL != EXTI_callbackPtr[extiNumber]) ) {
        (EXTI_callbackPtr[extiNumber])();
    }else {
        /* DEBUG    */
    }

    #if(NESTING == NESTING_DISABLED)
    GIE_Enable();
    #endif
}

/*!< ISR of INT0                      */
void __vector_1(void) __attribute__((signal));
void __vector_1(void) {

    ISR_Generic(EXTI_0);
}

/*!< ISR of INT1        */
void __vector_2(void) __attribute__((signal));
void __vector_2(void) {
    
    ISR_Generic(EXTI_1);
}

/*!< ISR of INT2                      */
void __vector_3(void) __attribute__((signal));
void __vector_3(void) {
    
    ISR_Generic(EXTI_2);
}

/*!< ISR of INT3                      */
void __vector_4(void) __attribute__((signal));
void __vector_4(void) {
    
    ISR_Generic(EXTI_3);
}

/*!< ISR of INT4                      */
void __vector_5(void) __attribute__((signal));
void __vector_5(void) {
    
    ISR_Generic(EXTI_4);
}

/*!< ISR of INT5                      */
void __vector_6(void) __attribute__((signal));
void __vector_6(void) {
    
    ISR_Generic(EXTI_5);
}

/*!< ISR of INT6                      */
void __vector_7(void) __attribute__((signal));
void __vector_7(void) {
    
    ISR_Generic(EXTI_6);
}

/*!< ISR of INT7                      */
void __vector_8(void) __attribute__((signal));
void __vector_8(void) {
    
    ISR_Generic(EXTI_7);
}

