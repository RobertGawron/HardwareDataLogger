
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

void ST7735_DrawPixel(std::uint16_t x, std::uint16_t y, std::uint16_t color)
{
    mockLibST7735->ST7735_DrawPixel(x, y, color);
}

void ST7735_WriteString(std::uint16_t x, std::uint16_t y, const char *str, FontDef font, std::uint16_t color, std::uint16_t bgcolor)
{
    mockLibST7735->ST7735_WriteString(x, y, str, font, color, bgcolor);
}

void ST7735_FillRectangle(std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, std::uint16_t color)
{
    mockLibST7735->ST7735_FillRectangle(x, y, w, h, color);
}

void ST7735_FillScreen(std::uint16_t color)
{
    mockLibST7735->ST7735_FillScreen(color);
}

void ST7735_DrawImage(std::uint16_t x, std::uint16_t y, std::uint16_t w, std::uint16_t h, const std::uint16_t *data)
{
    mockLibST7735->ST7735_DrawImage(x, y, w, h, data);
}

void ST7735_InvertColors(bool invert)
{
    mockLibST7735->ST7735_InvertColors(invert);
}
