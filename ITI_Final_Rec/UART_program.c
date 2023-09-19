/*

 * UART_Program.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Mazen
 */
#include "STD_Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_REGISTER.h"

void UART_voidInit(void)
{
	u8 UCSRC_Value = 0;

	/*Select Register UCSRC*/
	SET_BIT(UCSRC_Value,7); //0b10000000

	/*8Bits*/
	SET_BIT(UCSRC_Value,2);//0b10000100
	SET_BIT(UCSRC_Value,1);//0b10000110

	UCSRC=UCSRC_Value;

	/*Baud Rate 9600 bit/sec -> 51*/
	UBRRL=51;

	/*Enable */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);

}


void UART_voidSendData(u8 Copy_Data)
{
	/*wait Until Flag is one To sur that Empty*/
	while((GET_BIT(UCSRA,UCSRA_UDRE))==0);
	{
		UDR=Copy_Data;
	}
}

u8 UART_u8RecieveData(void)
{
	/*wait Until Uart Receive Data*/
	while((GET_BIT(UCSRA,UCSRA_RXC)==0));

	/*Receive the Data*/
	return UDR;
}
