#include "Device/Inc/Display.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"

// #define U8X8_WITH_USER_PTR 1
#include "u8g2.h"
#include "u8x8.h"

#include <array>
#include <cstdint>
#include <cstdlib>

namespace Device
{

    // Not used. Required by the u8g2 library, but this action is handled by the St7735DisplayDriver class.
    std::uint8_t u8x8_byte_dummy_callback(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t arg_int, void *arg_ptr);

    // Not used. Required by the u8g2 library, but this action is handled by the St7735DisplayDriver class.
    std::uint8_t u8x8_gpio_and_delay_dummy_callback(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t arg_int, void *arg_ptr);

    static const std::uint8_t U8G2_STATUS_OK = 1u;
    static const std::uint8_t U8G2_STATUS_NOT_OK = 0u;

    namespace
    {
        // Define a constant for maximum displays
        constexpr std::size_t MAX_DISPLAYS = 10;

        // Struct for mapping display entries
        struct DisplayMapEntry
        {
            u8x8_t *u8x8;
            Device::Display *display;
        };

        // Use std::array for a fixed-size array
        static std::array<DisplayMapEntry, MAX_DISPLAYS> displayMap{};
        static std::size_t displayCount = 1;

        // This is a trampoline function.
        // It must have the same signature as u8x8_d_st7735.
        std::uint8_t trampolineU8x8DSt7735(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t argInt, void *argPtr)
        {
            for (std::size_t i = 0; i < displayCount; i++)
            {
                if (displayMap[i].u8x8 == u8x8)
                {
                    // Found the matching display instance
                    return displayMap[i].display->u8x8DSt7735Impl(u8x8, msg, argInt, argPtr);
                }
            }
            // No match found
            return U8G2_STATUS_NOT_OK;
        }
    }

    static const u8x8_display_info_t u8x8_st7735_128x128_display_info =
        {
            /* chip_enable_level = */ 0,
            /* chip_disable_level = */ 1,

            /* post_chip_enable_wait_ns = */ 10,
            /* pre_chip_disable_wait_ns = */ 10,
            /* reset_pulse_width_ms = */ 10,
            /* post_reset_wait_ms = */ 20,
            /* sda_setup_time_ns = */ 24,
            /* sck_pulse_width_ns = */ 45,
            /* sck_clock_hz = */ 8000000UL,
            /* spi_mode = */ 0,
            /* i2c_bus_clock_100kHz = */ 4,
            /* data_setup_time_ns = */ 30,
            /* write_pulse_width_ns = */ 65,
            /* tile_width = */ 16,
            /* tile_hight = */ 16,
            /* default_x_offset = */ 0,
            /* flipmode_x_offset = */ 0,
            /* pixel_width = */ 128,
            /* pixel_height = */ 128};

    static const std::uint8_t u8x8_d_st7735_init_seq[] = {
        U8X8_START_TRANSFER(),
        U8X8_END_TRANSFER(), /* disable chip */
        U8X8_END()           /* end of sequence */

    };

    std::uint8_t u8x8_byte_dummy_callback(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t arg_int, void *arg_ptr)
    {
        (void)u8x8;    // Mark parameter as unused
        (void)msg;     // Mark parameter as unused
        (void)arg_int; // Mark parameter as unused
        (void)arg_ptr; // Mark parameter as unused
        return U8G2_STATUS_OK;
    }

    std::uint8_t u8x8_gpio_and_delay_dummy_callback(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t arg_int, void *arg_ptr)
    {
        (void)u8x8;    // Mark parameter as unused
        (void)msg;     // Mark parameter as unused
        (void)arg_int; // Mark parameter as unused
        (void)arg_ptr; // Mark parameter as unused
        return U8G2_STATUS_OK;
    }

    std::uint8_t Display::u8x8DSt7735Impl(u8x8_t *u8x8, std::uint8_t msg, std::uint8_t arg_int, void *arg_ptr)

    {
        switch (msg)
        {
        case U8X8_MSG_DISPLAY_SETUP_MEMORY:
        {
            u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st7735_128x128_display_info);
        }
        break;

        case U8X8_MSG_DISPLAY_INIT:
        {
            // printf("Display initialization\n");
            u8x8_d_helper_display_init(u8x8);
            u8x8_cad_SendSequence(u8x8, u8x8_d_st7735_init_seq);
        }
        break;

        case U8X8_MSG_DISPLAY_DRAW_TILE:
        {
            const u8x8_tile_t *tile = static_cast<u8x8_tile_t *>(arg_ptr);

            for (std::uint8_t t = 0; t < arg_int; t++)
            {
                const std::uint8_t tile_x_start = tile->x_pos * 8; // Starting x position in pixels
                const std::uint8_t tile_y_start = tile->y_pos * 8; // Starting y position in pixels

                // printf("tile_x_start x=%d, y=%d\n", tile_x_start, tile_y_start);

                // Treat each byte as a column of 8 vertical pixels.
                for (std::uint8_t col = 0; col < 120; col++)
                {
                    const std::uint8_t col_data = tile->tile_ptr[col]; // This is a vertical column
                    for (std::uint8_t bit = 0; bit < 8; bit++)
                    {
                        Driver::DisplayPixelColor::PixelColor color = Driver::DisplayPixelColor::getColor(0x00, 0x00, 0x00);
                        const std::uint8_t x = tile_x_start + col;
                        const std::uint8_t y = tile_y_start + bit;

                        if (col_data & (1 << bit))
                        {
                            // Now (col, bit) corresponds to (x, y) pixel offsets within the tile:
                            // x = tile_x_start + col
                            // y = tile_y_start + bit
                            // printf("Pixel ON at x=%d, y=%d\n", tile_x_start + col, tile_y_start + bit);
                            color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
                        }

                        displayDriver.setPixel(x, y, color);
                    }
                }

                tile++;
            }
        }
        break;

        case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
        case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
        case U8X8_MSG_DISPLAY_REFRESH:
        {
        }
        break;

        default:
        {
            // printf("Unhandled message: %d\n", msg);
        }
        break;
        }

        return U8G2_STATUS_OK;
    }

    void Display::u8g2_Setup_st7735(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
    {
        // Calculate the number of tile rows needed for 128x128 resolution.
        // Each tile is 8 pixels high, so for a 128-pixel height:
        std::uint8_t tile_buf_height = 16; // 128 / 8 = 16 tiles.

        // Allocate buffer dynamically for 128x128 resolution.
        // Each tile is 8 pixels wide * 1 byte (8 bits) = 8 bytes per tile.
        // For 16 rows and 16 tiles per row:
        // Total buffer size = 16 rows * 16 tiles/row * 8 bytes/tile = 2048 bytes.
        std::uint8_t *buf = static_cast<std::uint8_t *>(malloc(128 * tile_buf_height));

        if (buf == nullptr)
        {
            // printf("Error: Memory allocation failed for u8g2 buffer\n");
            return;
        }

// Can't fix, MUI related implementation.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"

        // Setup the display with the appropriate parameters.
        u8g2_SetupDisplay(u8g2, trampolineU8x8DSt7735, u8x8_cad_001, byte_cb, gpio_and_delay_cb);

#pragma clang diagnostic pop

        // Configure the buffer and the rendering method (vertical top to bottom).
        u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
    }

    Display::Display(Driver::IDisplayDriver &_displayDriver) : displayDriver(_displayDriver)
    {

        displayMap[0].u8x8 = &u8g2.u8x8;
        displayMap[0].display = this;
    }

    bool Display::initialize()
    {
        const u8g2_cb_t *rotation = U8G2_R0;
        u8g2_Setup_st7735(&u8g2, rotation, u8x8_byte_dummy_callback, u8x8_gpio_and_delay_dummy_callback);

        return true;
    }

};
