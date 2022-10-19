/* -----------------------------------------------------------------------------------------
[FILE NAME]    :	common_macros.h

[AUTHOR]       :	Mohamed Karam Fouad

[DATA CREATED] :	26/09/2022

[DESCRIPTION]  :	This file contains the most used macros in embedded applications
------------------------------------------------------------------------------------------*/

#ifndef HELPERS_COMMON_MACROS_H_
#define HELPERS_COMMON_MACROS_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
/* -----------------------------------------------------------------------------------------
[MACRO NAME]   :	SET_BIT
[DESCRIPTION]  :	This macro is used to set certain bit in a certain register
					or variable
[Args]		   :
				in  -> a_REG:
							This argument indicates the register or the variable in which
							the bit will set
				in  -> a_BIT:
							This argument indicates the bit number which will set
------------------------------------------------------------------------------------------*/

#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
/* -----------------------------------------------------------------------------------------
[MACRO NAME]   :	CLEAR_BIT
[DESCRIPTION]  :	This macro is used to clear certain bit in a certain register
					or variable
[Args]		   :
				in  -> a_REG:
							This argument indicates the register or the variable in which
							the clear will be cleared
				in  -> a_BIT:
							This argument indicates the bit number which will be cleared
------------------------------------------------------------------------------------------*/

#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
/* -----------------------------------------------------------------------------------------
[MACRO NAME]   :	TOGGLE_BIT
[DESCRIPTION]  :	This macro is used to toggle certain bit in a certain register
					or variable
[Args]		   :
				in  -> a_REG:
							This argument indicates the register or the variable in which
							the clear will be toggled
				in  -> a_BIT:
							This argument indicates the bit number which will be toggled
------------------------------------------------------------------------------------------*/

#define ROR(REG,NUM) (REG=(REG>>NUM)|(REG<<(8-NUM)))
/* -----------------------------------------------------------------------------------------
[MACRO NAME]   :	ROR_BIT
[DESCRIPTION]  :	This macro is used to rotate rigth certain resgister value with
					specific number of rotates.
[Args]		   :
				in  -> a_REG:
							This argument indicates the register or the variable which will
							will be rotated
				in  -> a_NUM:
							This argument indicates the number of rotates
------------------------------------------------------------------------------------------*/

#define ROL(REG,NUM) (REG=(REG<<NUM)|(REG>>(8-NUM)))
/* -----------------------------------------------------------------------------------------
[MACRO NAME]   :	ROL_BIT
[DESCRIPTION]  :	This macro is used to rotate left certain resgister value with
					specific number of rotates.
[Args]		   :
				in  -> a_REG:
							This argument indicates the register or the variable which will
							will be rotated
				in  -> a_NUM:
							This argument indicates the number of rotates
------------------------------------------------------------------------------------------*/

#define BIT_IS_SET(REG,BIT) (REG&(1<<BIT))
/* -----------------------------------------------------------------------------------------
[Return]       :			True if the bit is set
						    False if the bit is clear
------------------------------------------------------------------------------------------*/

#define BIT_IS_CLEAR(REG,BIT) (!(REG&(1<<BIT)))
/* -----------------------------------------------------------------------------------------
[Return]       :			True if the bit is clear
						    False if the bit is set
------------------------------------------------------------------------------------------*/

#endif /* HELPERS_COMMON_MACROS_H_ */
