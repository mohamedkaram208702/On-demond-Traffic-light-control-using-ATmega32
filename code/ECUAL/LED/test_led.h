/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	TEST_led.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for testing the LED driver.
------------------------------------------------------------------------------------------*/

#ifndef TEST_LED_H_
#define TEST_LED_H_

#include "LED.h"

/*******************************************************************************
 *                             TEST Functions                                  *
 *******************************************************************************/

LED_STATE test_led_init()
{
	st_Led _led = { .port = PORTB_ID, .pin = PIN0_ID };
	return LED_Init(&_led);
}

LED_STATE test_led_on()
{
	st_Led _led = { .port = PORTB_ID, .pin = PIN0_ID };
	LED_STATE status = LED_SUCCESS;
	
	status = LED_Init(&_led);
	if(status == LED_FAILURE)
		return LED_FAILURE;
		
	return LED_On(&_led);
	
}

LED_STATE test_led_off()
{
	st_Led _led = { .port = PORTB_ID, .pin = PIN0_ID };
	LED_STATE status = LED_SUCCESS;
	
	status = LED_Init(&_led);
	if(status == LED_FAILURE)
		return LED_FAILURE;
	
	return LED_Off(&_led);	
}

LED_STATE test_led_toggle()
{
	st_Led _led = { .port = PORTB_ID, .pin = PIN0_ID };
	LED_STATE status = LED_SUCCESS;
	
	status = LED_Init(&_led);
	if(status == LED_FAILURE)
		return LED_FAILURE;
	
	return LED_Toggle(&_led);
}



#endif /* TEST_LED_H_ */
