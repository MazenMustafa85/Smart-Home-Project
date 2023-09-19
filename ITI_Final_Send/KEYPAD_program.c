/*********************************************************/
/*********************************************************/
/**************     Author: AhmedOsama    ***************/
/**************     Layer:  HAL            ***************/
/**************     Component: KEYPAD      ***************/
/**************     Version:1.00           ***************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include <util/delay.h>

void KEYPAD_Init(void)
{

	/*Columns as output*/
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COLUMN0_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COLUMN1_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COLUMN2_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_COLUMN3_PIN,DIO_u8PIN_OUTPUT);

	/*Rows as input*/
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW0_PIN,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW1_PIN,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW2_PIN,DIO_u8PIN_INPUT);
	DIO_u8SetPinDirection(KEYPAD_PORT,KEYPAD_ROW3_PIN,DIO_u8PIN_INPUT);

	/*Colomns high and rows pullup*/
	DIO_u8SetPortValue(KEYPAD_PORT,DIO_u8PORT_HIGH);

}


u8 KEYPAD_GetKeyPressed(void)
{
	u8 PressedKey = KEYPAD_NotPressed, Column_Index, Row_Index,Pin_State,Local_u8Flag = 0;
	u8 KEYPAD_Array[Row_Num][Column_Num]= KEYPAD_ARR_VAL;
	u8 KEYPAD_Column_ARR[Column_Num]={KEYPAD_COLUMN0_PIN,KEYPAD_COLUMN1_PIN,KEYPAD_COLUMN2_PIN,KEYPAD_COLUMN3_PIN};
	u8 KEYPAD_Row_ARR[Row_Num]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN};

	for(Column_Index=0;Column_Index<Column_Num;Column_Index++)
	{
		/* Activate current column*/
		DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_Column_ARR[Column_Index],DIO_u8PIN_LOW);

		for(Row_Index=0;Row_Index<Row_Num;Row_Index++)
		{
			/*Read current row*/
			DIO_u8GetPinValue(KEYPAD_PORT,KEYPAD_Row_ARR[Row_Index],&Pin_State);

			/*Check if switch is pressed*/
			if(DIO_u8PORT_LOW == Pin_State)
			{
				PressedKey = KEYPAD_Array[Row_Index][Column_Index];

				/*Polling(busy waiting) until the key is released*/
				while(DIO_u8PORT_LOW == Pin_State)
				{
					DIO_u8GetPinValue(KEYPAD_PORT,KEYPAD_Row_ARR[Row_Index],&Pin_State);
				}

				Local_u8Flag = 1;
				break;
			}
		}

		/*Deactivate the current column*/
		DIO_u8SetPinValue(KEYPAD_PORT,KEYPAD_Column_ARR[Column_Index],DIO_u8PIN_HIGH);
		if(Local_u8Flag == 1)
			break ;
	}

	return PressedKey;
}


u8 KPD_Get_key(void)
{
	int key_value;
	key_value = KEYPAD_GetKeyPressed();
	while(key_value == KEYPAD_NotPressed) // polling
	{
		key_value = KEYPAD_GetKeyPressed();
	}
	return key_value;
}
