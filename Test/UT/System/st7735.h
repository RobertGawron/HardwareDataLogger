
#ifndef lib_st7735_h
#define lib_st7735_h

#include <gmock/gmock.h>
#include "fonts.h"

class MockLibST7735
{
public:
    MOCK_METHOD(void, ST7735_Unselect, (), ());
    MOCK_METHOD(void, ST7735_Init, (), ());
    MOCK_METHOD(void, ST7735_DrawPixel, (uint16_t x, uint16_t y, uint16_t color), ());
    MOCK_METHOD(void, ST7735_WriteString, (uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor), ());
    MOCK_METHOD(void, ST7735_FillRectangle, (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color), ());
    MOCK_METHOD(void, ST7735_FillScreen, (uint16_t color), ());
    MOCK_METHOD(void, ST7735_DrawImage, (uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data), ());
    MOCK_METHOD(void, ST7735_InvertColors, (bool invert), ());
};

// Declare a global instance of MockLibST7735
extern MockLibST7735 *mockLibST7735;

void ST7735_Unselect();
void ST7735_Init();
void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ST7735_WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ST7735_FillScreen(uint16_t color);
void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
void ST7735_InvertColors(bool invert);

#endif // lib_st7735_h