#include "UartDriverStub.hpp"
#include "UartStatus.hpp"
#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/UartId.hpp"

#include "EventHandlers.hpp"

#include <cstdint>
#include <string>

namespace Driver
{
    UartDriverStub::UartDriverStub(const Driver::UartId id)
        : uartId(id)
    {
    }

    bool UartDriverStub::onInitialize()
    {
        return true;
    }

    bool UartDriverStub::onStart()
    {
        return true;
    }

    bool UartDriverStub::onStop()
    {
        return true;
    }

    bool UartDriverStub::onReset()
    {
        return true;
    }

    UartStatus UartDriverStub::transmit(std::span<const std::uint8_t> data, std::uint32_t timeout)
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        serialTx(uartId, data.data(), size, timeout);

        return UartStatus::Ok;
    }

    UartStatus UartDriverStub::receive(std::span<std::uint8_t> data, std::uint32_t timeout)
    {
        (void)data;    // Mark data as unused
        (void)timeout; // Mark timeout as unused

        return UartStatus::Ok;
    }
}
