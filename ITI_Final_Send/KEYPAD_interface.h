/*
 * KEYPAD_interface.h
 *
 *  Created on: May 12, 2023
 *      Author: conncet
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


void KEYPAD_Init(void);

u8 KEYPAD_GetKeyPressed(void);

u8 KPD_Get_key(void);

#define KEYPAD_NotPressed    0xff


#endif /* KEYPAD_INTERFACE_H_ */
