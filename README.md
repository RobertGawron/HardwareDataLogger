# HardwareDataLogger

[![Unit Tests](https://github.com/RobertGawron/HardwareDataLogger/workflows/Unit%20Tests/badge.svg)](https://github.com/RobertGawron/HardwareDataLogger/actions?query=workflow%3A%22Unit+Tests%22) [![Static Code Analysis](https://github.com/RobertGawron/HardwareDataLogger/workflows/Static%20Code%20Analysis/badge.svg)](https://github.com/RobertGawron/HardwareDataLogger/actions?query=workflow%3A%22Static+Code+Analysis%22)

## Summary

Features:
- pulse counting from four different devices
    - logic level from 3V3 to 16V
    - SMA connectors are used
- gathering data via UART
    - DB9 connector is used
- user interface
    - LCD 128*160 RGB
    - four push button to manipulate the GUI, standard layout of buttons - up/down/left/right
    - dimming LCD when it's getting dark
- UART over USB socket to transfer logged data
- microSD card to permanently save logged data
- WiFi to remotely transfer logged data.

![Device Picture](./Documentation/Pictures/Device_03_09_2021.jpg)

## Hardware

PCB was designed in Kicad6 and will be routed in TopoR, so it will look a bit weird, yes... take a look on Google Images how those PCB looks like :)

The device is based on NUCLEO-F091RC evaluation board with added custom-made shield.

[Here is the circuit exported into pdf document.](./Hardware/Logger/Logger.pdf)

## Software

Firmware is being developed in C, CubeMX was used to configure hardware peripherals. Eclipse will be used as IDE.

## Simulation

PC Simulation of Firmware was made using Python+Qt, it uses build .so variant of the firmware (Makefile is used for firmware variant generation).