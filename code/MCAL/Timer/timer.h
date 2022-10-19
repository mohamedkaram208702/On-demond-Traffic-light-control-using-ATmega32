/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	timer.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the AVR timer driver.
------------------------------------------------------------------------------------------*/

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_
#include "../GPIO/GPIO.h"
#include "../../Helpers/common_macros.h"
#include "../../Helpers/std_types.h"
#include "../../Helpers/MCU_configuration.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum en_Timer
{
	TIMER_0,
	TIMER_1,
	TIMER_2

} en_Timer;

typedef struct st_TimerState
{
	uint8 initialized;
	uint8 WGM;
	uint8 COM;

}	st_TimerState;

#define NULL	0
#define MAX_8	255
#define MAX_16	65535

typedef enum TIMER_STATE
{
	TIM_SUCCESS = 1,
	TIM_FAILURE = 0

} TIMER_STATE;

/* Timer/Counter 0 */
typedef enum en_WGM0	// Timer/Counter0 Wave Generation Flags
{
	WGM0_NORMAL = 0,
	WGM0_CTC,
	WGM0_FAST_PWM,
	WGM0_PHASE_CORRECT_PWM,

} en_WGM0;

typedef enum en_COM0	// Timer/Counter0 Compare Output Mode Flags
{
	COM0_DISCONNECTED = 0,

	COM0_NON_PWM_TOGGLE,
	COM0_NON_PWM_CLEAR,
	COM0_NON_PWM_SET,

	COM0_FAST_PWM_TOGGLE,
	COM0_FAST_PWM_NV,		// NON-INVERTING
	COM0_FAST_PWM_IV,		// INVERTING

	COM0_PHASE_CORRECT_TOGGLE,
	COM0_PHASE_CORRECT_NV,
	COM0_PHASE_CORRECT_IV

} en_COM0;

typedef enum en_CS0		// Timer/Counter0 Clock Select Flags
{
	CS0_NO_CLOCK = 0,
	CS0_1,
	CS0_8,
	CS0_64,
	CS0_256,
	CS0_1024,
	CS0_XTRN_FALL,
	CS0_XTRN_RISE

} en_CS0 ;

/* Timer/Counter 2 */
typedef enum en_WGM2	// Timer/Counter2 Wave Generation Flags
{
	WGM2_NORMAL = 0,
	WGM2_CTC,
	WGM2_FAST_PWM,
	WGM2_PHASE_CORRECT_PWM,

} en_WGM2;

typedef enum en_CS2		// Timer/Counter2 Clock Select Flags
{
	CS2_NO_CLOCK = 0,
	CS2_1,
	CS2_8,
	CS2_32,
	CS2_64,
	CS2_128,
	CS2_256,
	CS2_1024

} en_CS2 ;

typedef enum en_COM2	// Timer/Counter2 Compare Output Mode Flags
{
	COM2_DISCONNECTED = 0,

	COM2_NON_PWM_TOGGLE,
	COM2_NON_PWM_CLEAR,
	COM2_NON_PWM_SET,

	COM2_FAST_PWM_TOGGLE,
	COM2_FAST_PWM_NV,		// NON-INVERTING
	COM2_FAST_PWM_IV,		// INVERTING

	COM2_PHASE_CORRECT_TOGGLE,
	COM2_PHASE_CORRECT_NV,
	COM2_PHASE_CORRECT_IV

} en_COM2;

/* Timer/Counter 1 */
typedef enum en_WGM1	// Timer/Counter1 Wave Generation Flags
{
	WGM1_NORMAL = 0,
	WGM1_CTC,
	WGM1_FAST_PWM,
	WGM1_PHASE_CORRECT_PWM,

} en_WGM1;

typedef enum en_COM1	// Timer/Counter1 Compare Output Mode
{
	COM1_DISCONNECTED = 0,

	COM1_NON_PWM_TOGGLE,
	COM1_NON_PWM_CLEAR,
	COM1_NON_PWM_SET,

	COM1_FAST_PWM_TOGGLE,
	COM1_FAST_PWM_NV,		// NON-INVERTING
	COM1_FAST_PWM_IV,		// INVERTING

	COM1_PHASE_CORRECT_TOGGLE,
	COM1_PHASE_CORRECT_NV,
	COM1_PHASE_CORRECT_IV

} en_COM1;

typedef enum en_CS1		// Timer/Counter1 Clock Select Flags
{
	CS1_NO_CLOCK = 0,
	CS1_1,
	CS1_8,
	CS1_64,
	CS1_256,
	CS1_1024,
	CS1_XTRN_FALL,
	CS1_XTRN_RISE

} en_CS1;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
TIMER_STATE Timer0_Init(en_WGM0 _WGM, en_COM0 _COM, uint8 _setInterrupt);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer0_Init
[DESCRIPTION]   :	Initializes Timer/Counter0 by setting the WGM and the COM.
[Args]		    :
				  in  -> _WGM :
				  	  	  	  	  The wave generation flag.

				  in  -> _COM :
								  The compare output mode flag.
				  in  -> _setInterrupt :
				  				  Enable interrupts or not.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer0_Sleep(uint16 _duration, en_CS0 _clk);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer0_Sleep  (Timer_delay)
[DESCRIPTION]   :	A one-call function that initializes the timer and blocks
					the calling thread until the specified duration elapses.
[Args]		    :
				  in  -> _duration :
				  	  	  	  	  The sleep duration in milli-seconds.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer0_Start(en_CS0 _clk, uint16 _count);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer0_Start
[DESCRIPTION]   :	Starts an initialized timer. Sets the Output Compare Register
                    and the clock.
[Args]		    :
				  in  -> _count :
				  	  	  	  	  The number of ticks to count.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer0_Stop();
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer0_Stop
[DESCRIPTION]   :	Stops the timer by clearing the clock select bits.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer2_Init(en_WGM2 _WGM, en_COM2 _COM, uint8 _setInterrupt);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer2_Init
[DESCRIPTION]   :	Initializes Timer/Counter2 by setting the WGM and the COM.
[Args]		    :
				  in  -> _WGM :
				  	  	  	  	  The wave generation flag.

				  in  -> _COM :
								  The compare output mode flag.
				  in  -> _setInterrupt :
				  				  Enable interrupts or not.
[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer2_Sleep(uint16 _duration, en_CS2 _clk);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer2_Sleep
[DESCRIPTION]   :	A one-call function that initializes the timer and blocks
					the calling thread until the specified duration elapses.
[Args]		    :
				  in  -> _duration :
				  	  	  	  	  The sleep duration in milli-seconds.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer2_Start(en_CS2 _clk, uint16 _count);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer2_Start
[DESCRIPTION]   :	Starts an initialized timer. Sets the Output Compare Register
                    and the clock.
[Args]		    :
				  in  -> _count :
				  	  	  	  	  The number of ticks to count.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer2_Stop();
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer2_Stop
[DESCRIPTION]   :	Stops the timer by clearing the clock select bits.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/

// timer 1
/* Note:
	Timer 1 is more complex since there are 2 output compare units
	and a lot of different operating modes.
	For now it will only implement the same logic as Timers 0 & 2
	with the difference of increased resolution.
	-- ONLY OCR1A IS USED --
*/
TIMER_STATE Timer1_Init(en_WGM1 _WGM, en_COM1 _COM, uint8 _setInterrupt);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer1_Init
[DESCRIPTION]   :	Initializes Timer/Counter1 by setting the WGM and the COM.
[Args]		    :
				  in  -> _WGM :
				  	  	  	  	  The wave generation flag.

				  in  -> _COM :
								  The compare output mode flag.
				  in  -> _setInterrupt :
				  				  Enable interrupts or not.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer1_Sleep(uint16 _duration, en_CS1 _clk);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer1_Sleep
[DESCRIPTION]   :	A one-call function that initializes the timer and blocks
					the calling thread until the specified duration elapses.
[Args]		    :
				  in  -> _duration :
				  	  	  	  	  The sleep duration in milli-seconds.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer1_Start(en_CS1 _clk, uint16 _count);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer1_Start
[DESCRIPTION]   :	Starts an initialized timer. Sets the Output Compare Register
                    and the clock.
[Args]		    :
				  in  -> _count :
				  	  	  	  	  The number of ticks to count.

				  in  -> _clk :
								  The clock select flag/prescaler.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
TIMER_STATE Timer1_Stop();
/* -----------------------------------------------------------------------------------------
[Function NAME] :	Timer1_Stop
[DESCRIPTION]   :	Stops the timer by clearing the clock select bits.

[Return]        :TIM_SUCCESS on success, TIM_FAILURE otherwise
------------------------------------------------------------------------------------------*/
#endif /* MCAL_TIMER_TIMER_H_ */
