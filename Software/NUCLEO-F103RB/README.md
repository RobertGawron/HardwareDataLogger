# Firmware for NUCLEO-F103RB board

## Architecture

TODO UML diagrams.

## Prequises
* ST32CubeMX
* Visual STudio Code
* STM32 VS Code Extension
* Docker (in the future)

Note: Some people argue that using STM32CubeMX is a bad idea and that everything should be coded manually. I disagree, especially for personal projects. STM32CubeMX is a great time-saver and offers a more visual way to configure the project, making it easier to understand and modify. However, the GUI can be somewhat primitive and could definitely be improve

## Building
* Generate the project in STM32CubeMX, which will create the CMake setup.
* Configure the STM32 VS Code Extension.

Note: The generated CMake setup is not integrated with the main CMake configuration.   

## Open points
* Code formatting standard.

## Third party libraries used

I chose not to include third-party libraries as a git subtree because it would significantly complicate the project structure.

Libraries used:
* ST7735S LCD [following files: st7735.h, fonts.h, st7735.c, fonts.c](https://github.com/afiskon/stm32-st7735).
* SD card [following files: fatfs.h, user_diskio_spi.h, user_diskio.h, fatfs.c, user_diskio_spi.c, user_diskio.c](https://github.com/kiwih/cubemx-mmc-sd-card/).
