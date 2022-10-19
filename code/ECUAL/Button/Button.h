/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	Button.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the Button driver.
------------------------------------------------------------------------------------------*/
#ifndef ECUAL_BUTTON_BUTTON_H_
#define ECUAL_BUTTON_BUTTON_H_

#include "../../Helpers/Std_types.h"
#include "../../MCAL/GPIO/GPIO.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum BUTTON_STATE
{
	BUTTON_SUCCESS	 = 1,
	BUTTON_FAILURE	 = 0,

	BUTTON_PRESSED	 = 3,
	BUTTON_UNPRESSED = 4

} BUTTON_STATE;

typedef enum en_BUTTON_SETUP  // IF the button is pulled high or low
{
	BUTTON_SETUP_HIGH = 0,     // Pull up resistor
	BUTTON_SETUP_LOW  = 1	  // Pull down resistor
} en_BUTTON_SETUP;

typedef struct st_Button
{
	uint8 port;
	uint8 pin;
	en_BUTTON_SETUP setup;
} st_Button;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

BUTTON_STATE BUTTON_Init(st_Button* _button);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	BUTTON_Init
[DESCRIPTION]   :	Initializes the button on the selected port and pin.
[Args]		    :
				  in  -> _button :
				  	  	  	  	  A pointer to an st_Button structure.

[Return]        :BUTTON_SUCCESS on success, BUTTON_FAILURE otherwise
------------------------------------------------------------------------------------------*/
BUTTON_STATE BUTTON_State(st_Button* _button);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	BUTTON_Init
[DESCRIPTION]   :	Retrieves the button state whether pressed or unpressed.
[Args]		    :
				  in  -> _button :
				  	  	  	  	  A pointer to an st_Button structure.

[Return]        :BUTTON_PRESSED, BUTTON_UNPRESSED.
------------------------------------------------------------------------------------------*/

BUTTON_STATE BUTTON_Init_p(st_Button* _button);



#endif /* ECUAL_BUTTON_BUTTON_H_ */
