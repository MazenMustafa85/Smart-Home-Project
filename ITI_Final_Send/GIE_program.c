/*
 * GIE_program.c
 *
 *  Created on: May 24, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_config.h"
#include "GIE_register.h"
#include "GIE_interface.h"


/*Enable global interrupt*/
void GIE_Enable(void)
{
	/*Set bit SREG_I*/
	SET_BIT(SREG,SREG_I);
}

/*Disable global interrupt*/
void GIE_Disable(void)
{
	/*Clear bit SREG_I*/
	CLR_BIT(SREG,SREG_I);
}
