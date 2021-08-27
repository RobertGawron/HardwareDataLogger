# Firmware for NUCLEO-F103RB board

The project has two build configurations:
* for generating binary, this is used for flashing, use Eclipse project
* for generating shared library, this is used for PC simulation, use Makefile

Credits:
* Library to communicate with ST7735S LCD [following files: st7735.h, fonts.h, st7735.c, fonts.c](https://github.com/afiskon/stm32-st7735). I didn't include it as a git subtree, because it would complicate a lot a structure of the project.
