/*
 * STM32F401_KEYPAD.h
 *
 *  Created on: Mar 4, 2026
 *      Author: SD
 */

#ifndef STM32F401_KEYPAD_H_
#define STM32F401_KEYPAD_H_
#include "STM32F401_GPIO.h"
// Generic Structure for the KEYBOARD
typedef struct
{
	uint8_t rows[4];
	uint8_t cols[4];
	GPIO_RegDef_t * Rp;
	GPIO_RegDef_t * Cp;
}Keypad_Handle_t;
//API CODE to Activate the KEYBOARD
void InitKeypad(Keypad_Handle_t * pkey);
char Press_Key(Keypad_Handle_t * pkey);
#endif /* STM32F401_KEYPAD_H_ */
