/*
 * ADC_config.h
 *
 *  Created on: Jul 24, 2023
 *      Author: conncet
 */


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define REFERENCE_SELECTION			ADC_AVCC

#define ADC_RESOLUTION				_10_BIT

#define ADC_PRESCALLER_SELECTION	ADC_DIV_FACTOR_128

#define ADC_TRIGGER_SOURCE			FREE_RUNNING

#define ADC_TIMEOUT 				50000


#endif /* ADC_CONFIG_H_ */
