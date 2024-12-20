/// @file LibWrapper.h
/// @brief Wrapper that allows building code from BusinessLogic and Device folders as a PC library used for simulation in Python.

#ifndef LibWrapper_h
#define LibWrapper_h

#include <cstdint>
#include <array>
#include "MyApplication.hpp"

constexpr std::size_t PULSE_COUNTER_COUNT = 4;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initializes the library for use in simulations.
     *
     * This function performs all necessary initializations for the library,
     * setting up internal components required for the application to run.
     */
    void LibWrapper_Init();

    /**
     * @brief Main tick function to advance application state.
     *
     * This function is called periodically to update the internal state of the
     * application logic. It simulates the passage of time and processes events.
     */
    void LibWrapper_Tick();

    /**
     * @brief Gets the width of the display.
     *
     * @return The width of the display in pixels.
     */
    std::uint8_t LibWrapper_GetDisplayWidth();

    /**
     * @brief Gets the height of the display.
     *
     * @return The height of the display in pixels.
     */
    std::uint8_t LibWrapper_GetDisplayHeight();

    /**
     * @brief Gets the value of a specific pixel on the display.
     *
     * This function returns the value of a pixel located at the given coordinates.
     * The value represents the color or intensity of the pixel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The value of the pixel at the specified location.
     */
    std::uint16_t LibWrapper_GetPixelValue(std::uint8_t x, std::uint8_t y);

    typedef enum KeyboardKeyIdentifier
    {
        Up = 0u,         /**< Represents the 'Up' key, assigned with value 0. */
        Down = 1u,       /**< Represents the 'Down' key, assigned with value 1. */
        Left = 2u,       /**< Represents the 'Left' key, assigned with value 2. */
        Right = 3u,      /**< Represents the 'Right' key, assigned with value 3. */
        LastNotUsed = 4u /**< Represents the last enum value, used to determine the size of the enum. */
    } KeyboardKeyIdentifier;

    void LibWrapper_KeyPressed(KeyboardKeyIdentifier keyId);

    void LibWrapper_KeyReleased(KeyboardKeyIdentifier keyId);

    /**
     * @brief Updates the values of the pulse counters.
     *
     * This function takes an std::array containing the pulse counter values and updates
     * the internal state accordingly.
     *
     * @param pulseCounters An array of pulse counter values.
     */
    void LibWrapper_UpdatePulseCounters(const std::array<std::uint16_t, PULSE_COUNTER_COUNT> &pulseCounters);

#ifdef __cplusplus
}
#endif

#endif
