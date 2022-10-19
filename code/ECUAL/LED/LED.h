/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	LED.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the led driver.
------------------------------------------------------------------------------------------*/

#ifndef ECUAL_LED_LED_H_
#define ECUAL_LED_LED_H_
#include "../../MCAL/GPIO/GPIO.h"
#include "../../Helpers/std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum LED_STATE
{
	LED_SUCCESS = 1,
	LED_FAILURE = 0

} LED_STATE;

typedef struct st_Led
{
	uint8 port;
	uint8 pin;

} st_Led;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
LED_STATE LED_Init(st_Led* _led);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	LED_Init
[DESCRIPTION]   :	Initializes the led on the selected port and pin.
[Args]		    :
				  in  -> _led :
				  	  	  	  	  A pointer to an st_Led structure.

[Return]        :LED_SUCCESS on success, LED_FAILURE otherwise
------------------------------------------------------------------------------------------*/
LED_STATE LED_On(st_Led* _led);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	LED_On
[DESCRIPTION]   :	Switches the led on(writes logic high).
[Args]		    :
				  in  -> _led :
				  	  	  	  	  A pointer to an st_Led structure.

[Return]        :LED_SUCCESS on success, LED_FAILURE otherwise
------------------------------------------------------------------------------------------*/
LED_STATE LED_Off(st_Led* _led);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	LED_Off
[DESCRIPTION]   :	Switches the led off(writes logic low).
[Args]		    :
				  in  -> _led :
				  	  	  	  	  A pointer to an st_Led structure.

[Return]        :LED_SUCCESS on success, LED_FAILURE otherwise
------------------------------------------------------------------------------------------*/
LED_STATE LED_Toggle(st_Led* _led);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	LED_Toggle
[DESCRIPTION]   :	Toggles the led on/off.
[Args]		    :
				  in  -> _led :
				  	  	  	  	  A pointer to an st_Led structure.

[Return]        :LED_SUCCESS on success, LED_FAILURE otherwise
------------------------------------------------------------------------------------------*/
#endif /* ECUAL_LED_LED_H_ */
