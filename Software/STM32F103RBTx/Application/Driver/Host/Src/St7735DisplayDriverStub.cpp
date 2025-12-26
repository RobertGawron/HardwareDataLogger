#include "St7735DisplayDriverStub.hpp"
#include "IDisplayDriver.hpp"
#include "DisplayPixelColor.hpp"

#include "st7735.h"

#include <cstdint>
#include <array>

namespace Driver
{
    bool St7735DisplayDriverStub::onInitialize()
    {
        const bool status = true;
        return status;
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
        const bool status = true;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::displayOn()
    {
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::displayOff()
    {
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setOrientation(IDisplayDriver::Orientation _orientation)
    {
        orientation = _orientation;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getOrientation(IDisplayDriver::Orientation &_orientation) const
    {
        _orientation = orientation;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setCursor(std::uint8_t x, std::uint8_t y)
    {
        (void)x;
        (void)y;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawBitmap(std::uint8_t x,
                                                               std::uint8_t y,
                                                               std::uint8_t &bitmap)
    {
        (void)x;
        (void)y;
        (void)bitmap;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRGBRectangle(std::uint8_t x,
                                                                     std::uint8_t y,
                                                                     std::uint8_t &data,
                                                                     std::uint8_t width,
                                                                     std::uint8_t height)
    {
        (void)x;
        (void)y;
        (void)data;
        (void)width;
        (void)height;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawHorizontalLine(std::uint8_t x,
                                                                       std::uint8_t y,
                                                                       std::uint8_t length,
                                                                       DisplayPixelColor::PixelColor color)
    {
        for (std::uint16_t i = x; i < (x + length); ++i)
        {
            if (i < MAX_WIDTH && y < MAX_HEIGHT)
            {
                content.at(i).at(y) = color;
            }
        }
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawVerticalLine(std::uint8_t x,
                                                                     std::uint8_t y,
                                                                     std::uint8_t length,
                                                                     DisplayPixelColor::PixelColor color)
    {
        (void)x;
        (void)y;
        (void)length;
        (void)color;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRectangle(std::uint8_t x,
                                                                  std::uint8_t y,
                                                                  std::uint8_t width,
                                                                  std::uint8_t height,
                                                                  DisplayPixelColor::PixelColor color)
    {
        (void)x;
        (void)y;
        (void)width;
        (void)height;
        (void)color;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setPixel(std::uint8_t x,
                                                             std::uint8_t y,
                                                             DisplayPixelColor::PixelColor color)
    {
        if (x < MAX_WIDTH && y < MAX_HEIGHT)
        {
            content.at(x).at(y) = color;
        }
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getPixel(std::uint8_t x,
                                                             std::uint8_t y,
                                                             DisplayPixelColor::PixelColor &color) const
    {
        (void)x;
        (void)y;
        (void)color;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getXSize(std::uint8_t &size) const
    {
        size = ST7735_HEIGHT;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getYSize(std::uint8_t &size) const
    {
        size = ST7735_WIDTH;
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    DisplayPixelColor::PixelColor St7735DisplayDriverStub::getPixelValue(std::uint8_t x, std::uint8_t y) const
    {
        DisplayPixelColor::PixelColor result = 0U;

        if (x < MAX_WIDTH && y < MAX_HEIGHT)
        {
            result = content.at(x).at(y);
        }

        return result;
    }
}
