#include "STM32F401_GPIO.h"
#include "STM32F401_LCD.h"
#include "STM32F401_KEYPAD.h"

/* LCD Handle */
LCD_Handle_t LCD;

/* Keypad Configuration */
Keypad_Handle_t MyKeypad =
{
    .Rp = GPIOC,
    .Cp = GPIOC,
    .rows = {3,4,5,6},
    .cols = {7,8,9,10},
};

/* Interrupt Flag for Backspace */
volatile uint8_t backspace_flag = 0;

/* Calculator Variables */
char key_val;
char op = 0;
uint32_t num1 = 0;
uint32_t num2 = 0;
uint32_t result = 0;

/* LCD Cursor Position */
uint8_t lcd_pos = 0;

int main()
{
    GPIO_Handle_t gpio;

    /* Enable GPIO Clocks */
    GPIO_PLLCLK_Init(GPIOA, ENABLE);
    GPIO_PLLCLK_Init(GPIOB, ENABLE);
    GPIO_PLLCLK_Init(GPIOC, ENABLE);

    /* Configure LCD Data Pins PB0–PB7 */
    for (uint32_t i = 0; i < 8; i++)
    {
        LCD.data[i].pGPIOx = GPIOB;
        LCD.data[i].GPIO_config.GPIO_PinNumber = i;
        LCD.data[i].GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
        LCD.data[i].GPIO_config.GPIO_PinSpeed = GPIO_SPEED_HIGH;
        LCD.data[i].GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;
        LCD.data[i].GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;
    }

    /* LCD Control Pins */
    LCD.EN.pGPIOx = GPIOC;
    LCD.EN.GPIO_config.GPIO_PinNumber = 0;
    LCD.EN.GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
    LCD.EN.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    LCD.EN.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;
    LCD.EN.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;

    LCD.RS.pGPIOx = GPIOC;
    LCD.RS.GPIO_config.GPIO_PinNumber = 1;
    LCD.RS.GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
    LCD.RS.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    LCD.RS.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;
    LCD.RS.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;

    LCD.RW.pGPIOx = GPIOC;
    LCD.RW.GPIO_config.GPIO_PinNumber = 2;
    LCD.RW.GPIO_config.GPIO_PinMode = GPIO_MODE_OUT;
    LCD.RW.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    LCD.RW.GPIO_config.GPIO_Pinpupdcontrol = GPIO_NO_PUPD;
    LCD.RW.GPIO_config.GPIO_PinOptype = GPIO_OP_TYPE_PP;

    /* Initialize LCD */
    InitLCD(&LCD);
    delay();

    CmdLCD(&LCD, CLEAR_LCD);
    StrLCD(&LCD, "Calculator");
    CmdLCD(&LCD, 0xC0);
    StrLCD(&LCD, "Ready...");
    delay();
    CmdLCD(&LCD, CLEAR_LCD);

    /* Initialize Keypad */
    InitKeypad(&MyKeypad);

    /* Configure PA0 as Interrupt Button (Backspace) */
    gpio.pGPIOx = GPIOA;
    gpio.GPIO_config.GPIO_PinNumber = 0;
    gpio.GPIO_config.GPIO_PinMode = GPIO_MODE_IT_FT;
    gpio.GPIO_config.GPIO_PinSpeed = GPIO_SPEED_FAST;
    gpio.GPIO_config.GPIO_Pinpupdcontrol = GPIO_PIN_PU;
    GPIO_Init(&gpio);

    /* Enable EXTI Interrupt */
    GPIO_IRQCONFIG(IRQ_EXTI_0, ENABLE);
    GPIO_IRPriority(IRQ_EXTI_0, 2);

    /* Main Loop */
    while(1)
    {
        /* Backspace Interrupt Handling */
        if(backspace_flag)
        {
            if(lcd_pos > 0)
            {
                lcd_pos--;

                CmdLCD(&LCD, 0x80 + lcd_pos);
                CharLCD(&LCD, ' ');
                CmdLCD(&LCD, 0x80 + lcd_pos);
            }

            if(op == 0)
            {
                num1 = num1 / 10;
            }
            else
            {
                if(num2 > 0)
                    num2 = num2 / 10;
                else
                    op = 0;
            }

            backspace_flag = 0;
        }

        /* Read Keypad */
        key_val = Press_Key(&MyKeypad);

        if(key_val)
        {
            CharLCD(&LCD, key_val);
            lcd_pos++;

            /* Number Input */
            if(key_val >= '0' && key_val <= '9')
            {
                if(op == 0)
                    num1 = num1 * 10 + (key_val - '0');
                else
                    num2 = num2 * 10 + (key_val - '0');
            }

            /* Operator Input */
            else if(key_val=='+' || key_val=='-' || key_val=='*' || key_val=='/')
            {
                op = key_val;
            }

            /* Equal Operation */
            else if(key_val == '=')
            {
                switch(op)
                {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;

                    case '/':
                        if(num2 != 0)
                            result = num1 / num2;
                        else
                        {
                            CmdLCD(&LCD, CLEAR_LCD);
                            StrLCD(&LCD,"Math Error");
                            num1 = num2 = 0;
                            op = 0;
                            lcd_pos = 0;
                            continue;
                        }
                        break;
                }

                CmdLCD(&LCD, CLEAR_LCD);
                NumLCD(&LCD, result);

                num1 = result;
                num2 = 0;
                op = 0;
                lcd_pos = 0;
            }

            /* Clear from keypad */
            else if(key_val == 'c')
            {
                CmdLCD(&LCD, CLEAR_LCD);
                num1 = 0;
                num2 = 0;
                op = 0;
                lcd_pos = 0;
            }
        }
    }
}

/* EXTI Interrupt Handler (Backspace Button) */
void EXTI0_IRQHandler(void)
{
    GPIO_IRQHandle(0);
    backspace_flag = 1;
}
