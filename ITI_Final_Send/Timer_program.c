/*
 * Timer_program.c
 *
 *  Created on: Aug 27, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer_interface.h"
#include "Timer_config.h"
#include "Timer_register.h"
#include "Timer_private.h"

static void (*TIMER0_pvCallBackFunc)(void)=NULL;

void TIMER0_voidInit(void)
{
	/*Choose CTC mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Output compare match interrupt enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Set compare match value to 250*/
	OCR0 = 250;
	/*Prescaler division by 8*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

}

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErorrStatus = OK;

	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Copy_pvCallBackFunc = NULL_POINTER;
	}
	return Local_u8ErorrStatus;
}
void TIMER1_voidInit(void)
{
	/*Fast PWM non inverting mode*/
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Set wave form for fast PWM */
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*Set prescaler */
	TCCR1B &= PRESCALER_MASK;
	TCCR1B |= DIVIDE_BY_8;
}

void TIMER1_voidSetICR(u16 Copy_u16TopValue)
{
	ICR1 = Copy_u16TopValue;
}

void TIMER1_voidSetChannelCompareMatch(u16 Copy_u16CompareMatch)
{
	OCR1A = Copy_u16CompareMatch;
}

void TIMER1_voidSetOVFInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TOIE1);
}

void TIMER1_voidSetNormalMode(void)
{
	TCCR1A = 0;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}
