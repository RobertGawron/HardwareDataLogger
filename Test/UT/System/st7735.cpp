
#include "st7735.h"

// Declare a global instance of MockLibST7735
extern MockLibST7735 *mockLibST7735;

// Override the ST7735 functions to use the global mock instance

void ST7735_Unselect()
{
    mockLibST7735->ST7735_Unselect();
}

void ST7735_Init()
{
    mockLibST7735->ST7735_Init();
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    mockLibST7735->ST7735_DrawPixel(x, y, color);
}

void ST7735_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
{
    mockLibST7735->ST7735_WriteString(x, y, str, font, color, bgcolor);
}

void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    mockLibST7735->ST7735_FillRectangle(x, y, w, h, color);
}

void ST7735_FillScreen(uint16_t color)
{
    mockLibST7735->ST7735_FillScreen(color);
}

void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
{
    mockLibST7735->ST7735_DrawImage(x, y, w, h, data);
}

void ST7735_InvertColors(bool invert)
{
    mockLibST7735->ST7735_InvertColors(invert);
}
