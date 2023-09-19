/*
 * UART_interface.h
 *
 *  Created on: Aug 29, 2023
 *      Author: conncet
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);

void UART_voidSendData(u8 Copy_u8Data);

u8 UART_u8RecieveData(void);

#endif /* UART_INTERFACE_H_ */
