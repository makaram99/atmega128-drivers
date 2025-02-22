/**************************************************************************
 * @file        TIMER_service.c
 * @author      Mahmoud Karam (ma.karam272@gmail.com)
 * @brief       Timer Services for.
 * @version     1.0.0
 * @date        2022-02-11
 * @copyright   Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER.h"
#include "TIMER_service.h"

/****************************************************************************
 * Function: TTIMER_delay()
 /**
 * Description: used for delay to wait and make processor busy
 *				 the maximum period depend on prescaler that used
 *				            -prescaler 8    -----> max time 256        micro second
 *				            -prescaler 64   -----> max time 2_048       micro second
 *				            -prescaler 256  -----> max time 8_192       micro second
 *                         -prescaler 1024 -----> max time 32_768     micro second
 *                         desired period calculation depend on that
 *
 * PRECONDTION: TIMER CLK SOURCE IS CLOCK
 *
 * @param[IN]  period
 *
 * @return Error error
 ******************************************************************************/

ERROR_t TTIMER_delayMs(const u64_t u64Period){

	ERROR_t error = DONE;
	u32_t TickTime,OverFlowTicks,Freq,Prescaler,DesiredTicks;
	u8_t Flag,Preload;
	f32_t NO_ofOverflow;

	/*
	 * define the freq ,presacler, OverFlowTicks parameters
	 */
	Freq = SYS_CLK;
	Prescaler = TIMER_CLK_SRC ;
	OverFlowTicks= TIMER_TICKS;
	/*
	 * calculate the Tick time of counter in microsecond
	 */
	TickTime = Prescaler / Freq;

	/*
	 * calculate the desired ticks
	 */

	DesiredTicks = Period / TickTime;

	/**
	 * Check the relation between overflow ticks and desired ticks
	 */
	if(DesiredTicks > OverFlowTicks){

		NO_ofOverflow = (f32_t)DesiredTicks /OverFlowTicks;
		/*to get integer part */
		Flag = (u32_t)NO_ofOverflow;
		/*to get fraction part and calculate the preload value*/
		Preload = ((1-(NO_ofOverflow -Flag))*OverFlowTicks);
		if(Preload >0 ){
			Flag ++;
		}
		TCNT0 = Preload;

		/*Stuck until during is elapsed */

		while(Flag > 0)
		{
			/*Decrement flag each time */
			Flag --;
			/*stay polling until flag is raised */
			while(BIT_READ(TIFR,TIFR_TOV0) != 1);
			/*CLEAR FLAG BY ST WITH LOGIC ONE*/
			BIT_SET(TIFR,TIFR_TOV0);

		}


		error = STAT1;


	}
	else if(DesiredTicks < OverFlowTicks){
		/*
		 * we calculate the preload value and set to timer register
		 */
		Preload = OverFlowTicks -DesiredTicks;
		TCNT0 = Preload;
		/*stay polling until flag is raised */
		while(BIT_READ(TIFR,TIFR_TOV0) != 1);
		/*CLEAR FLAG BY ST WITH LOGIC ONE*/
		BIT_SET(TIFR,TIFR_TOV0);
		error = STAT2;
	}
	else if(DesiredTicks == OverFlowTicks){
		TCNT0 = 0;

		/*stay polling until flag is raised */
		while(BIT_READ(TIFR,TIFR_TOV0) != 1);
		/*CLEAR FLAG BY ST WITH LOGIC ONE*/
		BIT_SET(TIFR,TIFR_TOV0);
		error = STAT3;
	}

	else
	{
		error = NULLPTR;
	}

	return error;



}


static char not_leap(void);

TIME_t time  = {0};

/* keep track of time, date, month, and year */
ERROR_t TIMER_getTime(TIME_t * const retTime) {
    ERROR_t error = ERROR_OK;

    *retTime = time;
    
    return error;
}

ISR(TIMER0_OVF_vect)
{
	if(++time.second == 60) {
		time.second = 0;
		if(++time.minute == 60) {
			time.minute = 0;
			if(++time.hour == 24) {
				time.hour = 0;
				if(++time.date == 32) {
					time.month++;
					time.date = 1;
				} else if(time.date == 31) {
					if((time.month == 4) || (time.month == 6) || (time.month == 9) || (time.month == 11)) {
						time.month++;
						time.date = 1;
					}
				} else if(time.date == 30) {
					if(time.month == 2) {
						time.month++;
						time.date = 1;
					}
				} else if(time.date == 29) {
					if((time.month == 2) && (not_leap())) {
						time.month++;
						time.date = 1;
					}
				}

				if(time.month == 13) {
					time.month = 1;
					time.year++;
				}
			}
		}
	}
}

/* check for leap year */
static char not_leap(void)
{
	if(!(time.year % 100)) {
		return (char)(time.year % 400);
	} else {
		return (char)(time.year % 4);
	}
}