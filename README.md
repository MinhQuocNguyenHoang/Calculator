# STM32 Pocket Calculator (Casio-like)

## Demo

<div align="center"> <video src="https://github.com/user-attachments/assets/50ce03a3-e70b-4b47-9426-682c65b7a507" alt="Calculator beta" height=200/> </div>

---

## Documentation

| File | Description |
|---|---|
| [README.md](README.md) | Main project overview, hardware information, firmware features, and operating principle |
| [layout](./images/layout-1.png) | PCB layout designed using Altium Designer |
| [schematic](./images/schematic-1.png) | Hardware schematic diagram |
| [casio_stm32](./casio_stm32) | STM32 firmware source code |
| [casio_altium](./casio_altium) | PCB and schematic source files |

---

## Introduction

This project implements a handheld calculator system based on the STM32F030K6T6 microcontroller.

The calculator uses a custom-built 5x4 matrix keypad for user input and a 16x2 LCD (HD44780 driver) for displaying expressions and calculation results.

The project demonstrates embedded firmware development concepts including:

- GPIO control
- Matrix keypad scanning
- LCD interfacing in 4-bit mode
- Bare-metal programming (register-level STM32 development)
- Embedded mathematical processing
- PCB design using Altium Designer

---

## Hardware

<table align="center">
  <tr>
    <td align="center">
      <img src="./images/hardware.png" width="420"/>
    </td>
  </tr>
</table>

<p align="center">
  <strong><em>Figure 1:</em></strong> STM32 Calculator Hardware Prototype
</p>

### Hardware Components

| Component | Description |
|---|---|
| MCU | STM32F030K6T6 |
| Input | 5x4 matrix keypad built using push buttons |
| Display | LCD 16x2 using HD44780 driver |
| Flash and debug | STLINK V2.0 |
| PCB | Custom PCB designed using Altium Designer |

---

## Features
   - Basic Arithmetic: Support for addition, subtraction, multiplication, and division.
   - Advanced Expressions: Handles nested parentheses () and operator precedence (PEMDAS).
   - Equation Solver: Finds roots of continuous functions $f(x) = 0$ using numerical methods.
   - Bare-metal Efficiency: Ultra-fast startup and low memory footprint due to register-level programming.
   - Robust Input: 4x5 matrix keypad scanning with software debounce and Backspace/Clear support.

---

## System Operating Principle
This project was developed as a personal embedded systems project to explore bare-metal STM32 programming and low-level hardware control.

### Register-Level Hardware Control

One of the main objectives of this project was to understand how STM32 peripherals operate at the register level. Therefore, all hardware initialization and control are implemented by directly accessing peripheral registers instead of using HAL libraries.

This approach allowed me to:

* Configure GPIO and clock peripherals manually.
* Gain a deeper understanding of STM32 hardware architecture.
* Reduce software overhead and keep the firmware lightweight.
* Develop custom peripheral drivers from scratch.

### Equation Solving Algorithm

The calculator includes a Solver mode capable of finding the roots of equations in the form:

```text
f(x) = 0
```

The algorithm combines interval scanning with the Bisection Method.

#### Root Scanning

The firmware scans the range:

```text
[-10000, 10000]
```

using a step size of **1.0**.

For each interval `[l, r]`, it checks:

```text
f(l) * f(r) <= 0
```

If the sign changes, a root is assumed to exist within that interval according to the Intermediate Value Theorem.

#### Bisection Method

After detecting a valid interval, the firmware repeatedly halves the search range:

1. Compute the midpoint:

   ```text
   mid = (l + r) / 2
   ```

2. Evaluate `f(mid)`.

3. Determine which half contains the root.

4. Update the interval boundaries.

5. Repeat until the desired accuracy is reached.

The solver stops when the error becomes smaller than:

```text
ε = 10^-4
```

### Matrix Keypad Scanning

To support 20 input buttons while minimizing GPIO usage, a 4×5 matrix keypad is implemented.

The firmware scans the keypad by:

1. Driving one row at a time.
2. Reading the column states.
3. Identifying the pressed key from the row-column combination.
4. Applying software debouncing to prevent false key detection.

This method reduces hardware complexity while maintaining reliable input handling.

---

## PCB Layout

<p align="center">
  <img src="./images/layout-1.png" width="30%"/>
  <img src="./images/layout-2.png" width="30%"/>
  <img src="./images/layout-3.png" width="30%"/>
</p>

<p align="center">
  <strong><em>Figure 1:</em></strong> PCB Layout
</p>

---

## Schematic

<p align="center">
  <img src="./images/schematic-1.png" width="900"/>
</p>

<p align="center">
  <strong><em>Figure 2:</em></strong> Hardware Schematic
</p>
---

## Getting Started

### Prerequisites

#### Software Requirements
Before you begin, ensure you have the following tools installed on your system:
- **ARM GCC Toolchain**: The cross-compiler for ARM Cortex-M microcontrollers (`arm-none-eabi-gcc`).
- **GNU Make**: A build automation tool to manage the compilation process.
- **STM32CubeProgrammer**: Official tool to flash the firmware into the MCU.

#### Hardware Requirements
- STM32F030K6TX Development Board.
- 16x2 Character LCD (HD44780 compatible).
- 4x5 Matrix Keypad.
- ST-Link V2 Programmer.
- Please refer to the schematic above for component connections.

### Installation and Build Process

#### 1. Clone the Project
Download the repository to your local machine using git:
```bash
git clone https://github.com/MinhQuocNguyenHoang/Calculator.git
cd Calculator
```

#### 2. Configure Toolchain Path (Important)
Since the project uses a Makefile, you must ensure the compiler path matches your local installation:
1. Navigate to the `casio_stm32/` directory.
2. Open the `Makefile` with a text editor.
3. Locate the variable defining the toolchain path (e.g., `BINPATH` or `GCC_PATH`).
4. Update this path to point to the `bin` folder of your installed ARM GCC Toolchain.
   *Example for Windows:* `GCC_PATH = C:/ST/STM32CubeIDE/tools/bin`
   *Example for Linux:* `GCC_PATH = /usr/bin`

#### 3. Build the Firmware
Open your terminal in the `casio_stm32/` directory and run the following command:
```bash
make
```
Once the process completes:
- Temporary object files will be stored in the `build/` directory.
- The final firmware files (`.bin`, `.hex`, `.elf`) will be generated inside the `build/` folder.

#### 4. Flashing the Firmware
1. Connect your STM32F030K6TX board to your computer via the ST-Link V2.
2. Launch **STM32CubeProgrammer**.
3. Connect to the target device.
4. Select the generated `build/stm32_calculator.bin` file.
5. Click **Start Programming** to upload the firmware to the microcontroller at the address 0x08000000

---
## Software Environment

| Tool | Purpose |
|------|---------|
| ARM GCC Toolchain | Cross-compiler for ARM Cortex-M0 microcontrollers |
| GNU Make | Build automation system for managing compilation |
| Altium Designer | Hardware design (Schematic and PCB Layout) |
| STM32CubeProgrammer | Firmware flashing and device management |
| VS Code | Primary environment for source code development |

---
<h3>Contact Me</h3>

<p>
  <a href="https://github.com/MinhQuocNguyenHoang">
    <img src="https://img.shields.io/badge/GitHub-MinhQuocNguyenHoang-181717?style=for-the-badge&logo=github&logoColor=white"/>
  </a>
  
  <a href="https://www.linkedin.com/in/minhquoc-hcmus/">
    <img src="https://img.shields.io/badge/LinkedIn-Minh%20Quoc-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white"/>
  </a>
  
  <a href="mailto:quoc20053008@gmail.com">
    <img src="https://img.shields.io/badge/Gmail-quoc20053008%40gmail.com-EA4335?style=for-the-badge&logo=gmail&logoColor=white"/>
  </a>
</p>
