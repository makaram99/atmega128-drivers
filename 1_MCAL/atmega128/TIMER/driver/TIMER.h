/******************************************************************************
 * @file        TIMER.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref TIMER.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef TIMER_H
#define TIMER_H

/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                                  TYPEDEFS                                    */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    NO_CLOCK,               /* No clock source: Timer/Counter stopped */
    F_CPU_CLOCK,            /* No prescaling: running at full CPU clock speed */
    F_CPU_8,                /* Prescaler: CPU clock / 8 */
    F_CPU_32,               /* Prescaler: CPU clock / 32 */
    F_CPU_64,               /* Prescaler: CPU clock / 64 */
    F_CPU_128,              /* Prescaler: CPU clock / 128 */
    F_CPU_256,              /* Prescaler: CPU clock / 256 */
    F_CPU_1024,             /* Prescaler: CPU clock / 1024 */
    F_CPU_EXT_CLK_FALLING,  /* External clock on T0 pin, falling edge */
    F_CPU_EXT_CLK_RISING    /* External clock on T0 pin, rising edge */
}TIMER_CLOCK_t;

typedef enum {
    TIMER_MODE_NORMAL,      /* Counter increments on the rising edge of OCn pin */
    TIMER_MODE_CTC,         /* Counter is cleared when the counter matches OCRn register */
    TIMER_MODE_CTC_OCR,     /* Counter is cleared when the counter matches OCRn register */
    TIMER_MODE_CTC_ICR,     /* Counter is cleared when the counter matches the ICRn register */
    TIMER_MODE_FAST_PWM,    /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_8,  /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_9,  /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_10, /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_ICR,/* Counter increments on the rising edge of OCn pin, and the ICRn register is used as TOP value */
    TIMER_MODE_FAST_PWM_OCR,/* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM,       /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_8,     /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_9,     /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_10,    /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_ICR,   /* Counter increments on the rising edge of OCn pin, and the ICRn register is used as TOP value */
    TIMER_MODE_PHASE_CORRECT_PWM_OCR,   /* Counter increments on the rising edge of OCn pin, and OCRn register is used as TOP value */
    TIMER_MODE_PHASE_FREQ_CORRECT_ICR,  /* Counter increments on the rising edge of the ICR1 register */
    TIMER_MODE_PHASE_FREQ_CORRECT_OCR,  /* Counter increments on the rising edge of the OCR1 register */
}TIMER_MODE_t;

typedef enum {
    NO_OC,         /* No output compare: OCn disconnected */
    TOGGLE_OC,     /* Toggle OCn on compare match: OCn is set when the counter matches the OCR0 register, and cleared at the next OCR0 match */
    CLEAR_OC,      /* Clear OCn on compare match: OCn is cleared when the counter matches the OCR0 register, and set at the next OCR0 match */
    SET_OC         /* Set OCn on compare match: OCn is set when the counter matches the OCR0 register, and cleared at the next OCR0 match */
}TIMER_OC_t;

typedef enum {
    TIMER_OCA,     /* Output Compare A */
    TIMER_OCB,     /* Output Compare B */
    TIMER_OCC,     /* Output Compare C */
}TIMER_OCx_t;

typedef enum {
    PWM_0,    /* Connected with pin --> OC0      */
    PWM_1,    /* Connected with pin --> OC1A     */
    PWM_2,    /* Connected with pin --> OC1B     */
    PWM_3,    /* Connected with pin --> OC1C     */
    PWM_4,    /* Connected with pin --> OC2      */
    PWM_5,    /* Connected with pin --> OC3A     */
    PWM_6,    /* Connected with pin --> OC3B     */
    PWM_7,    /* Connected with pin --> OC3C     */
}PWM_t;


/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                      Prototypes of Timer 0 functions                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

#define TIMER0_GetTop()    (255U)

/*******************************************************************************
 *  @brief          Initialize Timer 0
 *  @param[in]  initValue: initial value of the timer
 *  @param[in]  clock: clock source of the timer
 *  @param[in]  timerMode: mode of the timer
 *  @param[in]  compareMode: compare mode of the timer
 ******************************************************************************/
void TIMER0_Init(u8_t initValue, const TIMER_CLOCK_t clock, const TIMER_MODE_t timerMode, 
                 const TIMER_OC_t compareMode);

/*******************************************************************************
 *  @brief          Set Compare Value of Timer 0 (OCR0)
 *  @param[in]  compareValue: compare value of the timer
 ******************************************************************************/
void TIMER0_SetCompareValue(const u8_t compareValue);

/*******************************************************************************
 *  @brief          Set Value of Timer 0 (TCNT0)
 *  @param[in]  compareValue: compare value of the timer
 ******************************************************************************/
void TIMER0_SetTimer(const u8_t timerValue);

/*******************************************************************************
 *  @brief          Enable Overflow Interrupt of Timer 0
 *  @param[in]  callbackFunction: callback function to be called when the timer 
 *              overflows
 ******************************************************************************/
void TIMER0_EnableOverflowInterrupt(void (* const callbackFunction)(void));

/*******************************************************************************
 *  @brief          Disable Overflow Interrupt of Timer 0
 ******************************************************************************/
void TIMER0_DisableOverflowInterrupt(void);

/*******************************************************************************
 *  @brief          Enable Compare Match Interrupt of Timer 0
 *  @param[in]  callbackFunction: callback function to be called when the timer 
 *              matches the compare value
 ******************************************************************************/
void TIMER0_EnableCompareMatchInterrupt(void (* const callbackFunction)(void));

/*******************************************************************************
 *  @brief          Disable Compare Match Interrupt of Timer 0
 ******************************************************************************/
void TIMER0_DisableCompareMatchInterrupt(void);

/*******************************************************************************
 *  @brief          Get Timer 0 Value (TCNT0)
 ******************************************************************************/
u8_t TIMER0_GetTimerValue(void);


/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                      Prototypes of Timer 1 functions                         */
/*                                                                              */
/*------------------------------------------------------------------------------*/

#define TIMER1_GetTop()    (65535U)

/*******************************************************************************
 *  @brief          Initialize Timer 2
 *  @param[in]  initValue: initial value of the timer
 *  @param[in]  clock: clock source of the timer
 *  @param[in]  timerMode: mode of the timer
 *  @param[in]  compareMode: compare mode of the timer
 *  @param[in]  OCx: output compare of the timer (TIMER_OCA, TIMER_OCB, TIMER_OCC)
 ******************************************************************************/
void TIMER1_Init(const u16_t initValue, const TIMER_CLOCK_t clock, 
                 const TIMER_MODE_t timerMode, const TIMER_OC_t compareMode, 
                 const TIMER_OCx_t OCx);

/*******************************************************************************
 *  @brief          Set Compare Value of Timer 2
 *  @param[in]  compareValue: compare value of the timer
 *  @param[in]  OCx: output compare of the timer (TIMER_OCA, TIMER_OCB, TIMER_OCC)
 ******************************************************************************/
void TIMER1_SetCompareValue(const u16_t compareValue, const TIMER_OCx_t OCx);

/*******************************************************************************
 *  @brief          Set Value of Timer 2 (TCNT2)
 *  @param[in]  timerValue: timer value
 ******************************************************************************/
void TIMER1_SetTimer(const u16_t timerValue);

/*******************************************************************************
 *  @brief          Enable Overflow Interrupt of Timer 2
 *  @param[in]  callbackFunction: callback function to be called when the timer 
 *              overflows
 ******************************************************************************/
void TIMER1_EnableOverflowInterrupt(void (* const callbackFunction)(void));

/*******************************************************************************
 *  @brief          Disable Overflow Interrupt of Timer 2
 ******************************************************************************/
void TIMER1_DisableOverflowInterrupt(void);

/*******************************************************************************
 *  @brief          Enable Compare Match Interrupt of Timer 2
 *  @param[in]  OCx: output compare of the timer (TIMER_OCA, TIMER_OCB, TIMER_OCC)
 *  @param[in]  callbackFunction: callback function to be called when the timer 
 *              matches the compare value
 ******************************************************************************/
void TIMER1_EnableCompareMatchInterrupt(const TIMER_OCx_t OCx, 
                                        void (* const callbackFunction)(void));

/*******************************************************************************
 *  @brief          Disable Compare Match Interrupt of Timer 2
 *  @param[in]  OCx: output compare of the timer (TIMER_OCA, TIMER_OCB, TIMER_OCC)
 ******************************************************************************/
void TIMER1_DisableCompareMatchInterrupt(const TIMER_OCx_t OCx);

/*******************************************************************************
 *  @brief          Enable Capture Interrupt of Timer 2
 *  @param[in]  callbackFunction: callback function to be called when the timer
 ******************************************************************************/
void TIMER1_EnableCaptureInterrupt(void (* const callbackFunction)(void));

/*******************************************************************************
 *  @brief          Disable Capture Interrupt of Timer 2
 ******************************************************************************/
void TIMER1_DisableCaptureInterrupt(void);

/*******************************************************************************
 *  @brief          Get Timer 2 Value (TCNT2)
 ******************************************************************************/
u16_t TIMER1_GetTimerValue(void);


/*------------------------------------------------------------------------------*/
/*                      Prototypes of PWMs functions                            */
/*------------------------------------------------------------------------------*/

/*******************************************************************************
 *  @brief          Initialize PWM
 *  @param[in]  channel: PWM channel, can be one of the following:
 *              \ref PWM_0 to \ref PWM_7. Members of \ref PWM_t enumeration
 * @param[in]   frequencyInKHz: frequency of the PWM signal
 ******************************************************************************/
void PWM_Init(const PWM_t channel, const u32_t frequencyInKHz);

/*******************************************************************************
 *  @brief          Set Duty Cycle of PWM
 *  @param[in]  channel: PWM channel, can be one of the following:
 *              \ref PWM_0 to \ref PWM_7. Members of \ref PWM_t enumeration
 * @param[in]   dutyCyclePercentage: duty cycle of the PWM signal in %
 ******************************************************************************/
void PWM_Write(const PWM_t channel, const u8_t dutyCyclePercentage);

#endif  /* TIMER_H */   
