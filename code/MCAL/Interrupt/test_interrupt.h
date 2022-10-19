/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	test_Interrupt.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for testing the AVR Interrupt driver.
------------------------------------------------------------------------------------------*/


#ifndef TEST_INTERRUPT_H_
#define TEST_INTERRUPT_H_

#include"Interrupt.h"


/*******************************************************************************
 *                             TEST Functions                                  *
 *******************************************************************************/

void  test_INT_ENABLE_ALL(void)
{
	INT_ENABLE_ALL();
}
void  test_INT_DISABLE_ALL(void)
{
	INT_DISABLE_ALL();
}
INT_STATE  test_INT0_Init(en_ISC0 _ISC0)
{
	return INT0_Init(_ISC0);
}
INT_STATE  test_INT1_Init(en_ISC1 _ISC1)
{
	return INT1_Init(_ISC1);
}
INT_STATE  test_INT2_Init(en_ISC2 _ISC2)
{
	return INT2_Init(_ISC2);
}
INT_STATE  test_INT0_Disable(void)
{
	return INT0_Disable();
}
INT_STATE  test_INT1_Disable(void)
{
	return INT1_Disable();
}
INT_STATE  test_INT2_Disable(void)
{
	return INT2_Disable();
}



#endif /* TEST_INTERRUPT_H_ */
