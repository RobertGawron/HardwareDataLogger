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

    UartExchangeStatus UartDriverStub::transmit(uint8_t *data, uint16_t size, uint32_t timeout)
    {

        return UartExchangeStatus::Ok;
    }

    UartExchangeStatus UartDriverStub::receive(uint8_t *data, uint16_t size, uint32_t timeout)
    {

        return UartExchangeStatus::Ok;
    }

}
