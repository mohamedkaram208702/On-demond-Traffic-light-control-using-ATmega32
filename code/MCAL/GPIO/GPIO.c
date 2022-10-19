/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	GPIO.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the AVR GPIO driver.
------------------------------------------------------------------------------------------*/
#include "GPIO.h"
#include "../../Helpers/MCU_configuration.h"
#include "../../Helpers/common_macros.h"
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
GPIO_STATE GPIO_setupPinDirection(const uint8 port_num,const uint8 pin_num, GPIO_PinDirectionType direction)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)){
		return GPIO_FALIURE;
	}
	else{
		/* Setup the pin direction as required */
		switch(port_num){
		case PORTA_ID:
			if(direction == PIN_OUTPUT){
				SET_BIT(DDRA,pin_num);
			}else{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;
		case PORTB_ID:
			if(direction == PIN_OUTPUT){
				SET_BIT(DDRB,pin_num);
			}else{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT){
				SET_BIT(DDRC,pin_num);
			}else{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT){
				SET_BIT(DDRD,pin_num);
			}else{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}
/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
GPIO_STATE GPIO_writePin(const uint8 port_num,const uint8 pin_num, uint8 value)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)){
		return GPIO_FALIURE;
	}
	else{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(value == HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;
		case PORTD_ID:
			if(value == HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}
/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(const uint8 port_num,const uint8 pin_num)
{
	uint8 pin_value = LOW;
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)){
		return GPIO_FALIURE;
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num){
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num))
			{
				pin_value=HIGH;
			}
			else
			{
				pin_value=LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pin_value=HIGH;			}
			else
			{
				pin_value=LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pin_value=HIGH;			}
			else
			{
				pin_value=LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pin_value=HIGH;			}
			else
			{
				pin_value=LOW;
			}
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return pin_value;
}
/*
 * * Description :
 * Toggle the pin
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
GPIO_STATE	GPIO_PinToggle (const uint8 port_num,const uint8 pin_num)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)){
		return GPIO_FALIURE;
	}
	else
	{
		switch(port_num){
		case PORTA_ID:
			TOGGLE_BIT(PORTA, pin_num);
			break;
		case PORTB_ID:
			TOGGLE_BIT(PORTB, pin_num);
			break;
		case PORTC_ID:
			TOGGLE_BIT(PORTC, pin_num);
			break;
		case PORTD_ID:
			TOGGLE_BIT(PORTD, pin_num);
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}
/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
GPIO_STATE GPIO_setupPortDirection(const uint8 port_num, uint8 direction)
{
	if(port_num >= NUM_OF_PORTS)
	{
		return GPIO_FALIURE;
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num){
		case PORTA_ID:
			DDRA=direction;
			break;
		case PORTB_ID:
			DDRB=direction;
			break;
		case PORTC_ID:
			DDRC=direction;
			break;
		case PORTD_ID:
			DDRD=direction;
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}
/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
GPIO_STATE GPIO_writePort(const uint8 port_num, uint8 value)
{
	if(port_num >= NUM_OF_PORTS)
	{
		return GPIO_FALIURE;
	}
	else
	{
		switch(port_num){
		case PORTA_ID:
			PORTA=value;
			break;
		case PORTB_ID:
			PORTB=value;
			break;
		case PORTC_ID:
			PORTC=value;
			break;
		case PORTD_ID:
			PORTD=value;
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}
/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(const uint8 port_num)
{
	uint8 port_value = LOW;
	if(port_num >= NUM_OF_PORTS)
	{
		return GPIO_FALIURE;
	}
	else
	{
		switch(port_num){
		case PORTA_ID:
			port_value=PINA;
			break;
		case PORTB_ID:
			port_value=PINB;
			break;
		case PORTC_ID:
			port_value=PINC;
			break;
		case PORTD_ID:
			port_value=PIND;
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return port_value;
}
/*
 * * Description :
 * Toggle the pin
 * If the input port number is not correct, The function will return Logic Low.
 */
GPIO_STATE	GPIO_PortToggle(const uint8 port_num)
{
	if(port_num >= NUM_OF_PORTS)
	{
		return GPIO_FALIURE;
	}
	else
	{
		switch(port_num){
		case PORTA_ID:
			PORTA^=0xFF;
			break;
		case PORTB_ID:
			PORTB^=0xFF;
			break;
		case PORTC_ID:
			PORTC^=0xFF;
			break;
		case PORTD_ID:
			PORTD^=0xFF;
			break;
		default:
			return GPIO_FALIURE;
		}
	}
	return GPIO_SUCCESS ;
}

