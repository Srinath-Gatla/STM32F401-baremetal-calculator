/*
 * STM32F401_KEYPAD.c
 *
 *  Created on: Mar 4, 2026
 *      Author: SD
 */
#include "STM32F401_KEYPAD.h"
// 2X2 matrix for the KEYPAD, this varies with respect to what the keypad you have with
static char keypad[4][4]=
{
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'c','0','=','+'},
};
// Initialize the Keypad
void InitKeypad(Keypad_Handle_t * pKey)
{
	//initialize the clock
	GPIO_PLLCLK_Init(pKey->Rp,ENABLE);
    GPIO_PLLCLK_Init(pKey->Cp,ENABLE);
	// for Rows
    GPIO_Handle_t GPIO_KEY;
    GPIO_KEY.pGPIOx=pKey->Rp;
    GPIO_KEY.GPIO_config.GPIO_PinMode=GPIO_MODE_OUT;
    GPIO_KEY.GPIO_config.GPIO_PinOptype=GPIO_OP_TYPE_PP;
    GPIO_KEY.GPIO_config.GPIO_PinSpeed=2;
    GPIO_KEY.GPIO_config.GPIO_Pinpupdcontrol=GPIO_NO_PUPD;

    for(uint8_t i=0;i<4;i++)
    {
    	GPIO_KEY.GPIO_config.GPIO_PinNumber=pKey->rows[i];
    	GPIO_Init(&GPIO_KEY);

    	GPIO_Write_Pin(pKey->Rp,pKey->rows[i],GPIO_PIN_SET);
    }
	// For the Coloums
	GPIO_KEY.pGPIOx=pKey->Cp;
	GPIO_KEY.GPIO_config.GPIO_PinMode=GPIO_MODE_IN;
	GPIO_KEY.GPIO_config.GPIO_PinOptype=GPIO_OP_TYPE_PP;
	GPIO_KEY.GPIO_config.GPIO_PinSpeed=2;
	GPIO_KEY.GPIO_config.GPIO_Pinpupdcontrol=GPIO_PIN_PU;
	for(uint8_t j=0;j<4;j++)
	{
		GPIO_KEY.GPIO_config.GPIO_PinNumber=pKey->cols[j];
		GPIO_Init(&GPIO_KEY);
	}
}
// Press the key and C program related to it
char Press_Key(Keypad_Handle_t * pkey)
{
	for(uint8_t row=0;row<4;row++)
	{
		// set and clear all the pins of port A
		for(uint8_t i=0;i<4;i++)
		{
			GPIO_Write_Pin(pkey->Rp,pkey->rows[i],GPIO_PIN_SET);
		}
		GPIO_Write_Pin(pkey->Rp,pkey->rows[row],GPIO_PIN_RESET);
		for(uint32_t d=0;d<3000;d++);
		for(uint8_t col=0;col<4;col++)
		{
			if((GPIO_Read_Pin(pkey->Cp,pkey->cols[col]))==0)
			{
				while((GPIO_Read_Pin(pkey->Cp,pkey->cols[col]))==0);
				return keypad[row][col];
			}
		}
	}
	return 0;
}
