#ifndef LibWrapper_h
#define LibWrapper_h

#include <stdint.h>
#include "MyApplication.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
    // TODO add Doxygen

    void LibWrapper_Init();
    void LibWrapper_Tick();
    uint8_t LibWrapper_GetDisplayWidth();
    uint8_t LibWrapper_GetDisplayHeight();

    typedef struct PixelValue
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } PixelValue;

    PixelValue LibWrapper_GetPixelValue(uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
