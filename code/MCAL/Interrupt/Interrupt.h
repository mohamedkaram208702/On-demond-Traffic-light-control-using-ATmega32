/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	Interrupt.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the AVR Interrupt driver.
------------------------------------------------------------------------------------------*/

#ifndef MCAL_INTERRUPT_INTERRUPT_H_
#define MCAL_INTERRUPT_INTERRUPT_H_
#include "../../Helpers/std_types.h"
#include "../../Helpers/MCU_configuration.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum INT_STATE
{
	INT_SUCCESS = 1,
	INT_FAILURE = 0

} INT_STATE;

typedef enum en_ISC0		// Interrupt0 Sense Control
{
	ISC0_LOW_LEVEL = 0,
	ISC0_ANY_CHANGE,
	ISC0_FALLING_EDGE,
	ISC0_RISING_EDGE

} en_ISC0;

typedef enum en_ISC1		// Interrupt1 Sense Control
{
	ISC1_LOW_LEVEL = 0,
	ISC1_ANY_CHANGE,
	ISC1_FALLING_EDGE,
	ISC1_RISING_EDGE

} en_ISC1;

typedef enum en_ISC2		// Interrupt1 Sense Control
{
	ISC2_FALLING_EDGE = 0,
	ISC2_RISING_EDGE

} en_ISC2;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void INT_ENABLE_ALL(void);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT_ENABLE_ALL
[DESCRIPTION]   :	Sets the global interrupt flag in SREG.

------------------------------------------------------------------------------------------*/

void INT_DISABLE_ALL(void);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT_DISABLE_ALL
[DESCRIPTION]   :	Clear the global interrupt flag in SREG.

------------------------------------------------------------------------------------------*/

INT_STATE  INT0_Init(en_ISC0 _ISC0);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT0_Init
[DESCRIPTION]   :	Initialize interrupt 0
[Args]		    :
				  in  -> _ISC0	:
								Interrupt sense control 0

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/

INT_STATE  INT1_Init(en_ISC1 _ISC1);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT1_Init
[DESCRIPTION]   :	Initialize interrupt 0
[Args]		    :
				  in  -> _ISC1	:
								Interrupt sense control 1

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/

INT_STATE  INT2_Init(en_ISC2 _ISC2);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT2_Init
[DESCRIPTION]   :	Initialize interrupt 2
[Args]		    :
				  in  -> _ISC2	:
								Interrupt sense control 2

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/

INT_STATE  INT0_Disable(void);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT0_Disable
[DESCRIPTION]   :	Disables interrupt 0

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/

INT_STATE  INT1_Disable(void);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT1_Disable
[DESCRIPTION]   :	Disables interrupt 1

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/

INT_STATE  INT2_Disable(void);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	INT2_Disable
[DESCRIPTION]   :	Disables interrupt 2

[Return]        :INT_SUCCESS on success, INT_FAILURE otherwise.
------------------------------------------------------------------------------------------*/






#endif /* MCAL_INTERRUPT_INTERRUPT_H_ */
