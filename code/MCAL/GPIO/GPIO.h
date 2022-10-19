/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	GPIO.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the AVR GPIO driver.
------------------------------------------------------------------------------------------*/


#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_
#include "../../Helpers/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

typedef enum GPIO_STATE
{
	GPIO_SUCCESS = 1,
	GPIO_FALIURE = 0

} GPIO_STATE;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
GPIO_STATE GPIO_setupPinDirection(const uint8 port_num,const uint8 pin_num, GPIO_PinDirectionType direction);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_setupPinDirection
[DESCRIPTION]   :	Setup the direction of the required pin input/output.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

				  in  -> pin_num

				  in  -> direction

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
GPIO_STATE GPIO_writePin(const uint8 port_num,const uint8 pin_num, uint8 value);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_writePin
[DESCRIPTION]   :	Write the value Logic High or Logic Low on the required pin.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
 	 	 	 	 	If the pin is input, this function will enable/disable the internal pull-up resistor.
[Args]		    :
				  in  -> port_num:

				  in  -> pin_num

				  in  -> The value to write

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
uint8 GPIO_readPin(const uint8 port_num,const uint8 pin_num);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_readPin
[DESCRIPTION]   :	Read and return the value for the required pin, it should be Logic High or Logic Low.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

				  in  -> pin_num

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
GPIO_STATE	GPIO_PinToggle (const uint8 port_num,const uint8 pin_num);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_PinToggle

[DESCRIPTION]   :	Toggles the pin
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

				  in  -> pin_num

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
GPIO_STATE GPIO_setupPortDirection(const uint8 port_num, GPIO_PinDirectionType direction);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_setupPortDirection

[DESCRIPTION]   :	Setup the direction of the required port all pins input/output.
 	 	 	 	 	If the direction value is PORT_INPUT all pins in this port should be input pins.
 	 	 	 	 	If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

				  in  -> direction

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
GPIO_STATE GPIO_writePort(const uint8 port_num, uint8 value);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_writePort

[DESCRIPTION]   :	Write the value on the required port.
 	 	 	 	 	If any pin in the port is output pin the value will be written.
 	 	 	 	 	If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

				  in  -> The value to write.

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
uint8 GPIO_readPort(const uint8 port_num);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_readPort

[DESCRIPTION]   :	Write the value on the required port.
 	 	 	 	 	If any pin in the port is output pin the value will be written.
 	 	 	 	 	If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/
GPIO_STATE	GPIO_PortToggle(const uint8 port_num);
/* -----------------------------------------------------------------------------------------
[Function NAME] :	GPIO_PortToggle

[DESCRIPTION]   :	Toggles the port
 	 	 	 	 	If the input port number or pin number are not correct, The function will not handle the request.
[Args]		    :
				  in  -> port_num:

[Return]        :GPIO_SUCCESS on success, GPIO_FAILURE otherwise
------------------------------------------------------------------------------------------*/

#endif /* MCAL_GPIO_GPIO_H_ */
