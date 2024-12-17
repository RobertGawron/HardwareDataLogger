#include "UartDriverStub.hpp"

namespace Driver
{

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

    UartExchangeStatus UartDriverStub::transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        (void)data;    // Mark data as unused
        (void)size;    // Mark size as unused
        (void)timeout; // Mark timeout as unused

        return UartExchangeStatus::Ok;
    }

    UartExchangeStatus UartDriverStub::receive(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        (void)data;    // Mark data as unused
        (void)size;    // Mark size as unused
        (void)timeout; // Mark timeout as unused

        return UartExchangeStatus::Ok;
    }

}
