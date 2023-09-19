/*
 * LM35_program.c
 *
 *  Created on: Aug 1, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LM35_config.h"
#include "LM35_interface.h"
#include "LM35_private.h"
#include "ADC_interface.h"


u8 LM35_u8TempRead(u16 A_u16ADCReading)
{
	u16 MilliVolt, Temp;

	MilliVolt = (u16) (((u16)A_u16ADCReading * 5000UL) / RESOLUTION_SELECTION);

	Temp = MilliVolt / 10;

	return Temp;
}


