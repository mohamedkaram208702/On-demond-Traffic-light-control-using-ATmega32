/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	test_GPIO.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Header file for the test GPIO driver.
------------------------------------------------------------------------------------------*/


#ifndef TEST_GPIO_H_
#define TEST_GPIO_H_

#include "GPIO.h"

/*******************************************************************************
 *                             TEST Functions                                  *
 *******************************************************************************/

GPIO_STATE	test_IO_PortInit	(const uint8 port_num, GPIO_PinDirectionType direction)
{
	return GPIO_setupPortDirection(port_num, direction);
}
GPIO_STATE	test_IO_PortWrite	(const uint8 port_num, uint8 value)
{
	return GPIO_writePort(port_num, value);
}
uint8		test_IO_PortRead	(const uint8 port_num)
{
	return GPIO_readPort(port_num);
}
GPIO_STATE	test_IO_PortToggle	(const const uint8 port_num)
{
	return GPIO_PortToggle(port_num);
}
GPIO_STATE	test_IO_PinInit		(const uint8 port_num,const uint8 pin_num, GPIO_PinDirectionType directionr)
{
	return GPIO_setupPinDirection(port_num, pin_num, directionr);
}
GPIO_STATE	test_IO_PinWrite	(const uint8 port_num,const uint8 pin_num, uint8 value)
{
	return GPIO_writePin(port_num, pin_num, value);
}
uint8		test_IO_PinRead		(const uint8 port_num,const uint8 pin_num)
{
	return GPIO_readPin(port_num, pin_num);
}
GPIO_STATE	test_IO_PinToggle	(const uint8 port_num,const uint8 pin_num)
{
	return GPIO_PinToggle(port_num, pin_num);
}



#endif /* TEST_GPIO_H_ */
