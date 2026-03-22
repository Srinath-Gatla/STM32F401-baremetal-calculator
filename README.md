# STM32F401 LCD Keypad Calculator (Bare-Metal Embedded Project)

## Project Overview
This project is a bare-metal embedded calculator built using the STM32F401 microcontroller. The calculator uses a 16x2 LCD for display and a 4x4 matrix keypad for user input. It supports basic arithmetic operations such as addition, subtraction, multiplication, and division. A push button connected to an external interrupt (EXTI) is used for backspace or starting a new calculation.

The project is developed using register-level programming without using STM32 HAL libraries. All peripheral drivers such as GPIO, LCD, Keypad, and External Interrupt are written from scratch.

---

## Features
- Bare-metal GPIO driver
- 16x2 LCD driver (8-bit mode)
- 4x4 Matrix keypad driver
- External Interrupt (EXTI) for backspace / new calculation
- Basic calculator operations (+, −, ×, ÷)
- Multi-digit number input
- Divide-by-zero error handling
- LCD display output
- Modular driver structure

---

## Hardware Requirements
- STM32F401RE Microcontroller
- 16x2 LCD Display
- 4x4 Matrix Keypad
- Push Button (for EXTI interrupt / backspace)
- Breadboard and connecting wires
- Power supply / ST-Link programmer

---

## Pin Configuration

### LCD Connections
| LCD Pin | STM32 Pin |
|--------|-----------|
| D0–D7  | PB0–PB7   |
| RS     | PC1       |
| RW     | PC2       |
| EN     | PC0       |

### Keypad Connections
| Keypad | STM32 Pin |
|--------|-----------|
| Rows   | PC3–PC6   |
| Cols   | PC7–PC10  |

### Interrupt Button
| Button | STM32 Pin |
|--------|-----------|
| EXTI   | PA0       |

---

## Project Structure
STM32F401-Calculator/
│
├── Drivers/
│ ├── STM32F401_GPIO.c
│ ├── STM32F401_LCD.c
│ ├── STM32F401_KEYPAD.c
│
├── Inc/
│ ├── STM32F401_GPIO.h
│ ├── STM32F401_LCD.h
│ ├── STM32F401_KEYPAD.h
│
├── Src/
│ ├── main.c
│
└── README.md


---

## Calculator Operations
| Key | Operation |
|-----|-----------|
| 0–9 | Number input |
| +   | Addition |
| -   | Subtraction |
| *   | Multiplication |
| /   | Division |
| =   | Result |
| c   | Clear |
| Button (PA0) | Backspace / New Calculation |

---

## How It Works
1. The keypad is scanned continuously to detect key presses.
2. Numbers entered are displayed on the LCD.
3. Operator keys store the operation.
4. When '=' is pressed, the result is calculated and displayed.
5. The external interrupt button (PA0) is used for backspace or starting a new calculation.
6. All drivers are written using register-level programming.

---

## Learning Outcomes
This project demonstrates:
- Embedded C programming
- STM32 register-level programming
- GPIO driver development
- LCD interfacing
- Matrix keypad interfacing
- External interrupt (EXTI)
- Application development on microcontrollers
- Modular embedded driver architecture

---

## Future Improvements
- Floating point calculations
- Expression evaluation
- UART debugging interface
- Timer interrupt keypad scanning
- FreeRTOS integration
- Menu-based LCD interface

---

## Author
**Embedded Systems Project – STM32 Bare-Metal Development**
Also Add This (GitHub Repo Description)

Use this in the repository description:

Bare-metal STM32F401 calculator using 16x2 LCD, 4x4 keypad, GPIO drivers, and EXTI interrupt for backspace functionality.

If you want, I can next help you create:

Driver architecture diagram
Circuit diagram
Resume project description
Interview explanation for this project
