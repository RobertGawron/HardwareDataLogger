/**
 * @file IDisplayDriver.hpp
 * @brief Defines the IDisplayDriver interface for interacting with a display device.
 */

#ifndef IDISPLAYDRIVER_H_
#define IDISPLAYDRIVER_H_

#include <cstdint>
#include "Driver/Interface/DriverState.hpp"
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
        /**
         * @enum StatusEnum
         * @brief Operation status codes for display operations.
         */
        enum class StatusEnum : std::uint8_t
        {
            Ok = 0u,  ///< Operation completed successfully.
            Fail = 1u ///< Operation failed.
        };

        using Status = StatusEnum; ///< Alias for StatusEnum.

        /**
         * @enum OrientationEnum
         * @brief Display orientation options.
         */
        enum class OrientationEnum : std::uint8_t
        {
            Horizontal = 0u, ///< Display is in horizontal orientation.
            Vertical = 1u    ///< Display is in vertical orientation.
        };

        using Orientation = OrientationEnum; ///< Alias for OrientationEnum.

        /**
         * @brief Virtual destructor for IDisplayDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~IDisplayDriver() override = default;

        /**
         * @brief Turns the display on.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status displayOn() = 0;

        /**
         * @brief Turns the display off.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status displayOff() = 0;

        /**
         * @brief Sets the display orientation.
         * @param orientation The orientation to set (horizontal or vertical).
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status setOrientation(Orientation orientation) = 0;

        /**
         * @brief Gets the current display orientation.
         * @param[out] orientation The current orientation of the display.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status getOrientation(Orientation &orientation) const = 0;

        /**
         * @brief Sets the cursor position on the display.
         * @param x The X-coordinate of the cursor (0-based).
         * @param y The Y-coordinate of the cursor (0-based).
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status setCursor(std::uint8_t x, std::uint8_t y) = 0;

        /**
         * @brief Draws a bitmap at the specified position.
         * @param x The X-coordinate for the top-left corner of the bitmap.
         * @param y The Y-coordinate for the top-left corner of the bitmap.
         * @param bitmap Reference to the bitmap data to draw.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status drawBitmap(std::uint8_t x, std::uint8_t y, std::uint8_t &bitmap) = 0;

        /**
         * @brief Fills a rectangle with RGB data.
         * @param x The X-coordinate of the top-left corner of the rectangle.
         * @param y The Y-coordinate of the top-left corner of the rectangle.
         * @param data Reference to the RGB data to fill.
         * @param width The width of the rectangle in pixels.
         * @param height The height of the rectangle in pixels.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status fillRGBRectangle(std::uint8_t x,
                                        std::uint8_t y,
                                        std::uint8_t &data,
                                        std::uint8_t width,
                                        std::uint8_t height) = 0;

        /**
         * @brief Draws a horizontal line.
         * @param x The starting X-coordinate of the line.
         * @param y The Y-coordinate of the line.
         * @param length The length of the line in pixels.
         * @param color The color of the line.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status drawHorizontalLine(std::uint8_t x,
                                          std::uint8_t y,
                                          std::uint8_t length,
                                          DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Draws a vertical line.
         * @param x The X-coordinate of the line.
         * @param y The starting Y-coordinate of the line.
         * @param length The length of the line in pixels.
         * @param color The color of the line.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status drawVerticalLine(std::uint8_t x,
                                        std::uint8_t y,
                                        std::uint8_t length,
                                        DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Fills a rectangle with a specific color.
         * @param x The X-coordinate of the top-left corner of the rectangle.
         * @param y The Y-coordinate of the top-left corner of the rectangle.
         * @param width The width of the rectangle in pixels.
         * @param height The height of the rectangle in pixels.
         * @param color The fill color of the rectangle.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status fillRectangle(std::uint8_t x,
                                     std::uint8_t y,
                                     std::uint8_t width,
                                     std::uint8_t height,
                                     DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Sets the color of a single pixel.
         * @param x The X-coordinate of the pixel.
         * @param y The Y-coordinate of the pixel.
         * @param color The color to set for the pixel.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status setPixel(std::uint8_t x,
                                std::uint8_t y,
                                DisplayPixelColor::PixelColor color) = 0;

        /**
         * @brief Gets the color of a single pixel.
         * @param x The X-coordinate of the pixel.
         * @param y The Y-coordinate of the pixel.
         * @param[out] color The current color of the pixel.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status getPixel(std::uint8_t x,
                                std::uint8_t y,
                                DisplayPixelColor::PixelColor &color) const = 0;

        /**
         * @brief Gets the display width in pixels.
         * @param[out] size The width of the display in pixels.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status getXSize(std::uint8_t &size) const = 0;

        /**
         * @brief Gets the display height in pixels.
         * @param[out] size The height of the display in pixels.
         * @return Status::Ok if successful, Status::Fail otherwise.
         */
        virtual Status getYSize(std::uint8_t &size) const = 0;
    };

}

#endif // IDISPLAYDRIVER_H_
