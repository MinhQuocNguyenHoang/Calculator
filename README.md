# Calculator

## Overview
This project implements a simple handheld calculator based on an STM32 microcontroller.  
It uses a **5x4 matrix keypad created from button** for input and a **16x2 LCD** (HD44780) to display results.

## Hardware Used
- MCU: STM32F030K6T6<br>
- Keypad: Created from 20 button (5x4 matrix)<br>
- Display: LCD 16x02 via GPIO 4 bit (driver HD44780)<br>
- Power supply + voltage regulator<br>
- Custom PCB designed with Altium Designer<br>

## Software Environment
- Language: Embedded C
- Framework: STM32CubeIDE, STM32CubeMX<br>
- RTOS: FreeRTOS real-time kernel<br>
- Tools: VS Code, Altium Designer (PCB design)<br>

## Project Structure
```
    Calculator/
    ├─ casio_altium # PCB design # schematic
    ├─ casio_stm32 #MCU code
    ├─ Readme.md # This files
    ├─ video_Demo # Demo video
    ├─ layout.pdf # PCB layout
    ├─ schematic.pdf # Schematic
```

## Features
- Input numbers and operations via Keypad.<br>  
- Display input and results on LCD 16x2.<br>  
- Supported operations:  
  - Addition, subtraction, multiplication, division<br>  
  - Solve linear equations (`ax + b = 0`)<br>  
  - Solve quadratic equations (`ax² + bx + c = 0`)<br>  
- Keypad debounce to prevent mis-entry.<br> 

## ## Wiring / Schematic
- [PCB Layout](./layout.pdf) 
- [Schematic](./schematic.pdf) 

## Getting Started
1. Install STM32CubeIDE<br>
2. Prepare ST-LINK<br>
3. Connect ST-LINK to stm32 via 4 pin (VCC, GND, SCLK, SWDIO)<br>
4. Run code<br>

## Demo
- [Demo](./video_Demo/demo.mp4)

## Operating principle
- Project has 2 mode: operation and solve the quation<br>
- Mode operation: Can solve a lot of operation include interger, float and double<br>
- Mode solve the equation: Can solve the quadratic equations and superlative equations<br>

## Author
Nguyễn Hoàng Minh Quốc<br>
Github: @MinhQuocNguyenHoang
