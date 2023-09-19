/*
 * Timer_register.h
 *
 *  Created on: Aug 27, 2023
 *      Author: conncet
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


#define TCNT0			*((volatile u8*)0x52)

#define OCR0			*((volatile u8*)0x5C)	/*Output compare register 0*/

#define TCCR0			*((volatile u8*)0x53)	/*Timer0 control register*/
#define TCCR0_WGM01		3						/*Waveform generation mode bit0*/
#define TCCR0_WGM00		6						/*Waveform generation mode bit1*/
#define TCCR0_COM00		4
#define TCCR0_COM01		5
#define TCCR0_CS00		0						/*Prescaler bit0*/
#define TCCR0_CS01		1						/*Prescaler bit1*/
#define TCCR0_CS02		2						/*Prescaler bit2*/

#define TIMSK			*((volatile u8*)0x59)	/*Timer mask*/
#define TIMSK_TOIE0		0
#define TIMSK_OCIE0		1						/*Output compare 0 interrupt enable*/
#define TIMSK_TOIE1		2
#define TIMSK_OCIE1B	3
#define TIMSK_OCIE1A	4
#define TIMSK_TICIE1	5


#define TCCR1A			*((volatile u8*)0x4F)
#define TCCR1A_WGM10	0
#define TCCR1A_WGM11	1
#define TCCR1A_COM1A1	7
#define TCCR1A_COM1A0	6

#define TCCR1B			*((volatile u8*)0x4E)
#define TCCR1B_WGM13	4
#define TCCR1B_WGM12	3

#define ICR1			*((volatile u16*)0x46)
#define OCR1A			*((volatile u16*)0x4A)

#define TIFR			*((volatile u16*)0x58)	/*Timer1 interrupt flag*/
#define TIFR_TOV1		2
#define TIFR_OCF1B		3
#define TIFR_OCF1A		4
#define TIFR_ICF1		5

#define TCNT1			*((volatile u16*)0x4C)


#endif /* TIMER_REGISTER_H_ */
