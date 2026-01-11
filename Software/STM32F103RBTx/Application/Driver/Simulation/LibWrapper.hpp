/// @file LibWrapper.h
/// @brief Wrapper that allows building code from BusinessLogic and Device folders as a PC library used for simulation in Python.

#ifndef LibWrapper_h
#define LibWrapper_h

#include <functional>
#include <cstdint>
#include <array>

// #include "MyApplication.hpp"
#include "EventHandlers.hpp"
// #include "KeyIdentifier.hpp"

constexpr std::size_t PULSE_COUNTER_COUNT = 4U;

enum KeyIdentifier : std::uint8_t
{
    /*
    Up = static_cast<std::uint8_t>(Driver::KeyIdentifier::Up),
    Down = static_cast<std::uint8_t>(Driver::KeyIdentifier::Down),
    Left = static_cast<std::uint8_t>(Driver::KeyIdentifier::Left),
    Right = static_cast<std::uint8_t>(Driver::KeyIdentifier::Right),
    LastNotUsed = static_cast<std::uint8_t>(Driver::KeyIdentifier::LastNotUsed)
*/
    Up,
    Down,
    Left,
    Right,
    LastNotUsed
};

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
     * @param xPosition The x-coordinate of the pixel.
     * @param yPosition The y-coordinate of the pixel.
     * @return The value of the pixel at the specified location.
     */
    std::uint16_t LibWrapper_GetPixelValue(std::uint8_t xPosition, std::uint8_t yPosition);

    void LibWrapper_KeyPressed(KeyIdentifier keyId);

    void LibWrapper_KeyReleased(KeyIdentifier keyId);

    /**
     * @brief Updates the values of the pulse counters.
     *
     * This function takes an std::array containing the pulse counter values and updates
     * the internal state accordingly.
     *
     * @param pulseCounters An array of pulse counter values.
     */
    void LibWrapper_UpdatePulseCounters(const std::array<std::uint32_t, PULSE_COUNTER_COUNT> &pulseCounters);

    /**
     * @brief Registers a callback for UART transmit operations.
     *
     * @param callback Function pointer to the UART TX callback.
     */
    void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback);

    /**
     * @brief Registers a callback for SD card open operations.
     *
     * @param callback Function pointer to the SD card open callback.
     */
    void LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback callback);

    /**
     * @brief Registers a callback for SD card write operations.
     *
     * @param callback Function pointer to the SD card write callback.
     */
    void LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback callback);

    /**
     * @brief Registers a callback for SD card close operations.
     *
     * @param callback Function pointer to the SD card close callback.
     */
    void LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback callback);

    /**
     * @brief Registers a callback for SD card initialize operations.
     *
     * @param callback Function pointer to the SD card initialize callback.
     */
    void LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback callback);

    /**
     * @brief Registers a callback for SD card start operations.
     *
     * @param callback Function pointer to the SD card start callback.
     */
    void LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback callback);

    /**
     * @brief Registers a callback for SD card stop operations.
     *
     * @param callback Function pointer to the SD card stop callback.
     */
    void LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback callback);

    /**
     * @brief Registers a callback for SD card reset operations.
     *
     * @param callback Function pointer to the SD card reset callback.
     */
    void LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback callback);

#ifdef __cplusplus
}
#endif

#endif
