#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/DriverState.hpp"

#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"

#include <cstdint>
#include <span>
#include <cassert>

namespace Driver
{
    UartDriver::UartDriver(UART_HandleTypeDef &_uartHandler) : uartHandler(_uartHandler)
    {
    }

    [[nodiscard]] bool UartDriver::onInitialize()
    {
        return true;
    }

    [[nodiscard]] bool UartDriver::onStart()
    {
        return true;
    }

    [[nodiscard]] bool UartDriver::onStop()
    {
        return true;
    }

    [[nodiscard]] bool UartDriver::onReset()
    {
        return true;
    }

    [[nodiscard]] UartStatus UartDriver::transmit(std::span<const std::uint8_t> data, std::uint32_t timeout)
    {
        UartStatus status = UartStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            if (data.empty())
            {
                status = UartStatus::ErrorFromHal;
            }
            else
            {
                // Ensure size fits in uint16_t for HAL function
                assert(data.size() <= UINT16_MAX && "Data size exceeds UART HAL limit");

                const auto size = static_cast<std::uint16_t>(data.size());
                const HAL_StatusTypeDef halStatus = HAL_UART_Transmit(
                    &uartHandler,
                    const_cast<std::uint8_t *>(data.data()), // HAL API doesn't take const
                    size,
                    timeout);
                status = getUartStatus(halStatus);
            }
        }

        return status;
    }

    [[nodiscard]] UartStatus UartDriver::receive(std::span<std::uint8_t> data, std::uint32_t timeout)
    {
        UartStatus status = UartStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            if (data.empty())
            {
                status = UartStatus::ErrorFromHal;
            }
            else
            {
                // Ensure size fits in uint16_t for HAL function
                assert(data.size() <= UINT16_MAX && "Data size exceeds UART HAL limit");

                const auto size = static_cast<std::uint16_t>(data.size());
                const HAL_StatusTypeDef halStatus = HAL_UART_Receive(
                    &uartHandler,
                    data.data(),
                    size,
                    timeout);
                status = getUartStatus(halStatus);
            }
        }

        return status;
    }
}
