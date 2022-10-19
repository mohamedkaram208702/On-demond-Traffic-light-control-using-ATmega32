/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	test_timer.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for testing the AVR timer driver.
------------------------------------------------------------------------------------------*/

#ifndef TEST_TIMER_H_
#define TEST_TIMER_H_

#include"timer.h"
/*******************************************************************************
 *                             TEST Functions                                  *
 *******************************************************************************/
TIMER_STATE test_Timer0_Init(en_WGM0 _WGM, en_COM0 _COM, uint8 _setInterrupt)
{
	return Timer0_Init(_WGM, _COM, _setInterrupt);
}
TIMER_STATE test_Timer0_Sleep(uint16 _duration, en_CS0 _clk)
{
	return Timer0_Sleep(_duration, _clk);
}
TIMER_STATE test_Timer0_Start(en_CS0 _clk, uint16 _count)
{
	return Timer0_Start(_clk, _count);
}
TIMER_STATE test_Timer0_Stop()
{
	return Timer0_Stop();
}
TIMER_STATE test_Timer2_Init(en_WGM2 _WGM, en_COM2 _COM, uint8 _setInterrupt)
{
	return Timer2_Init(_WGM, _COM, _setInterrupt);
}
TIMER_STATE test_Timer2_Sleep(uint16 _duration, en_CS2 _clk)
{
	return Timer2_Sleep(_duration, _clk);
}
TIMER_STATE test_Timer2_Start(en_CS2 _clk, uint16 _count)
{
	return Timer2_Start(_clk, _count);
}
TIMER_STATE test_Timer2_Stop()
{
	return Timer2_Stop();
}
TIMER_STATE test_Timer1_Init(en_WGM1 _WGM, en_COM1 _COM, uint8 _setInterrupt)
{
	return Timer1_Init(_WGM, _COM, _setInterrupt);
}
TIMER_STATE test_Timer1_Sleep(uint16 _duration, en_CS1 _clk)
{
	Timer1_Sleep(_duration, _clk);
}
TIMER_STATE test_Timer1_Start(en_CS1 _clk, uint16 _count)
{
	return Timer1_Start(_clk, _count);
}
TIMER_STATE test_Timer1_Stop()
{
	return Timer1_Stop();
}




#endif /* TEST_TIMER_H_ */
