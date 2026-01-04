module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_usart.h"

#include <span>
#include <cstdint>
#include <cassert>
#include <cstdint>

module Driver.UartDriver;

import Driver.DriverComponent;
import Driver.UartStatus;

namespace Driver
{

    UartStatus UartDriver::transmit(std::span<const std::uint8_t> data,
                                    std::uint32_t timeout) noexcept
    {
        UartStatus status = UartStatus::DriverInIncorrectMode;

        if (getState() == DriverComponent::State::RUNNING)
        {
            if (data.empty()) [[unlikely]]
            {
                status = UartStatus::ErrorFromHal;
            }
            else
            {
                // Ensure size fits in uint16_t for HAL function
                assert(data.size() <= UINT16_MAX && "Data size exceeds UART HAL limit");

                const auto size = static_cast<std::uint16_t>(data.size());
                const auto halStatus = HAL_USART_Transmit(
                    &uartHandler,
                    const_cast<std::uint8_t *>(data.data()), // HAL API doesn't accept const
                    size,
                    timeout);

                status = getUartStatus(halStatus);
            }
        }

        return status;
    }

    UartStatus UartDriver::receive(std::span<std::uint8_t> data,
                                   std::uint32_t timeout) noexcept
    {
        UartStatus status = UartStatus::DriverInIncorrectMode;

        if (getState() == DriverComponent::State::RUNNING)
        {
            if (data.empty()) [[unlikely]]
            {
                status = UartStatus::ErrorFromHal;
            }
            else
            {
                // Ensure size fits in uint16_t for HAL function
                assert(data.size() <= UINT16_MAX && "Data size exceeds UART HAL limit");

                const auto size = static_cast<std::uint16_t>(data.size());
                const auto halStatus = HAL_USART_Receive(
                    &uartHandler,
                    data.data(),
                    size,
                    timeout);

                status = getUartStatus(halStatus);
            }
        }

        return status;
    }

} // namespace Driver