#include <ST7735DisplayDriver.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h" // st7735.h needs
#include "st7735_old_lib.h"
#include <fonts_old_lib.h>

#ifdef __cplusplus
}
#endif

#include <stdio.h>

namespace Driver
{

void ST7735DisplayDriver::init()
{
	ST7735_Init();
	//ST7735_FillScreen(ST7735_BLUE);
	ST7735_FillScreen(ST7735_GREEN);
}

void ST7735DisplayDriver::showBacklightConf_ForDebugOnly(uint16_t ambientLight, uint8_t brightnessPercentage)
{
	char buff[12];
	sprintf(&buff[0], "%d %d", ambientLight, brightnessPercentage);
	ST7735_WriteString(20, 20, buff, Font_7x10, ST7735_BLACK, ST7735_WHITE);
}

}
