/*
 * LM35_interface.h
 *
 *  Created on: Aug 1, 2023
 *      Author: conncet
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#define RESOLUTION_10_BITS				1024UL

#define RESOLUTION_8_BITS				256UL


u8 LM35_u8TempRead(u16 A_u16ADCReading);

#endif /* LM35_INTERFACE_H_ */
