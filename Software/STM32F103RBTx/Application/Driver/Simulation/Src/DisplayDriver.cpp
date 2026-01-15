// DisplayDriver.cpp
module;

#include <cstdint>
#include <array>

module Driver.DisplayDriver;

// import Driver.Interface.DisplayPixelColor;

namespace Driver
{
    bool DisplayDriver::displayOn() noexcept
    {
        const bool status = true;
        return status;
    }

    bool DisplayDriver::displayOff() noexcept
    {
        const bool status = true;
        return status;
    }

    bool DisplayDriver::setOrientation(DisplayDriver::Orientation _orientation) noexcept
    {
        orientation = _orientation;
        const bool status = true;
        return status;
    }

    bool DisplayDriver::getOrientation(DisplayDriver::Orientation &_orientation) const noexcept
    {
        _orientation = orientation;
        const bool status = true;
        return status;
    }

    bool DisplayDriver::setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        const bool status = true;
        return status;
    }

    bool DisplayDriver::drawBitmap(std::uint8_t xPosition,
                                   std::uint8_t yPosition,
                                   std::uint8_t &bitmap) noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(bitmap);
        const bool status = true;
        return status;
    }

    bool DisplayDriver::fillRGBRectangle(std::uint8_t xPosition,
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
        const bool status = true;
        return status;
    }
#if 0
    bool DisplayDriver::fillRectangle(std::uint8_t xPosition,
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
        const bool status = true;
        return status;
    }

    bool DisplayDriver::setPixel(std::uint8_t xPosition,
                                 std::uint8_t yPosition,
                                 DisplayPixelColor::PixelColor color) noexcept
    {
        if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
        {
            //       content.at(xPosition).at(yPosition) = color;
        }
        const bool status = true;
        return status;
    }

    bool DisplayDriver::getPixel(std::uint8_t xPosition,
                                 std::uint8_t yPosition,
                                 DisplayPixelColor::PixelColor &color) const noexcept
    {
        static_cast<void>(xPosition);
        static_cast<void>(yPosition);
        static_cast<void>(color);
        const bool status = true;
        return status;
    }
#endif
    bool DisplayDriver::getXSize(std::uint8_t &size) const noexcept
    {
        size = 55; // ST7735_HEIGHT;
        const bool status = true;
        return status;
    }

    bool DisplayDriver::getYSize(std::uint8_t &size) const noexcept
    {
        size = 55; // ST7735_WIDTH;
        const bool status = true;
        return status;
    }
    /*
        DisplayPixelColor::PixelColor DisplayDriver::getPixelValue(std::uint8_t xPosition, std::uint8_t yPosition) const noexcept
        {
            DisplayPixelColor::PixelColor result = 0U;

            if (xPosition < MAX_WIDTH && yPosition < MAX_HEIGHT)
            {
                //  result = content.at(xPosition).at(yPosition);
            }

            return result;
        }
    */
    bool DisplayDriver::onInit() noexcept
    {
        return true;
    }
}