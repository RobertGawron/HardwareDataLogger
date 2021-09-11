#include "DisplayDriver.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h" // st7735.h needs it and it should be there but it's external lib, I don't want to modify it
#include "st7735.h"
#include "fonts.h"


#ifdef __cplusplus
}
#endif

namespace Driver
{

DisplayDriver::DisplayDriver()
{
}

DisplayDriver::~DisplayDriver()
{
}

void DisplayDriver::update()
{
	   ST7735_Init();

	   // dummy way to check communication with LCD
	   ST7735_FillScreen(ST7735_GREEN);
	   ST7735_DrawPixel(20, 20, ST7735_RED);
	   ST7735_DrawPixel(21, 20, ST7735_RED);
	   ST7735_DrawPixel(22, 20, ST7735_RED);
}
}
