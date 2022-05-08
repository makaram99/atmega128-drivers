/******************************************************************************
 * @file        WHEELS.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref WHEELS.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef WHEELS_H
#define WHEELS_H      

typedef enum{
    WHEELS_ON_FRONT,
    WHEELS_ON_BACK,
}WHEELS_POSITION_t;

typedef enum{
    SMOOTH_TURN,
    SHARP_TURN,
}WHEELS_TURN_t;

/****************************************************************************
 * @brief Initialize the wheels module.
 ***************************************************************************/
void WHEELS_Init(void);

/****************************************************************************
 * @brief Turn the wheels to go forward.
 ***************************************************************************/
void WHEELS_GoForward(void);

/****************************************************************************
 * @brief Turn the wheels to go backward.
 ***************************************************************************/
void WHEELS_GoBackward(void);

/****************************************************************************
 * @brief Turn the wheels to turn left.
 ***************************************************************************/
void WHEELS_TurnLeft(WHEELS_TURN_t smoothOrSharp);

/****************************************************************************
 * @brief Turn the wheels to turn right.
 ***************************************************************************/
void WHEELS_TurnRight(WHEELS_TURN_t smoothOrSharp);

/****************************************************************************
 * @brief Brake the wheels.
 ***************************************************************************/
void WHEELS_Brake(void);

/****************************************************************************
 * @brief Disables wheels and allows for free rolling.
 ***************************************************************************/
void WHEELS_Coast(void);

/****************************************************************************
 * @brief Set the speed of the wheels.
 * @param[in] Speed: The speed of the wheels.
 ***************************************************************************/
void WHEELS_SetSpeed(u8_t Speed);

/****************************************************************************
 * @brief Set the position of the wheels: on the front or on the back.
 * @param[in] wheelsPositions: The poition of the wheels: WHEELS_ON_FRONT or WHEELS_ON_BACK.
 ***************************************************************************/
void WHEELS_SetWheelsPosition(WHEELS_POSITION_t wheelsPositions);

/****************************************************************************
 * @brief Get the current consumption of the wheels.
 * @return f32_t The current consumption of the wheels in A.
 ***************************************************************************/
f32_t WHEELS_GetCurrentConsumption();

/****************************************************************************
 * @brief Get the current position of the wheels.
 * @return f32_t The current consumption of the wheels in A.
 ***************************************************************************/
WHEELS_POSITION_t WHEELS_GetWheelsPosition(void);

#endif                  
