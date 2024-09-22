#include "UartDriverStub.hpp"

namespace Driver
{

    bool UartDriverStub::init()
    {
        return true;
    }

    UartExchangeStatus UartDriverStub::transmit(const uint8_t *data, uint16_t size, uint32_t timeout)
    {

        return UartExchangeStatus::ok;
    }

    UartExchangeStatus UartDriverStub::receive(uint8_t *data, uint16_t size, uint32_t timeout)
    {

        return UartExchangeStatus::ok;
    }

}
