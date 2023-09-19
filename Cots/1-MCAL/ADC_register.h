/*
 * ADC_register.h
 *
 *  Created on: Jul 24, 2023
 *      Author: conncet
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_


#define	ADMUX			*((volatile u8*)0x27)		//ADC multiplexer selection register
#define ADMUX_REFS1		7							//Reference selection bit1
#define ADMUX_REFS0		6							//Reference selection bit0
#define ADMUX_ADLAR		5							//ADC left adjust result
#define ADMUX_MUX4		4
#define ADMUX_MUX3		3
#define ADMUX_MUX2		2
#define ADMUX_MUX1		1
#define ADMUX_MUX0		0


#define	ADCSRA			*((volatile u8*)0x26)		//ADC control and status register A
#define ADCSRA_ADEN		7							//ADC enable
#define ADCSRA_ADSC		6							//ADC start conversion
#define ADCSRA_ADATE	5							//ADC auto trigger enable
#define ADCSRA_ADIF		4							//ADC interrupt flag
#define ADCSRA_ADIE		3							//ADC interrupt enable
#define ADCSRA_ADPS2	2							//Prescaler bit2
#define ADCSRA_ADPS1	1							//Prescaler bit1
#define ADCSRA_ADPS0	0							//Prescaler bit0


#define	ADCH		*((volatile u8*)0x25)			//ADC high register


#define	ADCL		*((volatile u8*)0x24)			//ADC low register

#define SFIOR		*((volatile u8*)0x50)			//Special Function I/O Register

#define	ADC			*((volatile u16*)0x24)			//ADC 2 byte register

#endif /* ADC_REGISTER_H_ */
