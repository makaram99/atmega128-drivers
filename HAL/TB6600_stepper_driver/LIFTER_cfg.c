/******************************************************************************
 * @file        LIFTER_cfg.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Configuration source file for \ref LIFTER.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "LIFTER.h"
#include "LIFTER_cfg.h"

/********************************************************************************
 * @brief Lifter configurations
 * @note stepSize is the number of millimeters that the lifter will move when 
 *       calling LIFTER_move function.  \n
 *       For example, if the stepSize is 10, the lifter will move 10 millimeters
 *       when calling LIFTER_move function.
 * @note pulsePerRevolution is the number of pulses that the lifter will make
 *       to make one revolution.    \n
 *          For example, if the pulsePerRevolution is 200, the lifter will make 200
 *          pulses to make one revolution.
 *          Options: 
 *              * 200 --> Full step
 *              * 400 --> Half step
 *              * 800 --> 1/4 step      --> Not allowed with TB6560    
 *              * 1600 --> 1/8 step
 *              * 3200 --> 1/16 step
 *              * 6400 --> 1/32 step    --> Not allowed with TB6560
 * @note distancePerRevolution is the number of millimeters that the lifter will
 *       move in one revolution.    \n
 *        For example, if the distancePerRevolution is 100, the lifter will move
 *        100 millimeters in one revolution.
 * @note speed is the number of millimeters that the lifter will move in one second.
 *          For example, if the speed is 100, the lifter will move 100 millimeters in
 *          one second.
 * @note speed must be less <= stepSize
 * @details You can change default speed, overallStroke, pulsePerRevolution, 
 *          and revolutionStroke by calling faunctions LIFTER_SetSpeed, 
 *          LIFTER_SetOverallStroke, LIFTER_SetPulsesPerRevolution, and
 *          LIFTER_SetRevolutionStroke.
 *          See prototypes of these functions for more details.
 ******************************************************************************/
LIFTER_CONFIGS_t LifterConfigs = {
     .directionPin       = PIN_4,        /* Direction pin of the lifter */
     .directionPinPort   = PORT_D,       /* Direction pin port of the lifter */
     .pulsePin           = PIN_5,        /* Pulse pin of the lifter */
     .pulsePinPort       = PORT_D,       /* Pulse pin port of the lifter */
     .enablePin          = PIN_6,        /* Enable pin of the lifter */
     .enablePinPort      = PORT_D,       /* Enable pin port of the lifter */
     .overallStroke      = (u8_t)20,      /* Overall stroke of the lifter */
     .pulsesPerRevolution = (u16_t)1600,  /* Pulses per revolution */
     .revolutionStroke   = (u8_t)2,       /* Revolution stroke of the lifter */
     .speed              = (u8_t)4,       /* Speed of the lifter */
};