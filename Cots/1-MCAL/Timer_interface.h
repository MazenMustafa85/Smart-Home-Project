/*
 * Timer_interface.h
 *
 *  Created on: Aug 27, 2023
 *      Author: conncet
 */


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);

u8 TIMER0_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

void TIMER1_voidInit(void);

void TIMER1_voidSetICR(u16 Copy_u16TopValue);

void TIMER1_voidSetChannelCompareMatch(u16 Copy_u16CompareMatch);

void TIMER1_voidSetOVFInterrupt(void);

void TIMER1_voidSetNormalMode(void);


#endif /* TIMER_INTERFACE_H_ */

