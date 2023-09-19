/*
 * APP_program.c
 *
 *  Created on: Sep 2, 2023
 *      Author: conncet
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "APP_config.h"
#include "APP_interface.h"

#include <util/delay.h>

u8 Check_Password(u8 Copy_u8UserInput[],u8 Copy_u8Password[])
{
	u8 Local_u8Counter,Local_u8Failed=0,Local_u8Error=1;

	for(Local_u8Counter=0; Local_u8Counter<4; Local_u8Counter++)
	{
		if(Copy_u8UserInput[Local_u8Counter] != Copy_u8Password[Local_u8Counter])
		{
			Local_u8Failed++;
		}
	}
	if(Local_u8Failed != 0)
	{
		Local_u8Error = 0;
	}
	Local_u8Failed=0;

	return Local_u8Error;
}

void Room1_ON(void)
{
	DIO_u8SetPinValue(ROOM1_PORT,ROOM1_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(ROOM1_PORT,ROOM1_PIN1,DIO_u8PIN_HIGH);
}

void Room1_OFF(void)
{
	DIO_u8SetPinValue(ROOM1_PORT,ROOM1_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ROOM1_PORT,ROOM1_PIN1,DIO_u8PIN_LOW);
}

void Room2_ON(void)
{
	DIO_u8SetPinValue(ROOM2_PORT,ROOM2_PIN0,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(ROOM2_PORT,ROOM2_PIN1,DIO_u8PIN_HIGH);
}

void Room2_OFF(void)
{
	DIO_u8SetPinValue(ROOM2_PORT,ROOM2_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(ROOM2_PORT,ROOM2_PIN1,DIO_u8PIN_LOW);
}
void MusicSound(void)
{
	u8 i;
	for(i=0; i<250; i++)
	{
		/*Note_1*/
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(10);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(10);
	}
	/*Note_2*/
	for(i=0; i<250; i++)
	{
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(30);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(30);


	}
	/*Note_3*/
	for(i=0; i<250; i++)
	{
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(50);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(50);

	}
	/*Note_4*/
	for(i=0; i<250; i++)
	{
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(70);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(70);

	}
	/*Note_5*/
	for(i=0; i<250; i++)
	{
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(90);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(90);

	}
}

void AlarmSound(void)
{
	u8 i;
	for(i=0; i<250; i++)
	{
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_HIGH);
		_delay_us(90);
		DIO_u8SetPinValue(BUZ2_PORT,BUZ2_PIN,DIO_u8PIN_LOW);
		_delay_us(90);

	}
}
