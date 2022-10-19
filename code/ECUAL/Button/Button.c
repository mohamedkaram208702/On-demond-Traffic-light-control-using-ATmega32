/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	Button.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the Button driver.
------------------------------------------------------------------------------------------*/
# include"Button.h"
BUTTON_STATE BUTTON_Init(st_Button* _button)
{
	if(_button == NULL) return BUTTON_FAILURE;
	return GPIO_setupPinDirection(_button->port, _button->pin, PIN_OUTPUT);
}
BUTTON_STATE BUTTON_Init_p(st_Button* _button)
{
	if(_button == NULL)
		return BUTTON_FAILURE;

	return GPIO_setupPinDirection(_button->port, _button->pin, PIN_INPUT);
}
BUTTON_STATE BUTTON_State(st_Button* _button){
	/*
	* Depending on the button setup, a pressed button
	* can be logic high or logic low
	**/

	if(_button == NULL)
		return BUTTON_FAILURE;

	// read the button pin

	// if the button is pulled low, then a push should pull it high and vice versa
	if(		(((GPIO_readPin(_button->port, _button->pin)) == HIGH) && (_button->setup == BUTTON_SETUP_LOW))
		||	(((GPIO_readPin(_button->port, _button->pin)) == LOW)  && (_button->setup == BUTTON_SETUP_HIGH)))
		return BUTTON_PRESSED;
	else
		return BUTTON_UNPRESSED;
}
