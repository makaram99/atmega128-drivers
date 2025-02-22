/******************************************************************************
 * @file        LIFTER.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref LIFTER.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef LIFTER_H
#define LIFTER_H

/*******************************************************************************
 * @brief Initialize the lifter
 ******************************************************************************/
void LIFTER_Init(void);

/*******************************************************************************
 * @brief Move the lifter up 
 ******************************************************************************/
void LIFTER_MoveUp();

/*******************************************************************************
 * @brief Move the lifter down
 ******************************************************************************/
void LIFTER_MoveDown();

/*******************************************************************************
 * @brief Enable the lifter motor
 ******************************************************************************/
void LIFTER_Enable(void);

/*******************************************************************************
 * @brief Disable the lifter motor
 ******************************************************************************/
void LIFTER_Disable(void);

/*******************************************************************************
 * @brief Set the speed of the lifter motor
 * @param[in] speed: The speed of the lifter motor
 ******************************************************************************/
void LIFTER_SetSpeed(u8_t speed);

/*******************************************************************************
 * @brief Set the stroke of the lifter motor per revolution in mm
 * @param[in] overallStroke: The stroke of the lifter motor per revolution in mm
 ******************************************************************************/
void LIFTER_SetOverallStroke(u8_t overallStroke);

/*******************************************************************************
 * @brief Set the number of pulses per revolution
 * @param[in] pulsesPerRevolution: The number of pulses per revolution
 ******************************************************************************/
void LIFTER_SetPulsesPerRevolution(u16_t pulsesPerRevolution);

/*******************************************************************************
 * @brief Set the distance per revolution
 * @param[in] revolutionStroke: The distance per revolution in mm
 ******************************************************************************/
void LIFTER_SetRevolutionStroke(u8_t revolutionStroke);


#endif                  /* LIFTER_H */