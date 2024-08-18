#include <ST7735DisplayDriver.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx_hal.h" // st7735.h needs
#include "st7735.h"
#ifdef __cplusplus
}
#endif

#include <stdio.h>

namespace Driver
{

	bool ST7735DisplayDriver::init()
	{
		ST7735_Init();
		fillScreen(ST7735_BLACK);

		char buff[12];
		sprintf(&buff[0], "TEST");
		ST7735_WriteString(20, 20, buff, Font_7x10, ST7735_WHITE, ST7735_WHITE);

		return true;
	}

	/*
	showBacklightConf_ForDebugOnly(555, 555);
	void ST7735DisplayDriver::showBacklightConf_ForDebugOnly(uint16_t ambientLight, uint8_t brightnessPercentage)
	{
		char buff[12];
		sprintf(&buff[0], "%d %d", ambientLight, brightnessPercentage);
		ST7735_WriteString(20, 20, buff, Font_7x10, ST7735_BLACK, ST7735_WHITE);
	}*/

	bool ST7735DisplayDriver::drawPixel(uint16_t x, uint16_t y, uint16_t color)
	{
		ST7735_DrawPixel(x, y, color);

		return true;
	}
	bool ST7735DisplayDriver::writeString(uint16_t x, uint16_t y, const char *str, DisplayFont font, uint16_t color, uint16_t bgcolor)
	{
		ST7735_WriteString(x, y, str, font, color, bgcolor);

		return true;
	}
	bool ST7735DisplayDriver::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
	{
		ST7735_FillRectangle(x, y, w, h, color);

		return true;
	}
	bool ST7735DisplayDriver::fillScreen(uint16_t color)
	{
		ST7735_FillScreen(color);

		return true;
	}
	bool ST7735DisplayDriver::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
	{
		ST7735_DrawImage(x, y, w, h, data);

		return true;
	}
	void ST7735DisplayDriver::invertColors(bool invert)
	{
		ST7735_InvertColors(invert);
	}
}
