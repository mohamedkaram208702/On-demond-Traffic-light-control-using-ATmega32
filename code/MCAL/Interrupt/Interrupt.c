/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	Interrupt.c

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	Source file for the AVR Interrupt driver.
------------------------------------------------------------------------------------------*/
#include "../../Helpers/common_macros.h"
#include"Interrupt.h"
void  INT_ENABLE_ALL(void)
{
	__asm__ __volatile__ ("sei" ::: "memory");


}

void  INT_DISABLE_ALL(void)
{
	__asm__ __volatile__ ("cli" ::: "memory");


}


INT_STATE INT0_Init(en_ISC0 _ISC0)
{
	CLEAR_BIT(DDRD, PIN2);
	SET_BIT(GICR, INT0);
	MCUCR |=_ISC0;
	return INT_SUCCESS;
}

INT_STATE INT1_Init(en_ISC1 _ISC1)
{
	CLEAR_BIT(DDRD, PIN3);
	SET_BIT(GICR, INT1);
	MCUCR |=_ISC1<<2 ;
	return INT_SUCCESS;
}

INT_STATE INT2_Init(en_ISC2 _ISC2)
{
	CLEAR_BIT(DDRD, PIN3);
	SET_BIT(GICR, INT1);
	MCUCR |=_ISC2<< 6 ;
	return INT_SUCCESS;
}

INT_STATE INT0_Disable(void)
{
	CLEAR_BIT(GICR, INT0);

	return INT_SUCCESS;
}

INT_STATE INT1_Disable(void)
{
	CLEAR_BIT(GICR, INT1);

	return INT_SUCCESS;
}

INT_STATE INT2_Disable(void)
{
	CLEAR_BIT(GICR, INT2);

	return INT_SUCCESS;
}
