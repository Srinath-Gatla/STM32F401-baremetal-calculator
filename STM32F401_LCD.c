#include "STM32F401_LCD.h"
void delay(void)
{
	for(uint32_t i=0;i<50000;i++);
}
void LCD_Enable(LCD_Handle_t * Lp)
{
	GPIO_Write_Pin(Lp->EN.pGPIOx,Lp->EN.GPIO_config.GPIO_PinNumber,GPIO_PIN_SET);
	delay();
	GPIO_Write_Pin(Lp->EN.pGPIOx,Lp->EN.GPIO_config.GPIO_PinNumber,GPIO_PIN_RESET);
	delay();
}
void writeLCD(LCD_Handle_t *Lp, uint8_t data)
{
    // Write each bit to the corresponding data pin
    for(uint8_t i = 0; i < 8; i++)
    {
        uint8_t bit_value = (data >> i) & 0x01;
        GPIO_Write_Pin(Lp->data[i].pGPIOx,Lp->data[i].GPIO_config.GPIO_PinNumber,bit_value);
    }
    LCD_Enable(Lp);
}
void CmdLCD(LCD_Handle_t * Lp,uint8_t cmd)
{
	GPIO_Write_Pin(Lp->RS.pGPIOx,Lp->RS.GPIO_config.GPIO_PinNumber,GPIO_PIN_RESET);
	GPIO_Write_Pin(Lp->RW.pGPIOx,Lp->RW.GPIO_config.GPIO_PinNumber,GPIO_PIN_RESET);

	writeLCD(Lp,cmd);

	delay();   // ADD THIS
}
void CharLCD(LCD_Handle_t * Lp,uint8_t asciival)
{
	GPIO_Write_Pin(Lp->RS.pGPIOx,Lp->RS.GPIO_config.GPIO_PinNumber,GPIO_PIN_SET);
	GPIO_Write_Pin(Lp->RW.pGPIOx,Lp->RW.GPIO_config.GPIO_PinNumber,GPIO_PIN_RESET);
	writeLCD(Lp,asciival);
}
void StrLCD(LCD_Handle_t * Lp,char * s)
{
	while(*s)
	{
		CharLCD(Lp,*s++);
	}
}
void NumLCD(LCD_Handle_t * Lp,uint32_t num)
{
	char buff[10];
	uint32_t i=0;
	if(num == 0)
	{
		CharLCD(Lp,'0');
		return;
	}
	while(num>0)
	{
		buff[i++]=(num % 10) + '0';
		num/=10;
	}
	while(i--)
	{
		CharLCD(Lp,buff[i]);
	}
}
void FloatLCD(LCD_Handle_t * Lp, float num, uint32_t decimal)
{
    uint32_t integer = (uint32_t)num;
    float fraction = num - integer;

    // Display integer part
    NumLCD(Lp, integer);
    CharLCD(Lp, '.');

    // Display decimal part
    for(uint8_t i = 0; i < decimal; i++)
    {
        fraction *= 10;
        uint8_t digit = (uint8_t)fraction;
        CharLCD(Lp, digit + '0');
        fraction -= digit;
    }
}
void InitLCD(LCD_Handle_t * Lp)
{
	for(int i=0;i<8;i++)
	{
		GPIO_PLLCLK_Init(Lp->data[i].pGPIOx,ENABLE);
		GPIO_Init(&Lp->data[i]);
	}

	GPIO_PLLCLK_Init(Lp->EN.pGPIOx,ENABLE);
	GPIO_PLLCLK_Init(Lp->RS.pGPIOx,ENABLE);
	GPIO_PLLCLK_Init(Lp->RW.pGPIOx,ENABLE);

	GPIO_Init(&Lp->EN);
	GPIO_Init(&Lp->RW);
	GPIO_Init(&Lp->RS);

	delay();
	delay();

	CmdLCD(Lp,MODE_8BIT_2LINE);
	delay();

	CmdLCD(Lp,DSP_ON_CUR_OFF);
	delay();

	CmdLCD(Lp,CLEAR_LCD);
	delay();

	CmdLCD(Lp,ENTRY_MODE_LEFT);
	delay();
}
