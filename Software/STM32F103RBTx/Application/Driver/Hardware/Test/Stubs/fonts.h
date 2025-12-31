#ifndef lib_font_h
#define lib_font_h

// copy & paste from lib
#include <stdint.h>

using FontDef = struct
{
    const std::uint8_t width;
    std::uint8_t height;
    const std::uint16_t *data;
};

extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif
