/**
 * @file UartId.h
 * @brief Defines the UartId enum class for identifying different UARTs used in the system.
 */

#ifndef UartId_h
#define UartId_h

#include <cstdint>

namespace Driver
{

    /**
     * @enum UartId
     * @brief Enum class to identify UART channels used for different purposes.
     *
     * This enum is used to specify which UART is used for receiving measurement data,
     * transmitting data via WiFi, or transmitting data via USB.
     */
    enum class UartId : std::uint8_t
    {
        /**
         * @brief UART for receiving measurement data.
         */
        MEASUREMENT_RECEIVER = 0U,

        /**
         * @brief UART for sending/storing processed data via WiFi module.
         */
        TRANSMIT_VIA_WIFI = 1U,

        /**
         * @brief UART for sending/storing processed data via USB.
         */
        TRANSMIT_VIA_USB = 2U
    };

}

#endif // UartId_h
