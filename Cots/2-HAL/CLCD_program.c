/*********************************************************/
/*********************************************************/
/**************     Author: Ahmed Osama    ***************/
/**************     Layer:  MCAL           ***************/
/**************     SWC:    CLCD           ***************/
/**************     Version:1.00           ***************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "CLCD_coinfig.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include <util/delay.h>

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS pin to low for commend*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*Set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set commend to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS pin to high for commend*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

		/*Set RW pin to low for write*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

		/*Set data to data pins*/
		DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidInit(void)
{
	/*Wait for more than 30ms*/
	_delay_ms(40);

	/*Function set commend: 2 lines(N), 5*8 font size(F)*/
	CLCD_voidSendCommand(0b00111000);

	/*Display on off control: display enable(D), disable cursor(C), no blink cursor(B)*/
	CLCD_voidSendCommand(0b00001100);

	/*Clear display*/
	CLCD_voidSendCommand(1);
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_voidPosition(u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	u8 Local_u8Address;
	
	if(Copy_u8XPosition == 0)
	{
		Local_u8Address=Copy_u8YPosition;
	}
	else if(Copy_u8XPosition == 1)
	{
		Local_u8Address=Copy_u8YPosition+0x40;
	}
	CLCD_voidSendCommand(Local_u8Address+128);
}

void CLCD_voidWriteSpecielCharacter(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber,u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	u8 Local_u8CGRAMAddress = 0, Local_u8Iterator;
	/*calculate CGRAM address ehose each block is 8 byte*/
	Local_u8CGRAMAddress = Copy_u8PatternNumber*8;
	
	/*Send CGRAM address command to LCD, With setting bit 6, clearing bit 7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);
	
	/*Write the pattern into CGRAM*/
	for(Local_u8Iterator=0; Local_u8Iterator<8; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/*Go back to display the pattern*/
	CLCD_voidPosition(Copy_u8XPosition,Copy_u8YPosition);
	
	/*Display the pattern number written in CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}

void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	u8 DigitNumberArr[20];
	u8 Local_u8Temp;
	u8 Local_u8Counter1=0;
	s8 Local_u8Counter2;

	if(Copy_u32Number != 0)
	{
		while(Copy_u32Number > 0)
		{
			Local_u8Temp = Copy_u32Number%10;
			DigitNumberArr[Local_u8Counter1] = Local_u8Temp;
			Copy_u32Number = Copy_u32Number/10;
			Local_u8Counter1++;
		}
		for(Local_u8Counter2=Local_u8Counter1-1; Local_u8Counter2>=0; Local_u8Counter2--)
		{
			CLCD_voidSendData(48 + DigitNumberArr[Local_u8Counter2]);
		}
	}
	else
	{
		CLCD_voidSendData('0');
	}
}


