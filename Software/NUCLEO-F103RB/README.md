# Firmware for NUCLEO-F103RB board

The project has two build configurations:
* for generating binary, this is used for flashing, use Eclipse project
* for generating shared library, this is used for PC simulation, use Makefile

Credits:
* Library to communicate with ST7735S LCD [following files: gfx.h, st7735s.h, fonts.h, st7735s_compat.h, st7735s_compat.c, st7735s.c, gfx.c, fonts.c](https://github.com/bersch/ST7735S). I didn't include it as a git subtree, because it would complicate a lot a structure of the project.
