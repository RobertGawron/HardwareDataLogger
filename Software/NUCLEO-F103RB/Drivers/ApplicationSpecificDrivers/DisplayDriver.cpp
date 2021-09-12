#include "DisplayDriver.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h" // st7735.h needs it and it should be there but it's external lib, I don't want to modify it
#include "st7735.h"
#include "fonts.h"

#ifdef __cplusplus
}
#endif

#include <stdio.h>

namespace Driver
{

DisplayDriver::DisplayDriver()
{
}

DisplayDriver::~DisplayDriver()
{
}

void DisplayDriver::init()
{
	ST7735_Init();

	// dummy way to check communication with LCD
	ST7735_FillScreen(ST7735_BLUE);
	//ST7735_FillScreen(ST7735_WHITE);
	ST7735_DrawPixel(20, 20, ST7735_RED);
	ST7735_DrawPixel(21, 20, ST7735_RED);
	ST7735_DrawPixel(22, 20, ST7735_RED);
	//ST7735_WriteString(30, 30, "it is working", Font_7x10, ST7735_RED,
	//		ST7735_BLACK);

}

void DisplayDriver::tmp_displayBacklightConf(int adc_value, int pwm_value, int brightness)
{
	char buff[12];
	sprintf(&buff[0], "%d %d %d", adc_value, pwm_value, brightness);
	ST7735_WriteString(20, 20, "buff", Font_7x10, ST7735_BLACK, ST7735_WHITE);
}

}
