/*
 * main_send.c
 *
 *  Created on: Aug 29, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include "ADC_interface.h"
#include "LM35_interface.h"
#include "Ultra_Sonic_interface.h"
#include "Timer_interface.h"
#include "GIE_interface.h"
#include <util/delay.h>

u16 ADC_TempReading, ADC_Light;
u8 Local_u8Counter;

void TempReading_Func(void);

int main(void)
{
	u8 Pressed_Key;
	u16 Local_u16Distance;
	u32 Local_u32Light;
	/*TX pin OUTPUT*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_OUTPUT);

	/*RX pin INPUT*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_INPUT);

	/*PD7 output for motor*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_OUTPUT);

	/*PA0 input for Temperature sensor*/
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_INPUT);

	/*PA1 input for Light sensor*/
	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_INPUT);

	/*PORTB output*/
	DIO_u8SetPortDirection(DIO_u8PORTB,DIO_u8PORT_OUTPUT);

	/*PD6 ICP1 input*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_INPUT);

	/*PD2 output for buzzer*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_OUTPUT);



	UART_voidInit();
	KEYPAD_Init();
	ADC_Init();
	TIMER1_voidSetNormalMode();
	TIMER1_voidSetOVFInterrupt();
	GIE_Enable();
	while(1)
	{

		Pressed_Key = KEYPAD_GetKeyPressed();

		if(Pressed_Key != KEYPAD_NotPressed)
		{
			UART_voidSendData(Pressed_Key);
		}

		ADC_StartConversionAsynch(ADC_SINGLE_ENDED_CHAN_0, &ADC_TempReading, &TempReading_Func);
		_delay_ms(300);

		/*light sensor*/
		Local_u32Light = ADC_voidGetAnalogRead(ADC_SINGLE_ENDED_CHAN_1);

		LDR_voidMap(Local_u32Light);

		Local_u16Distance = UltraSonic_u16Distance();

		if(Local_u16Distance < 50)
		{

			for(Local_u8Counter=0; Local_u8Counter<250; Local_u8Counter++)
			{
				DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);
				_delay_us(30);
				DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_LOW);
				_delay_us(30);

			}



		}
	}
	return 0;
}

void TempReading_Func(void)
{
	u8 Local_u8TempReading;
	Local_u8TempReading = LM35_u8TempRead(ADC_TempReading);

	if(Local_u8TempReading > 30)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
	}
	else
	{
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);

	}
}

