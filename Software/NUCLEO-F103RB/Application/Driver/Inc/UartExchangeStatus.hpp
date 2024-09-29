/**
 * @file UartExchangeStatus.hpp
 * @brief Defines the UartExchangeStatus enumeration for UART communication status.
 */

#ifndef UartExchangeStatus_h
#define UartExchangeStatus_h

#include <stdint.h>

namespace Driver
{
    /**
     * @enum UartExchangeStatus
     * @brief Represents the status of a UART exchange operation.
     *
     * This enumeration provides a set of statuses that indicate the result of UART communication
     * operations. It is used to avoid direct dependency on STM32 HAL enums, making it easier to
     * switch to other platforms if needed.
     */
    enum class UartExchangeStatus : uint8_t
    {
        /**
         * @brief Indicates a successful UART exchange operation.
         */
        Ok,

        /**
         * @brief Indicates an error occurred during the UART exchange operation.
         */
        ErrorFromHal,

        /**
         * @brief Indicates that the UART is currently busy and cannot process the request.
         */
        Busy,

        /**
         * @brief Indicates that the UART exchange operation timed out.
         */
        Timeout,

        /**
         * @brief Indicates that the driver is in an incorrect mode for the requested operation.
         *
         * This status is returned when an operation is attempted while the driver is in a mode
         * that does not support the requested action. For example, attempting to send data when
         * the driver is configured for receiving only.
         */
        DriverInIncorrectMode,

        /**
         * @brief Indicates an unknown error occurred during the UART exchange operation.
         *
         * This status is returned when the cause of the failure cannot be determined. It acts as a
         * fallback for unexpected issues that do not match other predefined statuses.
         */
        ErrorUnknown
    };

}

#endif // UartExchangeStatus_h