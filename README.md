# ARM Cortex-M4 NVIC & SysTick Drivers - TM4C123

## Overview
This project implements low-level drivers for the NVIC (Nested Vectored Interrupt Controller) and SysTick timer on the TM4C123GH6PM microcontroller. The system is configured to run at 16 MHz and demonstrates interrupt handling and timing control using both interrupt and polling techniques.

## Objectives
- Develop SysTick timer driver with interrupt and busy-wait modes
- Implement NVIC driver for IRQ and system exception control
- Configure interrupt priorities and enable/disable mechanisms
- Apply real-time behavior using timer-based events

## Features

### SysTick Driver
- Periodic interrupt generation
- Busy-wait delay implementation
- Start/Stop/De-initialization control
- Callback function support
- Interrupt handler implementation

### NVIC Driver
- Enable/Disable IRQ interrupts
- Set IRQ priorities
- Enable/Disable system and fault exceptions
- Configure exception priorities

## Implementation Details
The project uses direct register-level programming (bare-metal Embedded C) without any abstraction layers. The drivers interact directly with TM4C123 hardware registers to control interrupts and timing behavior.

## Testing
The system demonstrates:
- LED rolling sequence using SysTick interrupt (1-second interval)
- Button-triggered behavior to stop timer and control LED states
- Busy-wait delay testing using SysTick
- Validation of NVIC configurations using register checks

## Files Structure
- nvic.c / nvic.h → NVIC driver
- systick.c / systick.h → SysTick driver
- main.c → Main application
- app.c → Application logic
- tm4c123gh6pm_registers.h → Hardware registers
- common_macros.h → Bit operations
- std_types.h → Standard data types

## Technologies
- Embedded C
- ARM Cortex-M4 Architecture
- TM4C123GH6PM (Tiva C)
- Bare-metal programming

## Author
Hassan Yasser
