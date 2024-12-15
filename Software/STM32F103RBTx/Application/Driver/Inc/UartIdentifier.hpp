/**
 * @file UartIdentifier.h
 * @brief Defines the UartIdentifier enum class for identifying different UARTs used in the system.
 */

#ifndef UartIdentifier_h
#define UartIdentifier_h

#include <cstdint>

namespace Driver
{

    /**
     * @enum UartIdentifier
     * @brief Enum class to identify UART channels used for different purposes.
     *
     * This enum is used to specify which UART is used for receiving measurement data,
     * transmitting data via WiFi, or transmitting data via USB.
     */
    enum class UartIdentifier : std::uint8_t
    {
        /**
         * @brief UART for receiving measurement data.
         */
        MeasurementReceiver = 0u,

        /**
         * @brief UART for sending/storing processed data via WiFi module.
         */
        DataTransmitterViaWiFiModule = 1u,

        /**
         * @brief UART for sending/storing processed data via USB.
         */
        DataTransmitterViaUSB = 2u
    };

}

#endif // UartIdentifier_h
