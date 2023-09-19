/*
 * ADC_privet.h
 *
 *  Created on: Jul 24, 2023
 *      Author: conncet
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADC_TRIGGER_SOURCE_MASK		0b00011111

#define ADC_ADMUX_MASK				0b11100000

#define IDLE						0 // Function is not busy
#define BUSY						1 // Function is busy doing another job

#define	SINGLE_CHANNEL_ASYNCH		0
#define CHAIN_ASYNCH				1

#endif /* ADC_PRIVATE_H_ */
