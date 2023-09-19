/*
 * main_reciveve.c
 *
 *  Created on: Aug 29, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "APP_interface.h"
#include "SERVO_INTERFACE.h"
#include "DC_Motor_interface.h"
#include <util/delay.h>

void main(void)
{

	/*Users Password*/
	u8 arr0[] = {'1','2','3','4'};
	u8 arr1[] = {'5','6','7','8'};
	u8 arr2[] = {'0','0','0','0'};

	u8 Local_u8Counter,Local_u8PressedKey,Local_u8Flag,Local_u8Password[4];
	u32 Local_u32Num1=0,Local_u32Num2=0;
	u8 Local_u8Operand=0,Local_u8Failed=1;

	/*PORTC output for LCD data pins*/
	DIO_u8SetPortDirection(DIO_u8PORTC,DIO_u8PORT_OUTPUT);

	/*PORTA output*/
	DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);

	/*TX output*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_OUTPUT);

	/*RX input*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_INPUT);

	/*PORTB output*/
	DIO_u8SetPortDirection(DIO_u8PORTB,DIO_u8PORT_OUTPUT);

	/*PD2 output for buzzer*/
	DIO_u8SetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_OUTPUT);

	Servo_Init();
	UART_voidInit();
	CLCD_voidInit();
	Servo_SetAngle(90);
	while(1)
	{
		/*Clear LCD*/
		CLCD_voidSendCommand(1);
		CLCD_voidPosition(0,0);
		CLCD_voidSendString("Enter Password");
		CLCD_voidPosition(1,0);
		for(Local_u8Counter=0; Local_u8Counter<4; Local_u8Counter++)
		{
			Local_u8Password[Local_u8Counter] = UART_u8RecieveData();
			CLCD_voidSendData('*');
		}

		/*Clear LCD*/
		CLCD_voidSendCommand(1);


		if(Check_Password(arr0,Local_u8Password) == 1)
		{
			Local_u8Flag = 1;
			CLCD_voidSendString("Welcome AHMED");
			Servo_SetAngle(180);
			_delay_ms(500);
		}
		else if(Check_Password(arr1,Local_u8Password) == 1)
		{
			Local_u8Flag = 1;
			CLCD_voidSendString("Welcome OMAR");
			Servo_SetAngle(180);
			_delay_ms(500);
		}
		else if(Check_Password(arr2,Local_u8Password) == 1)
		{
			Local_u8Flag = 1;
			CLCD_voidSendString("Welcome SAMAA");
			Servo_SetAngle(180);
			_delay_ms(500);
		}
		else
		{
			Local_u8Flag = 0;
			if(Local_u8Failed < 3)
			{

				CLCD_voidSendString("Try Again");
				AlarmSound();
				CLCD_voidPosition(1,0);
				CLCD_voidWriteNumber(Local_u8Failed);
				_delay_ms(1000);
				Local_u8Failed++;
			}
			else if(Local_u8Failed == 3)
			{
				CLCD_voidSendCommand(1);
				CLCD_voidSendString("Login failed");
				CLCD_voidPosition(1,0);
				CLCD_voidSendString("Wait 3 seconds");
				_delay_ms(3000);
			}

		}

		/*Clear LCD*/
		CLCD_voidSendCommand(1);

		if(Local_u8Flag == 1)
		{
			while(1)
			{
				CLCD_voidSendCommand(1);

				CLCD_voidPosition(0,0);
				CLCD_voidSendString("1-Light");
				CLCD_voidPosition(0,8);
				CLCD_voidSendString("2-Window");
				CLCD_voidPosition(1,0);
				CLCD_voidSendString("3-Calculator");

				Local_u8PressedKey = UART_u8RecieveData();


				switch(Local_u8PressedKey)
				{


				/*Case 1 for light mode*/
				case '1':
					CLCD_voidSendCommand(1);
					CLCD_voidPosition(0,0);
					CLCD_voidSendString("1-Room1");
					CLCD_voidPosition(0,8);
					CLCD_voidSendString("2-Room2");
					CLCD_voidPosition(1,0);
					CLCD_voidSendString("3-Exit");

					Local_u8PressedKey = UART_u8RecieveData();
					switch(Local_u8PressedKey)
					{
					case '1':
						CLCD_voidSendCommand(1);
						CLCD_voidPosition(0,0);
						CLCD_voidSendString("1-Room1 ON");
						CLCD_voidPosition(1,0);
						CLCD_voidSendString("2-Room1 OFF");
						Local_u8PressedKey = UART_u8RecieveData();

						switch(Local_u8PressedKey)
						{
						case '1':
							Room1_ON();
							break;
						case '2':
							Room1_OFF();
							break;
						}break;
						case '2':
							CLCD_voidSendCommand(1);
							CLCD_voidPosition(0,0);
							CLCD_voidSendString("1-Room2 ON");
							CLCD_voidPosition(1,0);
							CLCD_voidSendString("2-Room2 OFF");
							Local_u8PressedKey = UART_u8RecieveData();
							switch(Local_u8PressedKey)
							{
							case '1':
								Room2_ON();

								break;
							case '2':
								Room2_OFF();
								break;
							}break;
							case '3':
								break;
							default:
								CLCD_voidSendCommand(1);
								CLCD_voidPosition(0,0);
								CLCD_voidSendString("Wrong Input");
								_delay_ms(500);
					}
					break;
					/*case 2 for window mode*/
					case '2':
						CLCD_voidSendCommand(1);
						CLCD_voidPosition(0,0);
						CLCD_voidSendString("1-Open window");
						CLCD_voidPosition(1,0);
						CLCD_voidSendString("2-Close window");
						Local_u8PressedKey = UART_u8RecieveData();
						switch(Local_u8PressedKey)
						{
						case '1':
							Motor_Clockwise();
							break;
						case '2':
							Motor_Anticlockwise();
							break;
						default:
							CLCD_voidSendCommand(1);
							CLCD_voidPosition(0,0);
							CLCD_voidSendString("Wrong Input");
							_delay_ms(500);
						}
						break;
						/*case 3 for calculator*/
						case '3':
							CLCD_voidSendCommand(1);
							while(1)
							{
								Local_u8PressedKey = UART_u8RecieveData();// 1  +
								if(Local_u8PressedKey == 'E')
								{
									break;
								}
								if (Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9')
								{

									if (Local_u8Operand == 0)// operator 0
									{
										Local_u32Num1 = Local_u32Num1 * 10 + (Local_u8PressedKey - '0');

									}
									else
									{
										Local_u32Num2 = Local_u32Num2 * 10 + (Local_u8PressedKey - '0');
									}
									CLCD_voidSendData(Local_u8PressedKey);// 1
								}
								else if (Local_u8PressedKey == '+' || Local_u8PressedKey == '-' || Local_u8PressedKey == '*' || Local_u8PressedKey == '/')
								{
									Local_u8Operand = Local_u8PressedKey; // operator =  +
									CLCD_voidSendData(Local_u8PressedKey); // LCD +
								}
								else if (Local_u8PressedKey == '=')
								{
									u32 ResultValue;
									switch (Local_u8Operand)
									{
									case '+':
										ResultValue = Local_u32Num1 + Local_u32Num2;
										break;
									case '-':
										ResultValue = Local_u32Num1 - Local_u32Num2;
										break;
									case '*':
										ResultValue = Local_u32Num1 * Local_u32Num2;
										break;
									case '/':
										if (Local_u32Num2 != 0)
										{
											ResultValue = Local_u32Num1 / Local_u32Num2;
										}
										else
										{
											CLCD_voidSendCommand(1);
											CLCD_voidSendString("Error: Division by zero");
											_delay_ms(2000);
											CLCD_voidSendCommand(1);
											Local_u32Num1 = 0;
											Local_u32Num2 = 0;
											Local_u8Operand = 0;
											continue;
										}
										break;
									}
									CLCD_voidSendData('=');
									// LCD_SendCommand(1);
									CLCD_voidWriteNumber(ResultValue);
									Local_u32Num1 = 0;
									Local_u32Num2 = 0;
									Local_u8Operand = 0;
								}

							}
							break;
							/*case '+' for more options*/
						case'+':
							CLCD_voidSendCommand(1);
							CLCD_voidPosition(0,0);
							CLCD_voidSendString("4-Door");
							CLCD_voidPosition(0,7);
							CLCD_voidSendString("5-Music");
							Local_u8PressedKey = UART_u8RecieveData();
							switch(Local_u8PressedKey)
							{
							case '4':
								CLCD_voidSendCommand(1);
								CLCD_voidPosition(0,0);
								CLCD_voidSendString("1-Open door");
								CLCD_voidPosition(1,0);
								CLCD_voidSendString("2-Close door");
								Local_u8PressedKey = UART_u8RecieveData();
								switch(Local_u8PressedKey)
								{
								case '1':
									Servo_SetAngle(180);
									break;
								case '2':
									Servo_SetAngle(90);
									break;
								}break;
								case '5':
									for(Local_u8Counter=0;Local_u8Counter<2; Local_u8Counter++)
									{
										MusicSound();
									}
							}
							break;

							default:
								CLCD_voidSendCommand(1);
								CLCD_voidPosition(0,0);
								CLCD_voidSendString("Wrong Input");
								_delay_ms(500);
				}
			}
		}
	}
}
