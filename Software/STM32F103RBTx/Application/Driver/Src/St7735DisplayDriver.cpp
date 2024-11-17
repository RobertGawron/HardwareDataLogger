#include "Driver/Inc/St7735DisplayDriver.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"
#include "st7735.h"

namespace Driver
{
    bool St7735DisplayDriver::onInitialize()
    {
        return true;
    }

    bool St7735DisplayDriver::onStart()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onStop()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onReset()
    {
        return true;
    }

    IDisplayDriver::Status St7735DisplayDriver::displayOn()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::displayOff()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setOrientation(IDisplayDriver::Orientation orientation)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getOrientation(IDisplayDriver::Orientation &orientation) const
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setCursor(uint8_t x, uint8_t y)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawBitmap(uint8_t x, uint8_t y, uint8_t &bitmap)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRGBRectangle(uint8_t x,
                                                                 uint8_t y,
                                                                 uint8_t &data,
                                                                 uint8_t width,
                                                                 uint8_t height)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawHorizontalLine(uint8_t x,
                                                                   uint8_t y,
                                                                   uint8_t length,
                                                                   DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawVerticalLine(uint8_t x,
                                                                 uint8_t y,
                                                                 uint8_t length,
                                                                 DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRectangle(uint8_t x,
                                                              uint8_t y,
                                                              uint8_t width,
                                                              uint8_t height,
                                                              DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setPixel(uint8_t x,
                                                         uint8_t y,
                                                         DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getPixel(uint8_t x,
                                                         uint8_t y,
                                                         DisplayPixelColor::PixelColor &color) const
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getXSize(uint8_t &size) const
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getYSize(uint8_t &size) const
    {
        return IDisplayDriver::Status::Ok;
    }
}
