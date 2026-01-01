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

    IDisplayDriver::Status St7735DisplayDriverStub::setCursor(std::uint8_t xPosition, std::uint8_t yPosition)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawBitmap(std::uint8_t xPosition,
                                                               std::uint8_t yPosition,
                                                               std::uint8_t &bitmap)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(bitmap);
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRGBRectangle(std::uint8_t xPosition,
                                                                     std::uint8_t yPosition,
                                                                     std::uint8_t &data,
                                                                     std::uint8_t width,
                                                                     std::uint8_t height)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(data);
        static_cast<void>(width);
        static_cast<void>(height);
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRectangle(std::uint8_t xPosition,
                                                                  std::uint8_t yPosition,
                                                                  std::uint8_t width,
                                                                  std::uint8_t height,
                                                                  DisplayPixelColor::PixelColor color)
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(width);
        static_cast<void>(height);
        static_cast<void>(color);
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setPixel(std::uint8_t xPosition,
                                                             std::uint8_t yPosition,
                                                             DisplayPixelColor::PixelColor color)
    {
        if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
        {
            content.at(xPosition).at(yPosition) = color;
        }
        const IDisplayDriver::Status status = IDisplayDriver::Status::Ok;
        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getPixel(std::uint8_t xPosition,
                                                             std::uint8_t yPosition,
                                                             DisplayPixelColor::PixelColor &color) const
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(color);
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

    DisplayPixelColor::PixelColor St7735DisplayDriverStub::getPixelValue(std::uint8_t xPosition, std::uint8_t yPosition) const
    {
        DisplayPixelColor::PixelColor result = 0U;

        if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
        {
            result = content.at(xPosition).at(yPosition);
        }

        return result;
    }
}
