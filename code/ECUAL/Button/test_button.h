/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	Button.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for testing the Button driver.
------------------------------------------------------------------------------------------*/

#ifndef TEST_BUTTON_H_
#define TEST_BUTTON_H_

#include "Button.h"

/*******************************************************************************
 *                             TEST Functions                                  *
 *******************************************************************************/

BUTTON_STATE test_button_init()
{
	st_Button button={.port = PORTB_ID, .pin = PIN0_ID};
	return BUTTON_Init(&button);
}

BUTTON_STATE test_button_state(en_BUTTON_SETUP _setup)
{
	
	st_Button button = {.port = PORTB_ID, .pin = PIN0_ID, .setup = _setup };
	BUTTON_STATE state = BUTTON_SUCCESS;
	
	state = BUTTON_Init_p(&button);
	if(state == BUTTON_FAILURE)
		return BUTTON_FAILURE;
		
	return BUTTON_State(&button);

}



#endif /* TEST_BUTTON_H_ */
