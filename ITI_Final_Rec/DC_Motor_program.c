/*
 * DC_Motor_program.c
 *
 *  Created on: Sep 2, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_register.h"
#include "DIO_interface.h"
#include "DC_Motor_interface.h"
#include "DIO_config.h"
#include <util/delay.h>

void Motor_Clockwise(void)
{

	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_u8PIN_LOW);

	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN2,DIO_u8PIN_HIGH);
	_delay_ms(2300);
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN2,DIO_u8PIN_LOW);
}

void Motor_Anticlockwise(void)

{
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN2,DIO_u8PIN_LOW);

	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_u8PIN_HIGH);
	_delay_ms(2300);
	DIO_u8SetPinValue(MOTOR_PORT,MOTOR_PIN1,DIO_u8PIN_LOW);
}
