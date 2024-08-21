
#ifndef DisplayDriverStub_h
#define DisplayDriverStub_h

#include "St7735DisplayDriver.hpp"

#include "stm32f1xx_hal.h"
#include "st7735.h"

namespace Driver
{

    class DisplayDriverStub : public Driver::St7735DisplayDriver
    {
    public:
        typedef struct PixelRGBP
        {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
        } PixelRGBP;

        explicit DisplayDriverStub() = default;

        virtual ~DisplayDriverStub() = default;

        // Additional methods used in simulation
        virtual uint8_t getDisplayWidth() const;
        virtual uint8_t getDisplayHeight() const;
        PixelRGBP getPixel(uint8_t x, uint8_t y) const;

    private:
        PixelRGBP displayContent[ST7735_WIDTH][ST7735_HEIGHT];
    };

}

#endif