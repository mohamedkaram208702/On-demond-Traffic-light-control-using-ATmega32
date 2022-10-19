/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	TEST.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for testing the drivers.
------------------------------------------------------------------------------------------*/

#ifndef TESTS_H_
#define TESTS_H_

#include "../ECUAL/LED/LED.h"

#include "../ECUAL/Button/test_button.h"
#include "../ECUAL/LED/test_led.h"
#include "../MCAL/GPIO/test_gpio.h"
#include "../MCAL/Interrupt/test_interrupt.h"
#include "../MCAL/Timer/test_timer.h"


st_Led test_ledRed		= {.port = PORTA_ID, .pin = PIN0_ID};
st_Led test_ledGreen	= {.port = PORTA_ID, .pin = PIN1_ID};

void init_test_leds()
{


	LED_Init(&test_ledRed); LED_Init(&test_ledGreen);

}

#pragma region BUTTON_TESTS
/* void test_button_test(){
	/* test 1 */
/*if(test_button_init() == BUTTON_SUCCESS)
		LED_On(&test_ledGreen);
	else
		LED_On(&test_ledRed);*/

/* test 2 */
/*while(1){
		if(test_button_state(0) == BUTTON_PRESSED)	// setup high
		{
			LED_On(&test_ledGreen);
			LED_Off(&test_ledRed);
		}
		else{
			LED_On(&test_ledRed);
			LED_Off(&test_ledGreen);
		}
	}*/

/* test 3 */
/*while(1){
		if(test_button_state(1) == BUTTON_PRESSED)	// setup low
		{
			LED_On(&test_ledGreen);
			LED_Off(&test_ledRed);
		}
		else{
			LED_On(&test_ledRed);
			LED_Off(&test_ledGreen);
		}
	}*/
//}
#pragma endregion

#pragma region LED_TESTS
//void test_led_tests(){
	/* test 1 */
/*	if(test_led_init() == LED_SUCCESS)
		LED_On(&test_ledGreen);
	else
		LED_On(&test_ledRed);
*/
	/* test 2 */
//	if(test_led_on() == LED_SUCCESS)
//	LED_On(&test_ledGreen);
	//else
//	LED_On(&test_ledRed);

	/* test 3 */
//	if(test_led_off() == LED_SUCCESS)
//	LED_On(&test_ledGreen);
//	else
//	LED_On(&test_ledRed);

	/* test 4 */
//	if(test_led_toggle() == LED_SUCCESS)
	//LED_On(&test_ledGreen);
//	else
//	LED_On(&test_ledRed);
//}
#pragma endregion

#pragma region GPIO_TESTS
 //void test_gpio_tests(){
/* PORT TESTS */
//if(test_IO_PortInit(PORTA_ID, PIN_OUTPUT) == GPIO_SUCCESS)
//	LED_On(&test_ledGreen);
//if(test_IO_PortWrite(PORTA_ID, 0xff) == GPIO_SUCCESS)
//	LED_On(&test_ledRed);
//
	//GPIO_writePort (PORTA_ID, 0xff);
//	if(test_IO_PortRead(PORTA_ID) == GPIO_SUCCESS)
	//	return 0;
//if(test_IO_PortToggle(PORTA_ID) == GPIO_SUCCESS)
//return 0;


/* PIN TESTS */
//if(test_IO_PinInit(PORTA_ID, PIN0_ID, PIN_OUTPUT) == GPIO_SUCCESS)
//LED_On(&test_ledRed);
//if(test_IO_PinWrite(PORTA_ID, PIN0_ID, 1) == GPIO_SUCCESS)
//return 0;
//

//if(test_IO_PinRead(PORTA_ID, PIN0_ID) == GPIO_SUCCESS )
//return 0;
//if(test_IO_PinToggle(PORTA_ID, PIN0_ID) == GPIO_SUCCESS)
//return 0;
//}
#pragma endregion

#pragma region INT_TESTS
 //void test_int_tests(){
//test_INT_ENABLE_ALL();
//test_INT_DISABLE_ALL();
//
//// int0
//if(test_INT0_Init(ISC0_ANY_CHANGE)	 == INT_FAILURE) return 0;	// 0 1
//if(test_INT0_Init(ISC0_FALLING_EDGE) == INT_FAILURE) return 0;	// 1 0
//if(test_INT0_Init(ISC0_LOW_LEVEL)	 == INT_FAILURE) return 0;	// 0 0
//if(test_INT0_Init(ISC0_RISING_EDGE)  == INT_FAILURE) return 0;	// 1 1
//if(test_INT0_Disable() == INT_FAILURE) return 0;
//
//// int1
//if(test_INT1_Init(ISC1_ANY_CHANGE)	 == INT_FAILURE) return 0;	// 0 1
//if(test_INT1_Init(ISC1_FALLING_EDGE) == INT_FAILURE) return 0;	// 1 0
//if(test_INT1_Init(ISC1_LOW_LEVEL)	 == INT_FAILURE) return 0;	// 0 0
//if(test_INT1_Init(ISC1_RISING_EDGE)  == INT_FAILURE) return 0;	// 1 1
//if(test_INT1_Disable() == INT_FAILURE) return 0;
//
//// int2
//if(test_INT2_Init(ISC2_FALLING_EDGE) == INT_FAILURE) return 0;	// 0
//if(test_INT2_Init(ISC2_RISING_EDGE)  == INT_FAILURE) return 0;	// 1
//if(test_INT2_Disable() == INT_FAILURE) return 0;
//}
#pragma endregion

#pragma region TIMER_TESTS
// void test_timer_tests(){
//test_Timer0_Init(WGM0_FAST_PWM, COM0_PHASE_CORRECT_NV, 0);
//test_Timer0_Start(CS0_1024, 1 * 255);

//test_Timer2_Init(WGM2_FAST_PWM, COM2_PHASE_CORRECT_NV, 0);
//test_Timer2_Start(CS2_1024, 0.3 * 255);

//test_Timer1_Init(WGM1_FAST_PWM, COM1_PHASE_CORRECT_NV, 0);
//test_Timer1_Start(CS1_8, 0.1 * MAX_16);

//test_Timer0_Sleep(3000, CS0_1024);
//test_Timer2_Sleep(3000, CS2_1024);
//test_Timer1_Sleep(3000, CS1_1024);
//LED_On(&test_ledGreen);
//}
#pragma endregion



#endif /* TESTS_H_ */
