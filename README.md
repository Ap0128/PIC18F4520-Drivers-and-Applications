# PIC18F4520 Embedded Examples

This repository contains a collection of standalone C examples for the Microchip PIC18F4520 microcontroller. The projects demonstrate common embedded peripherals and interfacing techniques using the XC8 compiler and `xc.h` device headers.

## Overview

The codebase is organized as a set of small, focused firmware examples. Each source file is intended to demonstrate one peripheral, module, or application pattern that can be compiled independently and adapted for a custom hardware setup.

Typical topics covered in this repository include:

- LCD interfacing in 4-bit mode and over I2C
- Timer-based delays and frequency measurement
- ADC-based sensor interfacing
- EEPROM read and write examples
- PWM generation
- Relay, stepper motor, and keypad interfacing
- I2C protocol implementation and peripheral expansion

## Project Structure

```text
Applications/
  Frequency Measurement.c
  Hall Effect With ADC and I2C.c
  Password System.c

Basic Device Drivers/
  4x4 Matrix Interrupt Method.c
  4x4 Matrix Polling Method.c
  EEPROM Interfacing.c
  LCD 4 Bit Mode.c
  LCD_Driver.c
  LDR_ADC Interfacing.c
  PWM Generation Using ADC.c
  Relay.c
  Stepper Motor Interfacing.c
  TIM 0 Polling.c
  TIM 1 Polling.c
  TIM 2 Polling.c

Protocols/
  I2C Protocol.c
```

## Toolchain

- Microcontroller: PIC18F4520
- Compiler: Microchip XC8
- IDE: MPLAB X IDE recommended
- Header support: `xc.h`

Most examples are configured for the internal oscillator at 4 MHz and use standard PIC configuration bits directly in the source file.

## How To Use

1. Open the repository in MPLAB X IDE.
2. Create or import a PIC18F4520 project.
3. Add one example source file at a time to the project.
4. Set the correct device, oscillator configuration, and compiler options for your board.
5. Build and program the target device.

Because these are standalone demonstrations, several files define their own configuration bits, pin mappings, and helper functions. If you combine multiple examples into one project, review the pin assignments and remove duplicate function definitions.

## Hardware Notes

- Verify your board clock source matches the oscillator configuration used in the example.
- Check LCD wiring, keypad matrix connections, sensor inputs, and peripheral pin assignments before programming the device.
- Some examples assume external pull-ups, sensor modules, or driver circuits depending on the application.

## Example Categories

- `Applications`: Higher-level demo programs combining multiple peripherals.
- `Basic Device Drivers`: Reusable peripheral-focused source files.
- `Protocols`: Communication-layer examples such as I2C.

## Contributing

If you add a new example, keep the file self-contained, document the hardware assumptions near the top of the source file, and place it in the most appropriate folder.

## License

No license file is currently present in this repository. Add one if you want to define reuse or redistribution terms.
