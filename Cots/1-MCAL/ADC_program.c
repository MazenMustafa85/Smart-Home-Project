/*
 * ADC_program.c
 *
 *  Created on: Jul 24, 2023
 *      Author: conncet
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "DIO_interface.h"

u8 ADC_FUNCTION_BUSY = IDLE;
static u8* ADC_pu8ChainChannelArr = NULL;		/*Global variable to carry chain array*/
static u8* ADC_pu8ChainSize = NULL;				/*Global variable to carry number of channels*/
static u16* ADC_pu16ChainResultArr = NULL;		/*Global variable to carry chain result*/
static u8 ADC_u8ChainConvrsionIndex = 0;		/*Global variable to carry current conversion index*/

static u8 ADC_u8ISR_Source;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;
static u16* ADC_pu16Reading = NULL;

void ADC_Init(void)
{
	/*Reference Selection*/
#if(REFERENCE_SELECTION == ADC_AVCC)
	/*AVCC as reference voltage*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif(REFERENCE_SELECTION == ADC_AREF)
	/*AREF as reference voltage*/
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif(REFERENCE_SELECTION == ADC_INTERNAL)
	/*Internal 2.56V voltage as reference voltage*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else

#warning "Wrong Reference Selction Config"

#endif

#if(ADC_RESOLUTION == _8_BIT)
	/*Activate left adjust result*/
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif(ADC_RESOLUTION == _10_BIT)
	/*Activate right adjust result*/
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else

#warning "Wrong ADC Resolution"

#endif

	/*Clear Current ADC Prescaler*/
	CLR_BIT(ADCSRA, ADCSRA_ADPS2);
	CLR_BIT(ADCSRA, ADCSRA_ADPS1);
	CLR_BIT(ADCSRA, ADCSRA_ADPS0);

	/*Set Required Prescaler from the config file*/
	ADCSRA |= ADC_PRESCALLER_SELECTION;

	/*ADC Trigger Source Selection*/
	SFIOR &= ADC_TRIGGER_SOURCE_MASK;
	SFIOR |= ADC_TRIGGER_SOURCE << 5;

	/*ADC enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

#if(ADC_TRIGGER_SOURCE != FREE_RUNNING)
	/*Enable Auto Trigger Mode*/
	SET_BIT(ADCSRA, ADCSRA_ADATE);

	/*Start first conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);
#endif

}

u8 ADC_StartConversionSynch(u8 channel, u16* Reading)
{
	u32 Counter = 0;
	u8 ErrorState = OK;

	if(ADC_FUNCTION_BUSY == IDLE)
	{
		ADC_FUNCTION_BUSY = BUSY;

		/*Clear the MUX bits in ADMUX register*/
		ADMUX &= ADC_ADMUX_MASK;

		/*Set the required channel into the MUX bits*/
		ADMUX |= channel;

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/*Polling (busy waiting) until the conversion complete flag is set or counter reaching timeout value*/
		while((GET_BIT(ADCSRA, ADCSRA_ADIF)==0) && (Counter != ADC_TIMEOUT))
		{
			Counter++;
		}
		if(Counter == ADC_TIMEOUT)
		{
			/*Loop is broken because timeout is reached*/
			ErrorState = NOK;
		}
		else
		{
			/*Loop is broken because flag is raised*/
			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA, ADCSRA_ADIF);

			/*Return the reading*/
#if(ADC_RESOLUTION == _8_BIT)
			*Reading = ADCH;
#elif(ADC_RESOLUTION == _10_BIT)
			*Reading = ADC;
#else
#warning "You have used a wrong ADC Resolution, please use appropriate one"
#endif

			ADC_FUNCTION_BUSY = IDLE;
		}
	}
	else
	{
		ErrorState = BUSY_FUNC;
	}

	return ErrorState;

}

u8 ADC_StartConversionAsynch(u8 channel, u16* Reading, void(*NotificationFunc)(void))
{
	u8 ErrorState = OK;

	if(ADC_FUNCTION_BUSY == IDLE)
	{
		if((Reading == NULL) || (NotificationFunc == NULL))
		{
			ErrorState = NULL_POINTER;
		}
		else
		{
			/*Make ADC busy in order not to work until being idle*/
			ADC_FUNCTION_BUSY = BUSY;

			/*make ISR source: single channel asynchronous*/
			ADC_u8ISR_Source = SINGLE_CHANNEL_ASYNCH;

			/*Initialize the reading variable globally*/
			ADC_pu16Reading = Reading;

			/*Initialize the callback notification function globally*/
			ADC_pvCallBackNotificationFunc = NotificationFunc;

			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_ADMUX_MASK;

			/*Set the required channel into the MUX bits*/
			ADMUX |= channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
	}
	else
	{
		ErrorState = NOK;
	}
	return ErrorState;
}

u8 ADC_u8StartChainAsynch(Chain_t *Copy_Chain)
{
	u8 Local_u8ErrorState = OK;

	/*Check NULL pointer*/
	if(Copy_Chain == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		if(ADC_FUNCTION_BUSY == IDLE)
		{
			/*Make ADC busy*/
			ADC_FUNCTION_BUSY = BUSY_FUNC;

			/*Make ISR source: chain Asynchronous*/
			ADC_u8ISR_Source = CHAIN_ASYNCH;

			/*Initialize chain Channel Array*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;

			/*Initialize result Array*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;

			/*Initialize Chain size*/
			ADC_pu8ChainSize = Copy_Chain->Size;

			/*Initialize Notification function*/
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotificationFunc;

			/*Initialize current conversion index*/
			ADC_u8ChainConvrsionIndex = 0;

			/*Set Required channel(first channel)*/
			ADMUX &= ADC_ADMUX_MASK;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConvrsionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable conversion complete interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}

	return Local_u8ErrorState;
}


void LDR_voidMap(u32 Copy_u16Value)
{
	if(Copy_u16Value <= 4975  && Copy_u16Value>3845)
	{
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);


	}
	else if(Copy_u16Value <= 3845  && Copy_u16Value>2715)
	{
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);

	}
	else if(Copy_u16Value <= 2715  && Copy_u16Value>1585)
	{
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);

	}
	else if(Copy_u16Value <= 1585  && Copy_u16Value>454)
	{
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);

	}
}


u32 ADC_voidGetAnalogRead(u8 Copy_Channel)
{
	u32 Local_u32ADCDigitalValue ;
	u32 Local_u32ADCAnalogValue ;

	//clear Mux from 0 to 4 (reg&0b11100000)
	ADMUX &= 0b11100000 ;
	//reg or with copy_channel
	ADMUX |= Copy_Channel ;
	//start conversion
	SET_BIT(ADCSRA , ADCSRA_ADSC);
	//polling flag
	while(GET_BIT(ADCSRA, ADCSRA_ADIF)==0);
	//clear flag
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	//get reading right adjust
	Local_u32ADCDigitalValue = ADCL + (ADCH << 8) ;

	Local_u32ADCAnalogValue = (Local_u32ADCDigitalValue * 5000) / 1024 ;


	return Local_u32ADCAnalogValue;
}

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISR_Source == SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC result*/
#if(ADC_RESOLUTION == _8_BIT)
		*ADC_pu16Reading = ADCH;
#elif(ADC_RESOLUTION == _10_BIT)
		*ADC_pu16Reading = ADC;
#else
#warning "You have used a wrong ADC Resolution, please use appropriate one"
#endif

		/*Make ADC state be idle because it finished*/
		ADC_FUNCTION_BUSY = IDLE;

		/*Invoke the callback notification function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);
	}
	else if(ADC_u8ISR_Source == CHAIN_ASYNCH)
	{
		/*Read the current conversion*/
		ADC_pu16ChainResultArr[ADC_u8ChainConvrsionIndex] = ADCH;

		/*Increment chain index*/
		ADC_u8ChainConvrsionIndex++;

		/*Check chain is finished or not*/
		if(ADC_u8ChainConvrsionIndex == ADC_pu8ChainSize)
		{
			/*Chain is finished*/
			/*ADC is now IDLE*/
			ADC_FUNCTION_BUSY = IDLE;

			/*Invoke the call back notification function*/
			ADC_pvCallBackNotificationFunc();

			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*Chain is not finished*/
			/*Set new required channel*/
			ADMUX &= ADC_ADMUX_MASK;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainConvrsionIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}

}


