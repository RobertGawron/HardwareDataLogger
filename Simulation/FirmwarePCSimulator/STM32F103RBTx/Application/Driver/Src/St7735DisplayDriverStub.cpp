#include "St7735DisplayDriverStub.hpp"
#include "IDisplayDriver.hpp"
#include "DisplayPixelColor.hpp"

#include "st7735.h"

namespace Driver
{
    bool St7735DisplayDriverStub::onInitialize()
    {
        return true;
    }

    bool St7735DisplayDriverStub::onStart()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriverStub::onStop()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriverStub::onReset()
    {
        return true;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::displayOn()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::displayOff()
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setOrientation(IDisplayDriver::Orientation _orientation)
    {
        orientation = _orientation;

        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getOrientation(IDisplayDriver::Orientation &_orientation) const
    {
        _orientation = orientation;

        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setCursor(std::uint8_t x, std::uint8_t y)
    {
        (void)x; // Mark x as unused
        (void)y; // Mark y as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawBitmap(std::uint8_t x,
                                                               std::uint8_t y,
                                                               std::uint8_t &bitmap)
    {
        (void)x;      // Mark x as unused
        (void)y;      // Mark y as unused
        (void)bitmap; // Mark bitmap as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRGBRectangle(std::uint8_t x,
                                                                     std::uint8_t y,
                                                                     std::uint8_t &data,
                                                                     std::uint8_t width,
                                                                     std::uint8_t height)
    {
        (void)x;      // Mark x as unused
        (void)y;      // Mark y as unused
        (void)data;   // Mark data as unused
        (void)width;  // Mark width as unused
        (void)height; // Mark height as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawHorizontalLine(std::uint8_t x,
                                                                       std::uint8_t y,
                                                                       std::uint8_t length,
                                                                       DisplayPixelColor::PixelColor color)
    {
        for (std::uint16_t i = x; i < (x + length); i++)
        {
            content[i][y] = color;
        }
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawVerticalLine(std::uint8_t x,
                                                                     std::uint8_t y,
                                                                     std::uint8_t length,
                                                                     DisplayPixelColor::PixelColor color)
    {
        (void)x;      // Mark x as unused
        (void)y;      // Mark y as unused
        (void)length; // Mark length as unused
        (void)color;  // Mark color as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRectangle(std::uint8_t x,
                                                                  std::uint8_t y,
                                                                  std::uint8_t width,
                                                                  std::uint8_t height,
                                                                  DisplayPixelColor::PixelColor color)
    {
        (void)x;      // Mark x as unused
        (void)y;      // Mark y as unused
        (void)width;  // Mark width as unused
        (void)height; // Mark height as unused
        (void)color;  // Mark color as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setPixel(std::uint8_t x,
                                                             std::uint8_t y,
                                                             DisplayPixelColor::PixelColor color)
    {
        content[x][y] = color;
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getPixel(std::uint8_t x,
                                                             std::uint8_t y,
                                                             DisplayPixelColor::PixelColor &color) const
    {
        (void)x;     // Mark x as unused
        (void)y;     // Mark y as unused
        (void)color; // Mark color as unused
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getXSize(std::uint8_t &size) const
    {
        size = ST7735_HEIGHT;

        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getYSize(std::uint8_t &size) const
    {
        size = ST7735_WIDTH;

        return IDisplayDriver::Status::Ok;
    }

    DisplayPixelColor::PixelColor St7735DisplayDriverStub::getPixelValue(std::uint8_t x, std::uint8_t y) const
    {
        if ((x < MAX_WIDTH) && (y < MAX_HEIGHT))
        {
            return content[x][y];
        }
        return 0u; // Default value for out-of-bounds
    }
}
