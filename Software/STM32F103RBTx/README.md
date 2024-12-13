# Firmware for STM32F103RBTx

## Architecture

TODO UML diagrams.

## Toolchain
* ST32CubeMX
* Visual Studio Code
* STM32 VS Code Extension
* Docker

Note: Some people argue that using STM32CubeMX is a bad idea and that everything should be coded manually. I disagree, especially for personal projects. STM32CubeMX is a great time-saver and offers a more visual way to configure the project, making it easier to understand and modify. However, the GUI can be somewhat primitive and could definitely be improve

## Building
* Generate the project in STM32CubeMX, which will create the CMake setup.
* Configure the STM32 VS Code Extension.

Note: The generated CMake setup is not integrated with the main CMake configuration.   

## Architecture

Measurement flow diagram
![measurement flow diagram](../../../Documentation/Diagrams/MeasurementFlowSequenceDiagram.svg)

Sequence diagram of the display.
![sequence diagram of the display](../../Documentation/Diagrams/DisplaySequenceDiagram.svg)

## Open points

* Code formatting standard.

## Third party libraries used

* ST7735S LCD [STMicroelectronics/stm32-st7735](https://github.com/STMicroelectronics/stm32-st7735).

