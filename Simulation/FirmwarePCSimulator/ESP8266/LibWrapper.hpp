/// @file LibWrapper.hpp
/// @brief Wrapper for enabling ESP firmware code to function as a PC library for Python simulation.

#ifndef LibWrapper_h
#define LibWrapper_h

#include <cstdint>
#include "HmiEventHandlers.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Initializes the library wrapper.
     *
     * This function sets up the necessary components for the library to
     * operate as a simulation environment.
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
     * @brief Registers a callback for transmitting data via UART.
     *
     * The provided callback function will be called by the firmware when it
     * has data to send via UART.
     *
     * @param callback A function pointer to handle UART transmission.
     */
    void LibWrapper_RegisterOnSerialTx(void (*callback)(char *));

    /**
     * @brief Registers a callback for GPIO state changes.
     *
     * The provided callback function will be called by the firmware when a GPIO
     * pin state changes (e.g., high or low).
     *
     * @param callback A function pointer to handle GPIO state changes.
     */
    void LibWrapper_RegisterOnGpioChange(void (*callback)(GPIO_ID, bool));

    /**
     * @brief Simulates receiving data over UART.
     *
     * This function is used to simulate data being sent from an STM32 device
     * to the ESP8266 firmware.
     *
     * @param pData Pointer to the data buffer containing the received data.
     * @param Size Length of the data in bytes.
     * @param Timeout Timeout duration in milliseconds.
     * @return HAL status indicating the result of the operation.
     */
    HAL_StatusTypeDef LibWrapper_OnSerialRx(
        const std::uint8_t *pData,
        std::uint16_t Size,
        std::uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif // LibWrapper_h
