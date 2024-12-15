/**
 * @file IDisplayDriver.hpp
 * @brief Defines the IDisplayDriver interface for interacting with a display device.
 */

#ifndef IDISPLAYDRIVER_H_
#define IDISPLAYDRIVER_H_

#include <cstdint>
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
        using Status = enum class StatusEnum : std::uint8_t {
            Ok = 0u,  /**< Operation completed successfully. */
            Fail = 1u /**< Operation failed. */
        };

        using Orientation = enum class OrientationEnum : std::uint8_t {
            Horizontal = 0u, /**< Display is in horizontal orientation. */
            Vertical = 1u    /**< Display is in vertical orientation. */
        };

        /**
         * @brief Virtual destructor for IDisplayDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IDisplayDriver() override = default;

        /**
         * @brief Turns the display on.
         * @return Status of the operation.
         */
        virtual Status displayOn() = 0;

        /**
         * @brief Turns the display off.
         * @return Status of the operation.
         */
        virtual Status displayOff() = 0;

        /**
         * @brief Sets the display orientation.
         * @param orientation The orientation to set (horizontal or vertical).
         * @return Status of the operation.
         */
        virtual Status setOrientation(Orientation orientation) = 0;

        /**
         * @brief Gets the current display orientation.
         * @param[out] orientation The current orientation of the display.
         * @return Status of the operation.
         */
        virtual Status getOrientation(Orientation &orientation) const = 0;

        /**
         * @brief Sets the cursor position on the display.
         * @param x The X-coordinate of the cursor.
         * @param y The Y-coordinate of the cursor.
         * @return Status of the operation.
         */
        virtual Status setCursor(std::uint8_t x, std::uint8_t y) = 0;

        /**
         * @brief Draws a bitmap at the specified position.
         * @param x The X-coordinate for the bitmap.
         * @param y The Y-coordinate for the bitmap.
         * @param bitmap The bitmap data to draw.
         * @return Status of the operation.
         */
        virtual Status drawBitmap(std::uint8_t x, std::uint8_t y, std::uint8_t &bitmap) = 0;

        /**
         * @brief Fills a rectangle with RGB data.
         * @param x The X-coordinate of the rectangle.
         * @param y The Y-coordinate of the rectangle.
         * @param data The RGB data to fill.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @return Status of the operation.
         */
        virtual Status fillRGBRectangle(std::uint8_t x,
                                        std::uint8_t y,
                                        std::uint8_t &data,
                                        std::uint8_t width,
                                        std::uint8_t height) = 0;

        /**
         * @brief Draws a horizontal line.
         * @param x The starting X-coordinate.
         * @param y The Y-coordinate.
         * @param length The length of the line.
         * @param color The color of the line.
         * @return Status of the operation.
         */
        virtual Status drawHorizontalLine(std::uint8_t x,
                                          std::uint8_t y,
                                          std::uint8_t length,
                                          DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Draws a vertical line.
         * @param x The X-coordinate.
         * @param y The starting Y-coordinate.
         * @param length The length of the line.
         * @param color The color of the line.
         * @return Status of the operation.
         */
        virtual Status drawVerticalLine(std::uint8_t x,
                                        std::uint8_t y,
                                        std::uint8_t length,
                                        DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Fills a rectangle with a specific color.
         * @param x The X-coordinate of the rectangle.
         * @param y The Y-coordinate of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @param color The fill color of the rectangle.
         * @return Status of the operation.
         */
        virtual Status fillRectangle(std::uint8_t x,
                                     std::uint8_t y,
                                     std::uint8_t width,
                                     std::uint8_t height,
                                     DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Sets the color of a pixel.
         * @param x The X-coordinate of the pixel.
         * @param y The Y-coordinate of the pixel.
         * @param color The color of the pixel.
         * @return Status of the operation.
         */
        virtual Status setPixel(std::uint8_t x,
                                std::uint8_t y,
                                DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Gets the color of a pixel.
         * @param x The X-coordinate of the pixel.
         * @param y The Y-coordinate of the pixel.
         * @param[out] color The color of the pixel.
         * @return Status of the operation.
         */
        virtual Status getPixel(std::uint8_t x,
                                std::uint8_t y,
                                DisplayPixelColor::PixelColor &color) const = 0;

        /**
         * @brief Gets the width of the display.
         * @param[out] size The width of the display in pixels.
         * @return Status of the operation.
         */
        virtual Status getXSize(std::uint8_t &size) const = 0;

        /**
         * @brief Gets the height of the display.
         * @param[out] size The height of the display in pixels.
         * @return Status of the operation.
         */
        virtual Status getYSize(std::uint8_t &size) const = 0;
    };

}

#endif // IDISPLAYDRIVER_H_
