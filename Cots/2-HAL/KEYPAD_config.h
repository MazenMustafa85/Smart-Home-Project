/*********************************************************/
/*********************************************************/
/**************     Author: Ahmed Osama    ***************/
/**************     Layer:  HAL            ***************/
/**************     Component: KEYPAD      ***************/
/**************     Version:1.00           ***************/
/*********************************************************/
/*********************************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_



#define KEYPAD_PORT          DIO_u8PORTC

#define KEYPAD_COLUMN0_PIN   DIO_u8PIN4
#define KEYPAD_COLUMN1_PIN   DIO_u8PIN5
#define KEYPAD_COLUMN2_PIN   DIO_u8PIN6
#define KEYPAD_COLUMN3_PIN   DIO_u8PIN7

#define KEYPAD_ROW0_PIN      DIO_u8PIN0
#define KEYPAD_ROW1_PIN      DIO_u8PIN1
#define KEYPAD_ROW2_PIN      DIO_u8PIN2
#define KEYPAD_ROW3_PIN      DIO_u8PIN3



#define KEYPAD_ARR_VAL {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'E','0','=','+'}}


#endif /* KEYPAD_CONFIG_H_ */
