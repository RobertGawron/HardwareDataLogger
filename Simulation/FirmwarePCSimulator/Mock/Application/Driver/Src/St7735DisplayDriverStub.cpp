#include "St7735DisplayDriverStub.hpp"

#include <stdio.h>

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

    IDisplayDriver::Status St7735DisplayDriverStub::setCursor(uint8_t x, uint8_t y)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawBitmap(uint8_t x,
                                                               uint8_t y,
                                                               uint8_t &bitmap)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRGBRectangle(uint8_t x,
                                                                     uint8_t y,
                                                                     uint8_t &data,
                                                                     uint8_t width,
                                                                     uint8_t height)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawHorizontalLine(uint8_t x,
                                                                       uint8_t y,
                                                                       uint8_t length,
                                                                       DisplayPixelColor::PixelColor color)
    {
        // printf("St7735DisplayDriverStub::drawHorizontalLine start %d %d %d\n", x, x + length, y);
        for (uint16_t i = x; i < (x + length); i++)
        {
            content[i][y] = color;
        }
        // printf("St7735DisplayDriverStub::drawHorizontalLine stop\n");
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::drawVerticalLine(uint8_t x,
                                                                     uint8_t y,
                                                                     uint8_t length,
                                                                     DisplayPixelColor::PixelColor color)
    {

        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::fillRectangle(uint8_t x,
                                                                  uint8_t y,
                                                                  uint8_t width,
                                                                  uint8_t height,
                                                                  DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::setPixel(uint8_t x,
                                                             uint8_t y,
                                                             DisplayPixelColor::PixelColor color)
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getPixel(uint8_t x,
                                                             uint8_t y,
                                                             DisplayPixelColor::PixelColor &color) const
    {
        return IDisplayDriver::Status::Ok;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getXSize(uint8_t &size) const
    {
        IDisplayDriver::Status status = IDisplayDriver::Status::Ok;

        /*switch (orientation)
        {
        case IDisplayDriver::Orientation::Horizontal:
        {
            size = ST7735_HEIGHT;
        }
        break;

        case IDisplayDriver::Orientation::Vertical:
        {
            size = ST7735_WIDTH;
        }
        break;

        default:
        {
            IDisplayDriver::Status::Fail;
        }
        break;
        }*/
        size = ST7735_HEIGHT;

        return status;
    }

    IDisplayDriver::Status St7735DisplayDriverStub::getYSize(uint8_t &size) const
    {
        IDisplayDriver::Status status = IDisplayDriver::Status::Ok;

        /*switch (orientation)
        {
        case IDisplayDriver::Orientation::Horizontal:
        {
            size = ST7735_WIDTH;
        }
        break;

        case IDisplayDriver::Orientation::Vertical:
        {
            size = ST7735_HEIGHT;
        }
        break;

        default:
        {
            IDisplayDriver::Status::Fail;
        }
        break;
        }*/
        size = ST7735_WIDTH;

        return status;
    }

    DisplayPixelColor::PixelColor St7735DisplayDriverStub::getPixelValue(uint8_t x, uint8_t y) const
    {
        if ((x < MAX_WIDTH) && (y < MAX_HEIGHT))
        {
            return content[x][y];
        }
        return 0u; // Default value for out-of-bounds
    }
}
