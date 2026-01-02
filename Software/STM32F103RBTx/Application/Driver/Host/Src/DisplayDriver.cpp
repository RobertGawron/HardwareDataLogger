#include "DisplayDriver.hpp"
#include "DisplayDriver.hpp"
#include "DisplayPixelColor.hpp"

#include "st7735.h"

#include <cstdint>
#include <array>

namespace Driver
{

    DisplayDriver::Status DisplayDriver::displayOn() noexcept
    {
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::displayOff() noexcept
    {
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::setOrientation(DisplayDriver::Orientation _orientation) noexcept
    {
        orientation = _orientation;
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::getOrientation(DisplayDriver::Orientation &_orientation) const noexcept
    {
        _orientation = orientation;
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::drawBitmap(std::uint8_t xPosition,
                                                    std::uint8_t yPosition,
                                                    std::uint8_t &bitmap) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(bitmap);
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::fillRGBRectangle(std::uint8_t xPosition,
                                                          std::uint8_t yPosition,
                                                          std::uint8_t &data,
                                                          std::uint8_t width,
                                                          std::uint8_t height) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(data);
        static_cast<void>(width);
        static_cast<void>(height);
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::fillRectangle(std::uint8_t xPosition,
                                                       std::uint8_t yPosition,
                                                       std::uint8_t width,
                                                       std::uint8_t height,
                                                       DisplayPixelColor::PixelColor color) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(width);
        static_cast<void>(height);
        static_cast<void>(color);
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::setPixel(std::uint8_t xPosition,
                                                  std::uint8_t yPosition,
                                                  DisplayPixelColor::PixelColor color) noexcept
    {
        if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
        {
            content.at(xPosition).at(yPosition) = color;
        }
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::getPixel(std::uint8_t xPosition,
                                                  std::uint8_t yPosition,
                                                  DisplayPixelColor::PixelColor &color) const noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(color);
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::getXSize(std::uint8_t &size) const noexcept
    {
        size = ST7735_HEIGHT;
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayDriver::Status DisplayDriver::getYSize(std::uint8_t &size) const noexcept
    {
        size = ST7735_WIDTH;
        const DisplayDriver::Status status = DisplayDriver::Status::Ok;
        return status;
    }

    DisplayPixelColor::PixelColor DisplayDriver::getPixelValue(std::uint8_t xPosition, std::uint8_t yPosition) const noexcept
    {
        DisplayPixelColor::PixelColor result = 0U;

        if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
        {
            result = content.at(xPosition).at(yPosition);
        }

        return result;
    }
}
