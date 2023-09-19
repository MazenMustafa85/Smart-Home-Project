/*


 * SERVO_PROGRAM.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Mazen
 */
#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SERVO_REGISTER.h"




void Servo_Init(void)
{
	/*Select Mode 14 From Timer1*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*Clear OC1A on Compare Match,SET OC1A on OverFlow */
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	/*Make OC1A OUTPUT From PINDIRECTION to Generate PWM */
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN5, DIO_u8PIN_OUTPUT);

	/*Pre_Scaler */
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);


	/*Set New Value For Overflow*/
	ICR1=19999;

}

void Servo_SetAngle(u16 Copy_Angle)
{
	//0->999,90->1500,180->2000
	OCR1A_REG=999+ ((50.0f/9)*Copy_Angle);

}


