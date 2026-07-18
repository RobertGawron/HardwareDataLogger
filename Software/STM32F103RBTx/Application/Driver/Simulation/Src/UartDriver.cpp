module;

#include <cstdint>
#include <span>
#include <utility>

module Driver.UartDriver;

import EventHandlers;

namespace Driver
{
    UartDriver::UartDriver(const Driver::UartId deviceId) noexcept
        : uartId(deviceId)
    {
    }

    auto UartDriver::transmit(std::span<const std::uint8_t> data, std::uint32_t timeout) noexcept -> UartStatus
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        serialTx(std::to_underlying(uartId), data.data(), size, timeout);

        return UartStatus::Ok;
    }

    auto UartDriver::receive(std::span<std::uint8_t> data, std::uint32_t timeout) noexcept -> UartStatus
    {
        (void)data;    // Mark data as unused
        (void)timeout; // Mark timeout as unused

        return UartStatus::Ok;
    }
}