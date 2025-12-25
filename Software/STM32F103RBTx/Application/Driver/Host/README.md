# Purpose

The firmware can be compiled into a library that can run on a PC. This allows for easy development of the non-hardware-related logic. To enable this, a mock version of the drivers used by the firmware exists. These drivers here:

   * Do not have dependencies on HAL or other low-level libraries.
   * Have the extra capability to trigger events and receive data from the firmware (e.g., calling the system tick, getting data from UART, etc.).

In addition, there is a Python package that wraps this library and provides an easy-to-use interface for tests or simulation.

# Assumptions

   * No high-abstraction libraries are included here (e.g., no GUI, test frameworks, etc.).
   * The mock covers only the .cpp files from the Driver/ folder, meaning no mocks are needed or should be created for the BusinessLogic and Device folders.
