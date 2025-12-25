#include "UartDriverStub.hpp"
#include "UartExchangeStatus.hpp"
#include "UartIdentifier.hpp"

#include "HmiEventHandlers.hpp"

#include <cstdint>

namespace Driver
{
    UartDriverStub::UartDriverStub(const Driver::UartIdentifier id)
        : hwId(id)
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

    UartExchangeStatus UartDriverStub::transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        // hack but i dont need better for now
        if (hwId == UartIdentifier::DataTransmitterViaWiFi)
        {
            serialTx(data, size, timeout);

            /*  for (std::size_t i = 0u; i < size; i++)
              {
                  printf("UartDriverStub::transmit TX %d \n", (char)data[i]);
              }
              printf("\n");*/
        }

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
