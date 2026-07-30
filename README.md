# Modular Smart Home Controller

A modular embedded systems project for a smart home controller built around the ATmega32 AVR microcontroller. The system combines sensor-driven automation, secure access control, scene presets, and a cooperative non-blocking scheduler to provide a scalable and responsive home automation solution.

## Overview

The Smart Home Controller is designed using a layered embedded architecture that clearly separates hardware access, device abstraction, application logic, and shared utility definitions. The firmware is structured to support modular development, easy maintenance, and real-time responsiveness without blocking delays.

## Key Features

- Layered software architecture across MCAL, HAL, APP, and LIB
- Centralized arbitration engine for resolving conflicts between manual input, sensors, and presets
- Non-blocking task execution using a cooperative scheduler driven by Timer0
- Secure PIN-based access control with salted hashing and lockout logic
- Persistent secure state storage using internal EEPROM
- Simulation support through SimulIDE using the provided project file

## Project Architecture

```text
SmartHome_Project/
├── MCAL/
│   ├── gpio.h / gpio.c
│   ├── adc.h / adc.c
│   ├── timer0.h / timer0.c
│   ├── timer1.h / timer1.c
│   ├── i2c.h / i2c.c
│   ├── uart.h / uart.c
│   └── eeprom.h / eeprom.c
├── HAL/
│   ├── keypad.h / keypad.c
│   ├── lcd.h / lcd.c
│   ├── sensors.h / sensors.c
│   └── actuators.h / actuators.c
├── APP/
│   ├── arbitrator.h / arbitrator.c
│   ├── security.h / security.c
│   ├── scenes.h / scenes.c
│   ├── scheduler.h / scheduler.c
│   └── main.c
├── LIB/
│   ├── std_types.h
│   └── bit_math.h
├── DOCS/
│   ├── arbitration.md
│   ├── security_notes.md
│   ├── test_report.md
│   ├── flowchart.png
│   └── state_machine.png
└── smarthome.siml
```

## Architecture Highlights

1. Layered Software Architecture
   - MCAL handles direct register-level access and low-level peripheral control.
   - HAL provides device-level abstractions for sensors, actuators, keypad, and display.
   - APP contains the behavioral logic, including arbitration, scenes, security, and scheduling.
   - LIB provides shared definitions and helper utilities.

2. Centralized Arbitration Engine
   - The arbitration logic in arbitrator.c resolves conflicts between manual overrides, sensor rules, and preset scenes based on priority.

3. Non-Blocking Architecture
   - A cooperative scheduler runs on Timer0 ticks, allowing multiple tasks to be serviced without using blocking delays.

4. Secure Access Control
   - The security module implements PIN verification using salted hashing, failed-attempt lockout, and persistent EEPROM storage.

## Team Members & Module Breakdown

| Team Member | Role | Module Assignment |
|------------|------|-------------------|
| Haneen Ebeid | Partner A - Sensors, Actuators, Memory & System Logic | MCAL: adc, timer1, uart, eeprom; HAL: sensors, actuators; APP/LIB: scenes, arbitrator, bit_math.h |
| Rodina Khaled | Partner B - Interfaces, Security & System Timing | MCAL: gpio, timer0, i2c; HAL: keypad, lcd; APP/LIB: security, scheduler, std_types.h |

## Hardware & Simulation Requirements

### Target Hardware
- Microcontroller: ATmega32 (8-bit AVR)
- Peripherals: GPIO, ADC, Timer0, Timer1, UART, I2C
- Inputs: keypad, sensors
- Outputs: LCD, actuators, LEDs, relays, fan/lock control

### Simulation Environment
- Tool: SimulIDE
- Project file: smarthome.siml
- Use SimulIDE to simulate the ATmega32 microcontroller and connected peripheral modules.
  
## Build & Run Instructions

### Prerequisites
- AVR-GCC toolchain installed
- AVR programmer or simulation environment available
- SimulIDE installed for circuit-level simulation

### Build
Run the following command from the project root:

```bash
make
```

### Flash / Run
If you are using hardware programming:

```bash
make flash
```

For simulation, open the smarthome.siml file in SimulIDE and load the generated firmware binary or hex output.
<img width="1018" height="727" alt="image" src="https://github.com/user-attachments/assets/df27c1a8-8732-4443-86c7-28b4c34e1728" />

## Conclusion

This project demonstrates a complete embedded systems workflow, from low-level peripheral drivers to application-level decision logic, and serves as a solid foundation for smart automation development on AVR platforms.
