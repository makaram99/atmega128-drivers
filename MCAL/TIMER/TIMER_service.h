/******************************************************************************
 * @file        TIMER_service.h
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Interfaces header file for \ref TIMER_service.c
 * @version     1.0.0
 * @date        2022-03-20
 * @copyright   Copyright (c) 2022
 ******************************************************************************/
#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H

/*-----------------------------------------------------------------------------*/
/*                              TYPE DEFINITIONS                               */
/*-----------------------------------------------------------------------------*/

typedef struct {
	u8_t second;
	u8_t minute;
	u8_t hour;
	u8_t date;
	u8_t month;
	u8_t year;
} TIME_t;

extern TIME_t time;


/*------------------------------------------------------------------------------*/
/*                                                                              */
/*                       FUNCTIONS PROTOTYPES                                   */
/*                                                                              */
/*------------------------------------------------------------------------------*/

ERROR_t TTIMER_delayMs(const u64_t periodInMs);

ERROR_t TIMER_getTime(TIME_t * const time);


#endif  /* TIMER_SERVICE_H */   
