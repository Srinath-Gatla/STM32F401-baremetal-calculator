/*
 * STM32F401_LCD.h
 *  Created on: Mar 6, 2026
 *  Author: SD
 */
#ifndef STM32F401_LCD_H_
#define STM32F401_LCD_H_
#include "STM32F401XX.h"
#include "STM32F401_GPIO.h"
//LCD_Defines_Generic Structure
typedef struct
{
	GPIO_Handle_t data[8];
	GPIO_Handle_t RS;
	GPIO_Handle_t RW;
	GPIO_Handle_t EN;
}LCD_Handle_t;
//HD44780 Commands
#define CLEAR_LCD                 0x01
#define RET_CUR_HOME              0x02
#define ENTRY_MODE_RIGHT          0x06
#define ENTRY_MODE_RIGHT_SHIFT    0x07
#define ENTRY_MODE_LEFT           0x04
#define ENTRY_MODE_LEFT_SHIFT     0x05
#define DSP_OFF                   0x08
// defines for the Cursor
#define DSP_ON_CUR_OFF       0x0C
#define DSP_ON_CUR_ON        0x0E
#define DSP_ON_CUR_BLINK     0x0F
#define SHIFT_DISP_LEFT      0x10
#define SHIFT_DISP_RIGHT     0x14
// defines for the Data Display
#define MODE_8BIT_1LINE      0x30
#define MODE_4BIT_1LINE      0x20
#define MODE_8BIT_2LINE      0x38
#define MODE_4BIT_2LINE      0x28
#define GOTO_LINE1_POS0      0x80
#define GOTO_LINE2_POS0      0xC0
#define GOTO_LINE3_POS0      0x94
#define GOTO_LINE4_POS0      0xD4
#define GOTO_CGRAM_START     0x40
// write the code for the API
void delay(void);
void LCD_Enable(LCD_Handle_t * Lp);
void InitLCD(LCD_Handle_t * Lp);
void CharLCD(LCD_Handle_t * Lp, uint8_t asciival );
void StrLCD(LCD_Handle_t * Lp,char * str);
void NumLCD(LCD_Handle_t * Lp,uint32_t num);
void FloatLCD(LCD_Handle_t * Lp,float num,uint32_t decimal);
void CmdLCD(LCD_Handle_t * Lp,uint8_t cmd);
void writeLCD(LCD_Handle_t * Lp,uint8_t data);
#endif /* STM32F401_LCD_H_ */
