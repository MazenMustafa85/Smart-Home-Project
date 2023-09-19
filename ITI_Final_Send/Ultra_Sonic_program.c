/*
 * Ultra_Sonic_program.c
 *
 *  Created on: Sep 4, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "Ultra_Sonic_config.h"
#include "Ultra_Sonic_interface.h"
#include "Timer_register.h"
#include <util/delay.h>

u16 UltraSonic_u16Distance(void)
{
	u16 count,TimerOverflow,distance;

	/* Give 10us trigger pulse on trigger pin to HC-SR04 */
	DIO_u8SetPinDirection(TRIGGER_PORT,TRIGGER_PIN,DIO_u8PIN_OUTPUT);

	DIO_u8SetPinValue(TRIGGER_PORT,TRIGGER_PIN,DIO_u8PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(TRIGGER_PORT,TRIGGER_PIN,DIO_u8PIN_LOW);

	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/  //1000001
	TIFR = 1<<TIFR_ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TIFR_TOV1;	/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) */

	while ((TIFR & (1 << TIFR_ICF1)) == 0);/* Wait for rising edge */
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR = 1<<TIFR_ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TIFR_TOV1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */

	while ((TIFR & (1 << TIFR_ICF1)) == 0);/* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take count */
	/* 8MHz Timer frequancy sound speed =343 m/s */
	distance = (f64)count / 466.47;

	return distance;

}
