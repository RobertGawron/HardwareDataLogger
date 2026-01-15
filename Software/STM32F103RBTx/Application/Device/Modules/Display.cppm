module;

#include <cstdint>

#include "U8g2lib.h"
#include "u8g2.h"

export module Device.Display;

import Device.DeviceComponent;
import Device.DisplayPixelColor;

import Driver.DisplayDriver;

export namespace Device
{
    /**
     * @class Display
     * @brief Adapter class that implements the `IDisplay` interface using a provided display driver.
     *
     * The `Display` class bridges the `IDisplay` interface and a specific `DisplayDriver` implementation.
     * It manages the initialization and configuration of the display and provides utility functions
     * for working with the underlying display driver.
     */
    class Display final : public U8G2, public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a `Display` instance with a reference to a display driver.
         *
         * @param displayDriver Reference to a `Driver::DisplayDriver` implementation.
         */
        explicit Display(Driver::DisplayDriver &displayDriver);

        /* explicit constexpr Display(Driver::DisplayDriver &displayDriver) noexcept
             : displayDriver{displayDriver}
         {
         }*/

        ~Display() = default;

        // Non-copyable and non-movable
        Display() = delete;
        Display(const Display &) = delete;
        Display(Display &&) = delete;
        Display &operator=(const Display &) = delete;
        Display &operator=(Display &&) = delete;

        /**
         * @brief Initializes the display system.
         *
         * This method initializes the display by configuring the necessary hardware and software components.
         *
         * @return `true` if the initialization is successful; `false` otherwise.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Callback function for handling low-level display commands.
         *
         * This function implements a low-level interface for the ST7735 display driver.
         * It processes messages sent to the `u8x8` display driver.
         *
         * @param u8x8 Pointer to the `u8x8_t` structure representing the display context.
         * @param msg The message type (e.g., initialization, draw, or hardware commands).
         * @param argInt Integer argument associated with the message.
         * @param argPtr Pointer argument associated with the message.
         * @return A status code indicating success or failure.
         */
        [[nodiscard]] std::uint8_t u8x8DSt7735Impl(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t argInt, void *argPtr);

    private:
        /**
         * @brief Helper function to configure the u8g2 library for the ST7735 display.
         *
         * This method sets up the `u8g2` library with the appropriate callbacks and parameters
         * for the ST7735 display hardware.
         *
         * @param u8g2Handler Pointer to the `u8g2_t` structure representing the library context.
         * @param rotation Pointer to a `u8g2_cb_t` structure specifying the display rotation.
         * @param byte_cb Byte callback function for communication with the display.
         * @param gpio_and_delay_cb GPIO and delay callback function for controlling hardware signals.
         */
        static void u8g2_Setup_st7735(
            u8g2_t *u8g2Handler,
            const u8g2_cb_t *rotation,
            u8x8_msg_cb byte_cb,
            u8x8_msg_cb gpio_and_delay_cb);

        Driver::DisplayDriver &displayDriver;
    };

} // namespace Device