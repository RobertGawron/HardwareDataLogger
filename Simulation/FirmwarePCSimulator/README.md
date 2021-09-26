# PC Simulator for firmware

**IT DOESNT WORK**


Simulation project is built from two components:
- firmware (.so file) built with mocks that replace low level functions
- python script that loads this this firmware, and acts as a mockup of hardware

<!--
![Simulator Picture](https://raw.githubusercontent.com/RobertGawron/HardwareDataLogger/main/Documentation/Pictures/PCSimulation_15_10_2020.png)
-->

Note that in order to load .so object into an application, both of them needs to be 32bits, or 64bits. In case of errors during loading .so object, check your version on Python and gcc (both should be either 32bits or 64bits).

## Requirements
- Install Python
- Install PyQt5 by:  ```pip install PyQt5```
- Install gcc an makefile

## Usage

TBD