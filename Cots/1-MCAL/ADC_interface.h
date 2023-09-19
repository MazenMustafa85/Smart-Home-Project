/*
 * ADC_interface.h
 *
 *  Created on: Jul 24, 2023
 *      Author: conncet
 */


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


/*ADC Reference Selection*/
#define ADC_AREF								0
#define ADC_AVCC								1
#define ADC_INTERNAL							3


// Channel Selection
/*Single Ended Channel selection*/
#define ADC_SINGLE_ENDED_CHAN_0 				0
#define ADC_SINGLE_ENDED_CHAN_1					1
#define ADC_SINGLE_ENDED_CHAN_2					2
#define ADC_SINGLE_ENDED_CHAN_3					3
#define ADC_SINGLE_ENDED_CHAN_4					4
#define ADC_SINGLE_ENDED_CHAN_5					5
#define ADC_SINGLE_ENDED_CHAN_6					6
#define ADC_SINGLE_ENDED_CHAN_7					7


/*
 * Differential Channel Selection
 * TYPE - POSITIVE - NEGATIVE - GAIN  RESPECTIVELY
 */
#define DIFFERENTIAL_ADC0_ADC0_10X				8
#define DIFFERENTIAL_ADC1_ADC0_10X				9
#define DIFFERENTIAL_ADC0_ADC0_200X				10
#define DIFFERENTIAL_ADC1_ADC0_200X				11
#define DIFFERENTIAL_ADC2_ADC2_10X				12
#define DIFFERENTIAL_ADC3_ADC2_10X				13
#define DIFFERENTIAL_ADC2_ADC2_200X				14
#define DIFFERENTIAL_ADC3_ADC2_200X				15
#define DIFFERENTIAL_ADC0_ADC1_1X				16
#define DIFFERENTIAL_ADC1_ADC1_1X				17
#define DIFFERENTIAL_ADC2_ADC1_1X				18
#define DIFFERENTIAL_ADC3_ADC1_1X				19
#define DIFFERENTIAL_ADC4_ADC1_1X				20
#define DIFFERENTIAL_ADC5_ADC1_1X				21
#define DIFFERENTIAL_ADC6_ADC1_1X				22
#define DIFFERENTIAL_ADC7_ADC1_1X				23
#define DIFFERENTIAL_ADC0_ADC2_1X				24
#define DIFFERENTIAL_ADC1_ADC2_1X				25
#define DIFFERENTIAL_ADC2_ADC2_1X				26
#define DIFFERENTIAL_ADC3_ADC2_1X				27
#define DIFFERENTIAL_ADC4_ADC2_1X				28
#define DIFFERENTIAL_ADC5_ADC2_1X				29


/*ADC Prescaler Configuration*/
#define ADC_DIV_FACTOR_2						0
#define ADC_DIV_FACTOR_4						2
#define ADC_DIV_FACTOR_8						3
#define ADC_DIV_FACTOR_16						4
#define ADC_DIV_FACTOR_32						5
#define ADC_DIV_FACTOR_64						6
#define ADC_DIV_FACTOR_128						7

/*ADC Resolution*/
#define _8_BIT  								1
#define _10_BIT									2


#define FREE_RUNNING							0
#define ANALOG_COMPARATOR						1
#define EXTERNAL_INTERRUPT_REQUEST_0			2
#define	TIMER_0_COMPARE_MATCH					3
#define	TIMER_0_OVERFLOW						4
#define TIMER_COMPARE_MATCH_B					5
#define	TIMER_1_OVERFLOW						6
#define TIMER_1_CAPTURE_EVENT					7


typedef struct
{
	u8* Channel;
	u16* Result;
	u8 Size;
	void(*NotificationFunc)(void);
}Chain_t;

void ADC_Init(void);

u8 ADC_StartConversionSynch(u8 channel, u16* Reading);

u8 ADC_StartConversionAsynch(u8 channel, u16* Reading, void(*NotificationFunc)(void));

u8 ADC_u8StartChainAsynch(Chain_t *Copy_Chain);

void LDR_voidMap(u32 Copy_u16Value);

u32 ADC_voidGetAnalogRead(u8 Copy_Channel);


#endif /* ADC_INTERFACE_H_ */
