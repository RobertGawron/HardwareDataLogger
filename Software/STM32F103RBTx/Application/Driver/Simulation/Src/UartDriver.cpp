// UartDriver.cpp
module;

#include "EventHandlers.h"

#include <cstdint>
#include <span>
#include <utility>

module Driver.UartDriver;

namespace Driver
{
    UartDriver::UartDriver(const Driver::UartId deviceId) noexcept
        : uartId(deviceId)
    {
    }

    UartStatus UartDriver::transmit(std::span<const std::uint8_t> data, std::uint32_t timeout) noexcept
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        serialTx(std::to_underlying(uartId), data.data(), size, timeout);

        return UartStatus::Ok;
    }

    UartStatus UartDriver::receive(std::span<std::uint8_t> data, std::uint32_t timeout) noexcept
    {
        (void)data;    // Mark data as unused
        (void)timeout; // Mark timeout as unused

        return UartStatus::Ok;
    }
}