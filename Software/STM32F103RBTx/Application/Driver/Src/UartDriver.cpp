#include "Driver/Inc/UartDriver.hpp"
#include "Driver/Inc/UartExchangeStatus.hpp"
#include "Driver/Inc/DriverState.hpp"

#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"

#include <cstdint>
#include <array>
#include <algorithm> // For std::find_if

namespace Driver
{
    namespace
    {
        using HalStatusToDriverStatus = struct
        {
            HAL_StatusTypeDef halStatus;
            UartExchangeStatus driverStatus;
        };
        constexpr std::array<HalStatusToDriverStatus, 4> translation = {{{HAL_OK, UartExchangeStatus::Ok},
                                                                         {HAL_ERROR, UartExchangeStatus::ErrorFromHal},
                                                                         {HAL_BUSY, UartExchangeStatus::Busy},
                                                                         {HAL_TIMEOUT, UartExchangeStatus::Timeout}}};
    }

    UartDriver::UartDriver(UART_HandleTypeDef &_uartHandler) : uartHandler(_uartHandler)
    {
    }

    bool UartDriver::onInitialize()
    {
        return true;
    }

    bool UartDriver::onStart()
    {
        const bool status = true;

        return status;
    }

    bool UartDriver::onStop()
    {
        const bool status = true;

        return status;
    }

    bool UartDriver::onReset()
    {
        return true;
    }

    UartExchangeStatus UartDriver::transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            const HAL_StatusTypeDef halStatus = HAL_UART_Transmit(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::receive(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            const HAL_StatusTypeDef halStatus = HAL_UART_Receive(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::getExchangeStatus(HAL_StatusTypeDef halStatus)
    {
        // Use std::find_if for concise and safe lookup
        const auto *it = std::find_if(
            translation.begin(),
            translation.end(),
            [halStatus](const HalStatusToDriverStatus &entry)
            { return entry.halStatus == halStatus; });

        if (it != translation.end())
        {
            return it->driverStatus;
        }

        return UartExchangeStatus::ErrorUnknown;
    }
}
