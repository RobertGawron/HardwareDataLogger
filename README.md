# HardwareDataLogger

[![Static Code Analysis](https://github.com/RobertGawron/HardwareDataLogger/workflows/Static%20Code%20Analysis/badge.svg)](https://github.com/RobertGawron/HardwareDataLogger/actions?query=workflow%3A%22Static+Code+Analysis%22)

<!-- Tests were removed
 [![Unit Tests](https://github.com/RobertGawron/HardwareDataLogger/workflows/Unit%20Tests/badge.svg)](https://github.com/RobertGawron/HardwareDataLogger/actions?query=workflow%3A%22Unit+Tests%22)
-->


## Summary

**_TL;DR simple device that can collect and display data from other devices. It's more flexible than similar boards._**

The idea is to create a shield for NUCLEO-F103RB with following capabilities:
- Pulse counting from four different devices (e.g. Geiger Counters)
    - Logic level from 3V3 to 16V
    - SMA connectors are used
- Gathering data from a measurement device via UART
    - DB9 connector is used
- user interface
    - LCD 128*160 RGB
    - four push button to manipulate the GUI, standard button layout - up/down/left/right
    - dimming LCD when it's getting dark
- UART over USB to transfer logged data to external PC
- microSD card to permanently save logged data
- WiFi to remotely transfer logged data.

## Hardware

Prototype is visible below, PS. the final one will have custom designed PCB.

![Picture of Hardware Data Logger](./Documentation/Pictures/Device_03_09_2021.jpg)

* [Circuit exported to .pdf is available here](./Documentation/Circuit/Logger.pdf)
* Toolchain: KiCad6
* [More info.](./Hardware/Logger/README.md)

## Software

#### NUCLEO-F103RB
* Toolchain: STM32CubeIDE, C, C++
* [More info (Including fancy UML diagrams!!!).](./Software/NUCLEO-F103RB/README.md)


## Simulation

In order to be able to test GUI and other high level parts without need to constantly flash the device, a PC simulation will be created.

* Toolchain: Python, Qt.
* [More info.](./Simulation/FirmwarePCSimulator/README.md)

## Licence

The project is developed under the MIT License, but firmware uses uGFX library, so it's impossible to use it in commercial products without paying licence to the author of the library.