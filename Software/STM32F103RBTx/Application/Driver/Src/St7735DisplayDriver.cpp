#include "Driver/Inc/St7735DisplayDriver.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"
#include "st7735.h"
#include <cstdint>
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
        (void)orientation; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getOrientation(IDisplayDriver::Orientation &orientation) const
    {
        (void)orientation; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setCursor(std::uint8_t x, std::uint8_t y)
    {
        (void)x; // Mark parameter as unused
        (void)y; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawBitmap(std::uint8_t x, std::uint8_t y, std::uint8_t &bitmap)
    {
        (void)x;      // Mark parameter as unused
        (void)y;      // Mark parameter as unused
        (void)bitmap; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRGBRectangle(std::uint8_t x,
                                                                 std::uint8_t y,
                                                                 std::uint8_t &data,
                                                                 std::uint8_t width,
                                                                 std::uint8_t height)
    {
        (void)x;      // Mark parameter as unused
        (void)y;      // Mark parameter as unused
        (void)data;   // Mark parameter as unused
        (void)width;  // Mark parameter as unused
        (void)height; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawHorizontalLine(std::uint8_t x,
                                                                   std::uint8_t y,
                                                                   std::uint8_t length,
                                                                   DisplayPixelColor::PixelColor color)
    {
        (void)x;      // Mark parameter as unused
        (void)y;      // Mark parameter as unused
        (void)length; // Mark parameter as unused
        (void)color;  // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::drawVerticalLine(std::uint8_t x,
                                                                 std::uint8_t y,
                                                                 std::uint8_t length,
                                                                 DisplayPixelColor::PixelColor color)
    {
        (void)x;      // Mark parameter as unused
        (void)y;      // Mark parameter as unused
        (void)length; // Mark parameter as unused
        (void)color;  // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::fillRectangle(std::uint8_t x,
                                                              std::uint8_t y,
                                                              std::uint8_t width,
                                                              std::uint8_t height,
                                                              DisplayPixelColor::PixelColor color)
    {
        (void)x;      // Mark parameter as unused
        (void)y;      // Mark parameter as unused
        (void)width;  // Mark parameter as unused
        (void)height; // Mark parameter as unused
        (void)color;  // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::setPixel(std::uint8_t x,
                                                         std::uint8_t y,
                                                         DisplayPixelColor::PixelColor color)
    {
        (void)x;     // Mark parameter as unused
        (void)y;     // Mark parameter as unused
        (void)color; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getPixel(std::uint8_t x,
                                                         std::uint8_t y,
                                                         DisplayPixelColor::PixelColor &color) const
    {
        (void)x;     // Mark parameter as unused
        (void)y;     // Mark parameter as unused
        (void)color; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getXSize(std::uint8_t &size) const
    {
        (void)size; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriver::getYSize(std::uint8_t &size) const
    {
        (void)size; // Mark parameter as unused
        return IDisplayDriver::Status::Ok;
    }
}
