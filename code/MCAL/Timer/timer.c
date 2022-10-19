/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	timer.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the AVR timer driver.
------------------------------------------------------------------------------------------*/
#include"timer.h"

static st_TimerState g_Timer0 = { 0 };
static st_TimerState g_Timer1 = { 0 };
static st_TimerState g_Timer2 = { 0 };

static uint16 prescalers[3][8] =  { { 0, 1, 8, 64, 256, 1024,   0,    0},		// Timer0 Prescalers
		{ 0, 1, 8, 64, 256, 1024,   0,    0},		// Timer1 Prescalers
		{ 0, 1, 8, 32,  64,  128, 256, 1024}		// Timer2 Prescalers
};											// we use Zeros at the end for padding
/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/
static TIMER_STATE CalculateSettings(en_Timer _which, uint8 _clk, uint16 _duration, uint16* _start, uint16* _overflows)
{
	uint32_t MAX_Step = 0x0 ;
	if(_which == TIMER_0 || _which == TIMER_2)    // the determination for the type of timer.
		MAX_Step = MAX_8 + 1;
	else
		MAX_Step = MAX_16 + 1;
	/* Description:
	 * Example:
	 * For System Clock=1Mhz and timer prescaler is F_CPU/1024.
	 * Timer frequency will be around 1Khz, Ttimer = 1ms
	 * For initial timer counter = 6, overflow will occur every 250ms (6 --> 255 --> 6)
	 * Overflow interrupt will be generated every 250ms, so we need two overflow interrupts to count 0.5second.
	 */
	volatile uint16 prescaler = prescalers[_which][_clk];
	float T_tick = prescaler/(F_CPU *1.0f)*1000 ;		// from micro to milli    T_tick( time of one clock )
	float T_max = T_tick * MAX_Step ;
	if( T_max == _duration ){
		* _start=_duration;
	}else if ( _duration < T_max ){
		*_start = (T_max - _duration) / T_tick ;
	}else
	{
		*_overflows = ceil(_duration / T_max);
		*_start = MAX_Step - ( _duration / T_tick) / *_overflows ;
	}
	return TIM_SUCCESS;
}
/***************************    Timer0    ***************************/
TIMER_STATE Timer0_Init(en_WGM0 _WGM, en_COM0 _COM, uint8 _setInterrupt){
	if(g_Timer0.initialized == 1)
		return TIM_FAILURE;
	SET_BIT(DDRB,3);                // set the OC0 pin to output mode
	switch (_WGM)
	{				    // set wave Generation Mode
		case WGM0_NORMAL:
		{
			/* Configure the timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 */
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			( TIMSK |= ((unsigned) _setInterrupt << TOIE0));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM0_CTC:
		{

			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE0));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM0_FAST_PWM :
		{
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE0));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM0_PHASE_CORRECT_PWM:
		{
			SET_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE0));	// Enable Timer0 Overflow Interrupt
			break;
		}
		default:
			return TIM_FAILURE;
	}
	/* Set Output Compare Mode */
		switch(_COM)
		{
			case COM0_NON_PWM_TOGGLE:				// 0 1
			{
				SET_BIT(TCCR0, COM00);
				CLEAR_BIT(TCCR0, COM01);
				break;
			}

			// intended fall through, all of those cases set the same bits
			case COM0_NON_PWM_CLEAR:				// 1 0
			case COM0_FAST_PWM_NV:
			case COM0_PHASE_CORRECT_NV:
			{
				CLEAR_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
				break;
			}

			case COM0_NON_PWM_SET:					// 1 1
			case COM0_FAST_PWM_IV:
			case COM0_PHASE_CORRECT_IV:
			{
				SET_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
				break;
			}

			default:
				return TIM_FAILURE;
		}
		g_Timer0.initialized = 1;
		g_Timer0.COM = _COM;
		g_Timer0.WGM = _WGM;

		return TIM_SUCCESS;
};
TIMER_STATE Timer0_Start(en_CS0 _clk, uint16 _count)
{
	if(_clk > CS0_XTRN_RISE || g_Timer0.initialized == 0)
		return TIM_FAILURE;
	switch(g_Timer0.WGM)
	{
		case WGM0_NORMAL:
		{
			TCNT0 = _count & 0xFF;
			break;
		}
		case WGM0_PHASE_CORRECT_PWM:
		case WGM0_FAST_PWM:
		case WGM0_CTC:
		{
			OCR0 = _count & 0xFF;
			break;
		}

		default:
			return TIM_FAILURE;
	}
	TCCR0 |= (_clk & 0x07);

	return TIM_SUCCESS;
}
TIMER_STATE Timer0_Sleep(uint16 _duration, en_CS0 _clk){
	if(_clk > CS0_XTRN_RISE)
		return TIM_FAILURE;

	Timer0_Init(WGM0_NORMAL, COM0_DISCONNECTED, 0);
	uint16 start = 0x00;
	uint16 overflows = 0x00;
	CalculateSettings(TIMER_0, _clk, _duration, &start, &overflows);
	do
		{
			TCNT0 = start;
			TCCR0 |= _clk & 0x07;

			while(BIT_IS_CLEAR(TIFR, TOV0))
				;	// using polling ( busy wait )
			SET_BIT(TIFR, TOV0);

			if(overflows == 0)
				break;

		} while ( --overflows);
	Timer0_Stop();

	return TIM_SUCCESS;
}
TIMER_STATE Timer0_Stop()
{
	TCCR0 = 0x00;
	TCNT0 = 0x00;
	OCR0  = 0x00;
	g_Timer0.initialized = 0;

	return TIM_SUCCESS;
}
/***************************    Timer2    ***************************/
TIMER_STATE Timer2_Init(en_WGM2 _WGM, en_COM2 _COM, uint8 _setInterrupt)
{
	if(g_Timer2.initialized == 1)
		return TIM_FAILURE;
	SET_BIT(DDRB,7);                // set the OC0 pin to output mode
	switch (_WGM)
	{				    // set wave Generation Mode
		case WGM2_NORMAL:
		{
			/* Configure the timer control register
		 * 1. Non PWM mode FOC0=1
		 * 2. Normal Mode WGM01=0 & WGM00=0
		 * 3. Normal Mode COM00=0 & COM01=0
		 */
			CLEAR_BIT(TCCR2, WGM20);
			CLEAR_BIT(TCCR2, WGM21);
			( TIMSK |= ((unsigned) _setInterrupt << TOIE2));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM2_CTC:
		{

			CLEAR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE2));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM2_FAST_PWM :
		{
			SET_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE2));	// Enable Timer0 Overflow Interrupt
			break;
		}
		case WGM2_PHASE_CORRECT_PWM:
		{
			SET_BIT(TCCR2, WGM20);
			CLEAR_BIT(TCCR2, WGM21);
			( TIMSK |= ((unsigned) _setInterrupt << OCIE2));	// Enable Timer0 Overflow Interrupt
			break;
		}
		default:
			return TIM_FAILURE;
	}
	/* Set Output Compare Mode */
		switch(_COM)
		{
			case COM2_NON_PWM_TOGGLE:				// 0 1
			{
				SET_BIT(TCCR2, COM20);
				CLEAR_BIT(TCCR2, COM21);
				break;
			}

			// intended fall through, all of those cases set the same bits
			case COM2_NON_PWM_CLEAR:				// 1 0
			case COM2_FAST_PWM_NV:
			case COM2_PHASE_CORRECT_NV:
			{
				CLEAR_BIT(TCCR2, COM20);
				SET_BIT(TCCR2, COM21);
				break;
			}

			case COM2_NON_PWM_SET:					// 1 1
			case COM2_FAST_PWM_IV:
			case COM2_PHASE_CORRECT_IV:
			{
				SET_BIT(TCCR2, COM20);
				SET_BIT(TCCR2, COM21);
				break;
			}

			default:
				return TIM_FAILURE;
		}
		g_Timer2.initialized = 1;
		g_Timer2.COM = _COM;
		g_Timer2.WGM = _WGM;

		return TIM_SUCCESS;
};
TIMER_STATE Timer2_Sleep(uint16 _duration, en_CS2 _clk)
{
	if(_clk > CS2_1024)
		return TIM_FAILURE;

	Timer2_Init(WGM2_NORMAL, COM2_DISCONNECTED, 0);

	uint16 start = 0x00;
	uint16 overflows = 0x00;

	CalculateSettings(TIMER_2, _clk, _duration, &start, &overflows);

	do
	{
		TCNT2 = start;
		TCCR2 |= _clk & 0x07;

		while(BIT_IS_CLEAR(TIFR, TOV2))
			;	// busy wait
		SET_BIT(TIFR, TOV2);

		if (overflows == 0)
			break;

	} while ( --overflows);

	Timer2_Stop();

	return TIM_SUCCESS;
}
TIMER_STATE Timer2_Start(en_CS2 _clk, uint16 _count)
{
	if(_clk > CS2_1024 || g_Timer2.initialized == 0)
		return TIM_FAILURE;

	switch(g_Timer2.WGM)
	{
		case WGM2_NORMAL:
		{
			TCNT2 = _count & 0xFF;
			break;
		}
		case WGM2_PHASE_CORRECT_PWM:
		case WGM2_FAST_PWM:
		case WGM2_CTC:
		{
			OCR2 = _count & 0xFF;
			break;
		}

		default:
			return TIM_FAILURE;
	}

	TCCR2 |= (_clk & 0x07);

	return TIM_SUCCESS;
}
TIMER_STATE Timer2_Stop()
{
	TCCR2 = 0x00;
	TCNT2 = 0x00;
	g_Timer2.initialized = 0;

	return TIM_SUCCESS;
}
/***************************    Timer1   ***************************/
TIMER_STATE Timer1_Init(en_WGM1 _WGM, en_COM1 _COM, uint8 _setInterrupt)
{
	if (g_Timer1.initialized == 1)
		return TIM_FAILURE;

	// set the OC1A pin to output mode
	SET_BIT(DDRD,5);

		/* Set Wave Generation Mode */
	switch(_WGM)
	{
		case WGM1_NORMAL:				// 0 0 0 0 (0xFFFF = TOP)
		{
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			TIMSK |= ((unsigned) _setInterrupt << TOIE1);
			break;
		}

		case WGM1_CTC:					// 0 1 0 0 ( OCR1A = TOP)
		{
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			TIMSK |= ((unsigned) _setInterrupt << OCIE1A);

			break;
		}

		case WGM1_FAST_PWM:				// 1 1 1 0 ( ICR1A = TOP )
		{
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);

			TIMSK |= ((unsigned) _setInterrupt << OCIE1A);
			break;
		}

		case WGM1_PHASE_CORRECT_PWM:	// 1 0 1 1 ( OCR1A = TOP )
		{
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);

			TIMSK |= ((unsigned) _setInterrupt << OCIE1A);
			break;

		}
		default:
			return TIM_FAILURE;
	}

		/* Set Output Compare Mode (ONLY OCRA)*/
	switch (_COM)
	{
		case COM1_DISCONNECTED:			// 0 0
		{
			CLEAR_BIT(TCCR1A, COM1A0);
			CLEAR_BIT(TCCR1A, COM1A1);

			break;
		}

		case COM1_NON_PWM_TOGGLE:		// 0 1
		case COM1_FAST_PWM_TOGGLE:
		case COM1_PHASE_CORRECT_TOGGLE:
		{
			if(_WGM == WGM1_FAST_PWM ||
			   _WGM == WGM1_PHASE_CORRECT_PWM ||
			   _WGM == WGM1_NORMAL) {

				SET_BIT(TCCR1A, COM1A0);
				CLEAR_BIT(TCCR1A, COM1A1);
			} else {
				CLEAR_BIT(TCCR1A, COM1A0);
				CLEAR_BIT(TCCR1A, COM1A1);
			}

			break;
		}

		case COM1_NON_PWM_CLEAR:		// 1 0
		case COM1_FAST_PWM_NV:
		case COM1_PHASE_CORRECT_NV:
		{
			SET_BIT(TCCR1A, COM1A0);
			CLEAR_BIT(TCCR1A, COM1A1);

			break;
		}

		case COM1_NON_PWM_SET:			// 1 1
		case COM1_FAST_PWM_IV:
		case COM1_PHASE_CORRECT_IV:
		{
			SET_BIT(TCCR1A, COM1A0);
			SET_BIT(TCCR1A, COM1A1);

			break;
		}

		default:
			return TIM_FAILURE;

	}

	g_Timer1.initialized = 1;
	g_Timer1.COM = _COM;
	g_Timer1.WGM = _WGM;

	return TIM_SUCCESS;
}

TIMER_STATE Timer1_Sleep(uint16 _duration, en_CS1 _clk)
{
	/* Note: there might be problems if this function is interrupted
	 while updating the 16bit registers TCCR1 & TCCR1B
	*/

	if(_clk > CS1_1024)
		return TIM_FAILURE;

	Timer1_Init(WGM1_NORMAL, COM1_DISCONNECTED, 0);


	uint16 start = 0x00;
	uint16 overflows = 0x00;

	CalculateSettings(TIMER_1, _clk, _duration, &start, &overflows);
	do
	{

		TCNT1H = start >> 8;
		TCNT1L = start & 0xFF;


		TCCR1B |= ( _clk & 0x07 );

		while(BIT_IS_CLEAR(TIFR, TOV1))
			;
		SET_BIT(TIFR, TOV1);


		if(overflows == 0)
			break;

	} while ( --overflows);

	Timer1_Stop();

	return TIM_SUCCESS;
}

TIMER_STATE Timer1_Start(en_CS1 _clk, uint16 _count)
{
    /* Note: there might be problems if this function is interrupted
	 while updating the 16bit register OCR1A
	*/
	if(_clk > CS1_XTRN_RISE || g_Timer1.initialized == 0)
		return TIM_FAILURE;


	switch(g_Timer1.WGM)
	{
		case WGM1_NORMAL:
		{
			TCNT1H = _count >> 8;
			TCNT1L = _count & 0xFF;
			break;
		}
		case WGM1_PHASE_CORRECT_PWM:
		case WGM1_FAST_PWM:
		case WGM1_CTC:
		{
			//ICR1H = (_count & 0xFF00) >> 8;
			//ICR1L = (_count & 0x00FF);

			OCR1AH = (_count & 0xFF00) >> 8;
			OCR1AL = (_count & 0x00FF);
			break;
		}

		default:
			return TIM_FAILURE;
	}


	TCCR1B |= ( _clk & 0x07 );

	return TIM_SUCCESS;
}

TIMER_STATE Timer1_Stop()
{
	TCCR1A  = 0x00;
	TCNT1H  = 0x00;
	TCNT1L  = 0x00;
	g_Timer1.initialized = 0;

	return TIM_SUCCESS;
}
