# EE 120 Lab 2: Stepper Motor Control

This project uses an STM32 NUCLEO-L476RG to control a 28BYJ-48 stepper motor through a ULN2003 Darlington driver board.

## Project Description

The program demonstrates how GPIO outputs can control the four motor phases. It includes both full-stepping and half-stepping sequences, along with clockwise and counterclockwise rotation routines.

## Hardware

- STM32 NUCLEO-L476RG
- 28BYJ-48 stepper motor
- ULN2003 Darlington driver board
- External 5 V motor supply

## GPIO Connections

The motor-control signals are connected to:

- PC5
- PC6
- PC8
- PC9

The STM32 GPIO pins control the ULN2003 driver inputs. The ULN2003 provides the current needed to drive the motor coils.

## Stepping Methods

- Full stepping uses a four-step sequence.
- Half stepping uses an eight-step sequence.
- The delay value controls the motor rotation speed.
- Different functions provide clockwise and counterclockwise rotation.

## Software

- C programming language
- Keil uVision
- STM32 Cortex-M4
- Direct GPIO register programming

## File

- `main.c` — GPIO initialization and stepper-motor control routines
