/**************************************************************************
 * @file        WHEELS.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       This is the source file for the WHEELS module based on the WHEELS module.
 * @details This is the source file for the WHEELS module based on the WHEELS module.
 *          The WHEELS module is a module that controls the wheels of the robot.
 *          WHEELS is a dual H-bridge module that controls the motors of the robot.
 *          There are 6 control pins: IN1A, IN2A, IN1B, IN2B, ENA, and ENB 	        
 *          There are 2 feadback pins: CTA and CTB.
 *          
 *          - IN1A and IN2A control the speed of motor A.  (PWM)
 *          - IN1B and IN2B control the speed of motor B.  (PWM)
 *          - ENA enables the driver's output for motor A.  (Digital)
 *          - ENB enables the driver's output for motor B.  (Digital)
 * 	        - CTA reports the current draw of motor A back to the microcontroller.  (Analog)
 *          - CTB reports the current draw of motor B back to the microcontroller.  (Analog)
 * @note    The PWM frequency is recommended to be 16 kHz for normal motors, 80 kHz for Coreless motors.
 * @note    CTA and CTB are Optional.
 * @par Example:
 * 	    When IN1A is driven LOW and IN2A is	provided a PWM signal, the	motor will go in reverse. 
 *      When IN1A is provided a PWM signal and IN2A is driven LOW, the motor will go forward.
 * @warning The driver requires a maximum duty cycle on the PWM input of no more than 98%.  
 * 	        Any higher might damage the driver / result in instability.
 * @details
 * Library usage:
 * 
 * 	Option 1:
 * 		WHEELS.Init();	This will use the default pins
 * 	
 * 	Option 2:
 * 		WHEELS.init(IN1A, IN1B, IN2A, IN2B, ENA, ENB, CTA, CTB);	  This will define which
 * 			pins are used on the microcontroller.  
 * 	
 * 	Once defined the motor can be controlled by using:
 * 	WHEELS.GoForward();		Moves both motors forward
 * 	WHEELS.GoBackward();	Moves both motors reverse
 *  WHEELS_TurnLeft(SMOOTH_TURN);	Moves the left and right motors forward,
 *                                  but the left motor is slower than the right motor
 *  WHEELS_TurnRight(SMOOTH_TURN);	Moves the left and right motors forward,
 *                                but the right motor is slower than the left motor
 *  WHEELS_TurnLeft(SHARP_TURN);	Moves the left motor backward and right motors forward
 *  WHEELS_TurnRight(SHARP_TURN);	Moves the right motor backward and left motors forward
 *  WHEELS.Brake();	        UNTESTED - USE WITH CAUTION
 * 	WHEELS.Coast();		    Disables motor output
 *  WHEELS_SetSpeed(x);	    Sets the speed of both motors to x
 *  WHEELS_SetWheelsPosition(WHEELS_ON_FRONT);	    Sets the wheels position on the front
 *  WHEELS_SetWheelsPosition(WHEELS_ON_BACK);	    Sets the wheels position on the back
 *  WHEELS_GetCurrentConsumption();	    Returns the current consumption of the wheels
 * @version     1.0.0
 * @date        2022-02-09
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "TIMER.h"
#include "WHEELS.h"
#include "WHEELS_cfg.h"

/**************************************************************************
 * @brief default position of wheels on front
 ***************************************************************************/
static PWM_t  _IN1A_channel;
static PWM_t  _IN2A_channel;
static PWM_t  _IN1B_channel;
static PWM_t  _IN2B_channel;

void WHEELS_Init(void) {
    /* Initialize pins connections for wheels positioned on front */
    WHEELS_SetWheelsPosition(WHEELS_Config.WHEELS_Position);

    /* Initialize PWM channels with the required frequency  */
    PWM_Init(WHEELS_Config.IN1A_channel, 16000U);    /* 16 KHz   */
    PWM_Init(WHEELS_Config.IN2A_channel, 16000U);
    PWM_Init(WHEELS_Config.IN1B_channel, 16000U);
    PWM_Init(WHEELS_Config.IN2B_channel, 16000U);
}

void WHEELS_GoForward(void) {
    /* Sending the PWM signal to the H-bridge module. */
    PWM_Write(_IN1A_channel, WHEELS_Config.SpeedPercentage);
    PWM_Write(_IN2A_channel, 0);
    PWM_Write(_IN1B_channel, WHEELS_Config.SpeedPercentage);
    PWM_Write(_IN2B_channel, 0);

    /* Enable the H-bridge module. */
    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, HIGH);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, HIGH);
}

void WHEELS_GoBackward(void) {
    /* Sending the PWM signal to the H-bridge module. */
    PWM_Write(_IN1A_channel, 0);
    PWM_Write(_IN2A_channel, WHEELS_Config.SpeedPercentage);
    PWM_Write(_IN1B_channel, 0);
    PWM_Write(_IN2B_channel, WHEELS_Config.SpeedPercentage);

    /* Enable the H-bridge module. */
    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, HIGH);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, HIGH);
}

void WHEELS_TurnLeft(const WHEELS_TURN_t smoothOrSharp) {
    /* Sending the PWM signal to the H-bridge module. */
    switch(smoothOrSharp) {
        case SMOOTH_TURN:
            PWM_Write(_IN1A_channel, WHEELS_Config.SpeedPercentage / 2);
            PWM_Write(_IN2A_channel, 0);
            PWM_Write(_IN1B_channel, WHEELS_Config.SpeedPercentage);
            PWM_Write(_IN2B_channel, 0);
            break;
        case SHARP_TURN:
            PWM_Write(_IN1A_channel, WHEELS_Config.SpeedPercentage);
            PWM_Write(_IN2A_channel, 0);
            PWM_Write(_IN1B_channel, 0);
            PWM_Write(_IN2B_channel, WHEELS_Config.SpeedPercentage);
            break;
        default:
            /* DEBUG: */
            break;
    }

    /* Enable the H-bridge module. */
    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, HIGH);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, HIGH);
}

void WHEELS_TurnRight(const WHEELS_TURN_t smoothOrSharp) {
    /* Sending the PWM signal to the H-bridge module. */
    switch(smoothOrSharp) {
        case SMOOTH_TURN:
            PWM_Write(_IN1A_channel, WHEELS_Config.SpeedPercentage);
            PWM_Write(_IN2A_channel, 0);
            PWM_Write(_IN1B_channel, WHEELS_Config.SpeedPercentage / 2);
            PWM_Write(_IN2B_channel, 0);
            break;
        case SHARP_TURN:
            PWM_Write(_IN1A_channel, 0);
            PWM_Write(_IN2A_channel, WHEELS_Config.SpeedPercentage);
            PWM_Write(_IN1B_channel, WHEELS_Config.SpeedPercentage);
            PWM_Write(_IN2B_channel, 0);
            break;
        default:
            /* DEBUG: */
            break;
    }

    /* Enable the H-bridge module. */
    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, HIGH);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, HIGH);
}

void WHEELS_Brake(void) {
    /* Sets all pins HIGH to enable brake. */
    PWM_Write(_IN1A_channel, 100);
    PWM_Write(_IN2A_channel, 100);
    PWM_Write(_IN1B_channel, 100);
    PWM_Write(_IN2B_channel, 100);

    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, HIGH);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, HIGH);
}

void WHEELS_Coast(void) {
    /* Disables motor and allows for free roll  */
    PWM_Write(_IN1A_channel, HIGH);
    PWM_Write(_IN2A_channel, HIGH);
    PWM_Write(_IN1B_channel, HIGH);
    PWM_Write(_IN2B_channel, HIGH);

    /* Disable the H-bridge module. */
    DIO_WritePin(WHEELS_Config.ENA_pin, WHEELS_Config.ENA_port, LOW);
    DIO_WritePin(WHEELS_Config.ENB_pin, WHEELS_Config.ENB_port, LOW);
}

void WHEELS_SetSpeed(const u8_t Speed) {
    WHEELS_Config.SpeedPercentage = Speed;
}


void WHEELS_SetWheelsPosition(const WHEELS_POSITION_t wheelsPositions) {
    switch(wheelsPositions) {
        case WHEELS_ON_FRONT:
            WHEELS_Config.WHEELS_Position = WHEELS_ON_FRONT;
            _IN1A_channel = WHEELS_Config.IN1A_channel;
            _IN2A_channel = WHEELS_Config.IN2A_channel;
            _IN1B_channel = WHEELS_Config.IN1B_channel;
            _IN2B_channel = WHEELS_Config.IN2B_channel;
            break;
        case WHEELS_ON_BACK:
            WHEELS_Config.WHEELS_Position = WHEELS_ON_BACK;
            _IN1A_channel = WHEELS_Config.IN2B_channel;
            _IN2A_channel = WHEELS_Config.IN1B_channel;
            _IN1B_channel = WHEELS_Config.IN2A_channel;
            _IN2B_channel = WHEELS_Config.IN1A_channel;
            break;
        default:
            break;
    }
}

WHEELS_POSITION_t WHEELS_GetWheelsPosition(void) {
    return WHEELS_Config.WHEELS_Position;
}


#if 0       /* Uncomment after implementing ADC driver and include ADC.h */
f32_t WHEELS_GetCurrentConsumption(void) {
	f32_t Current = 0;

	Current = ADC_ReadVoltage(WHEELS_Config.CTA_pin, WHEELS_Config.CTA_port);
    Current += ADC_ReadVoltage(WHEELS_Config.CTB_pin, WHEELS_Config.CTB_port);

    Current /= (2 * WHEELS_Config.currentSensitivity);

	return Current;
}

#endif