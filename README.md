# Modular Smart Home Controller (PRJ-05-SMARTHOME)

A modular embedded systems project for a smart home controller built around the ATmega32 AVR microcontroller. The system combines sensor-driven automation, secure access control, scene presets, and a cooperative non-blocking scheduler to provide a responsive and scalable home automation solution.

## Overview

The Smart Home Controller is designed as a layered embedded application that separates low-level hardware control from higher-level decision making. It uses a cooperative scheduler to handle periodic tasks without blocking the system, while an arbitration engine resolves conflicts between manual input, sensor conditions, and predefined scenes.

This project demonstrates professional embedded design practices such as:
- Layered architecture with clear separation of responsibilities
- Reusable MCAL and HAL modules
- Event-driven control without hard delays
- Persistent configuration and security logic using EEPROM
- Real-time monitoring and actuation through AVR peripherals

---

## Key Features & Technical Highlights

- Modular layered architecture: MCAL, HAL, APP, and LIB
- Non-blocking task scheduling using Timer0 tick-based execution
- Centralized arbitration logic for conflict resolution
- Secure access control with PIN verification, hashing, salt, lockout logic, and EEPROM persistence
- Sensor integration for light, gas, and temperature monitoring
- PWM-based dimming and fan speed control using Timer1
- Actuator control for relays, lamps, LEDs, fan, and lock mechanisms
- Scene support for Cinema, Sleep, and Away modes
- I2C-based LCD display using a PCF8574 expander to reduce wiring
- Simulation-friendly design for testing in SimulIDE

---

## Project Architecture

```text
+--------------------------------------------------+
|                    APP Layer                      |
|  Scenes | Scheduler | Security | Arbitrator     |
+--------------------------------------------------+
|                    HAL Layer                      |
|  EEPROM | Sensors | Actuators | LCD | Keypad     |
+--------------------------------------------------+
|                    MCAL Layer                     |
|  GPIO | ADC | Timer0 | Timer1 | USART | I2C     |
+--------------------------------------------------+
|                    LIB Layer                      |
|            std_types.h | bit_math.h             |
+--------------------------------------------------+
```

### Design Principles

1. Layered Software Architecture
   - MCAL provides direct hardware abstraction for AVR peripherals.
   - HAL offers device-oriented services for sensors, actuators, display, and memory.
   - APP contains the system logic, scenes, scheduler, and security behavior.
   - LIB provides reusable definitions and helper utilities.

2. Arbitration Logic (The Brain)
   - A centralized arbitration engine handles competing requests.
   - Priority rules determine whether manual control, scene mode, or sensor automation should take precedence.

3. Non-Blocking Architecture
   - Periodic tasks run through a cooperative scheduler.
   - The design avoids blocking delays and keeps the controller responsive.

4. Secure Access Control
   - PIN verification is supported by a hash with salt.
   - Failed attempts trigger lockout logic.
   - Credentials and access states are stored persistently in EEPROM.

5. I2C Reduced Wiring
   - An I2C LCD interface minimizes pin usage and improves wiring simplicity.

---

## Team Members & Module Division

| Team Member | Role | Main Responsibilities |
|------------|------|----------------------|
| Rodina Khaled | Partner A - Actuators, Sensors, Memory & Logic | ADC, Timer1 PWM, USART, EEPROM, Sensors, Actuators, Scenes, Arbitrator, bit_math.h |
| Haneen Ebeid | Partner B - Interfaces, Security & System Timing | Timer0 tick scheduler, GPIO/DIO, I2C/TWI, LCD, Keypad, Security Module, Scheduler, std_types.h |

### Detailed Module Breakdown

| Partner | MCAL | HAL | APP / LIB |
|---------|------|-----|-----------|
| Rodina Khaled | ADC, Timer1, USART | EEPROM, Sensors, Actuators | Scenes, Arbitrator, bit_math.h |
| Haneen Ebeid | Timer0, GPIO/DIO, I2C/TWI | LCD, Keypad | Security Module, Scheduler, std_types.h |

---

## Hardware & Simulation Requirements

### Target Hardware
- Microcontroller: ATmega32 (8-bit AVR)
- Core peripherals: ADC, Timer0, Timer1, GPIO, USART, I2C/TWI
- Actuators: Relays, LEDs, lamps, fan, lock driver
- Sensors: LDR, gas sensor, temperature sensor
- Display: 16x2 LCD via I2C PCF8574 expander
- Input: 4x4 keypad with debouncing

### Simulation Environment
- Tool: SimulIDE
- Common virtual components used in simulation:
  - ATmega32 MCU
  - LCD module with I2C expander
  - Keypad matrix
  - LDR and analog sensor sources
  - Gas/temperature sensor inputs
  - LEDs and relay-based outputs
  - Fan and lock simulation elements

---

## Project Structure

```text
PRJ-05-SMARTHOME/
├── MCL/                # Microcontroller Abstraction Layer
├── HAL/                # Hardware Abstraction Layer
├── LOGIC/              # Application logic and controllers
├── Service/            # Shared definitions and utilities
├── src/                # Main application entry point
├── build/              # Generated object files and firmware output
└── Makefile            # AVR build configuration
```

---

## Build & Execution Instructions

### 1. Prerequisites
- AVR toolchain installed (AVR-GCC, AVR-Objcopy, avrdude)
- PlatformIO toolchain path configured if using the provided Makefile
- SimulIDE installed for circuit and firmware simulation

### 2. Build the Project
From the project root, run:

```bash
make
```

This generates the firmware binary and Intel HEX output under the build folder.

### 3. Flash the Firmware
If hardware programming is available:

```bash
make flash
```

### 4. Run in Simulation
- Open the project in SimulIDE.
- Load the ATmega32 microcontroller and connect the required components.
- Upload the generated firmware hex file to the simulated MCU.
- Run the simulation to observe sensor reactions, scene switching, and actuator behavior.

> Note: If your toolchain is installed in a different location, update the paths in the Makefile before building.

---

## Conclusion

The Modular Smart Home Controller demonstrates a complete embedded systems workflow, from low-level peripheral drivers to high-level application logic. It is suitable for academic projects, demonstrations, and further development into a more advanced smart automation platform.
