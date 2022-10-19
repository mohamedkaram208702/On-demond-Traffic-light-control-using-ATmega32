/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	LED.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the led driver.
------------------------------------------------------------------------------------------*/
#include"LED.h"
#include "../../MCAL/GPIO/GPIO.h"
LED_STATE LED_Init(st_Led* _led)
{
	if(_led == NULL) return LED_FAILURE;
	return GPIO_setupPinDirection(_led->port, _led->pin, PIN_OUTPUT);
}

LED_STATE LED_On(st_Led* _led)
{
	if(_led == NULL) return LED_FAILURE;
	return GPIO_writePin(_led->port, _led->pin, HIGH);
}

LED_STATE LED_Off(st_Led* _led)
{
	if(_led == NULL) return LED_FAILURE;
	return GPIO_writePin(_led->port, _led->pin, LOW);
}

LED_STATE LED_Toggle(st_Led* _led)
{
	if(_led == NULL) return LED_FAILURE;
	return GPIO_PinToggle(_led->port, _led->pin);
}
