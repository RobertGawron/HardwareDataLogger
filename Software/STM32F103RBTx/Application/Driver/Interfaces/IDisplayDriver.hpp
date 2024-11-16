/**
 * @file IDisplayDriver.hpp
 * @brief Defines the IDisplayDriver interface for interacting with a display device.
 */

#ifndef IDISPLAYDRIVER_H_
#define IDISPLAYDRIVER_H_

#include <stdint.h>
#include "Driver/Inc/DriverState.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"

namespace Driver
{

    /**
     * @class IDisplayDriver
     * @brief Interface for display drivers to interact with different display hardware.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any display driver. It includes basic display operations like drawing pixels,
     * writing strings, filling rectangles, filling the screen, drawing images, and
     * inverting colors.
     */
    class IDisplayDriver : public DriverState
    {
    public:
        typedef enum class Status
        {
            Ok = 0u,
            Fail = 1u
        } Status;

        typedef enum class Orientation
        {
            Horizontal = 0u,
            Vertical = 1u
        } Orientation;

        /**
         * @brief Virtual destructor for IDisplayDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IDisplayDriver() = default;

        virtual Status displayOn() = 0;
        virtual Status displayOff() = 0;
        virtual Status setOrientation(Orientation orientation) = 0;
        virtual Status getOrientation(Orientation &orientation) const = 0;
        virtual Status setCursor(uint8_t x, uint8_t y) = 0;
        virtual Status drawBitmap(uint8_t x, uint8_t y, uint8_t &bitmap) = 0;
        virtual Status fillRGBRectangle(uint8_t x,
                                        uint8_t y,
                                        uint8_t &data,
                                        uint8_t width,
                                        uint8_t height) = 0;
        virtual Status drawHorizontalLine(uint8_t x,
                                          uint8_t y,
                                          uint8_t length,
                                          DisplayPixelColor::PixelColor color) = 0;
        virtual Status drawVerticalLine(uint8_t x,
                                        uint8_t y,
                                        uint8_t length,
                                        DisplayPixelColor::PixelColor color) = 0;
        virtual Status fillRectangle(uint8_t x,
                                     uint8_t y,
                                     uint8_t width,
                                     uint8_t height,
                                     DisplayPixelColor::PixelColor color) = 0;
        virtual Status setPixel(uint8_t x,
                                uint8_t y,
                                DisplayPixelColor::PixelColor color) = 0;
        virtual Status getPixel(uint8_t x,
                                uint8_t y,
                                DisplayPixelColor::PixelColor &color) const = 0;
        virtual Status getXSize(uint8_t &size) const = 0;
        virtual Status getYSize(uint8_t &size) const = 0;
    };

}

#endif // IDISPLAYDRIVER_H_