#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include "Driver/Inc/UartExchangeStatus.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include "CobsEncoder.hpp"

#include <array>
#include <cstddef> // For std::size_t
#include <cstdint>
#include <cstring>

namespace Device
{

    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver)
        : driver(_driver)
    {
    }

    bool WiFiMeasurementRecorder::onInitialize()
    {
        const bool status = driver.initialize();
        return status;
    }

    bool WiFiMeasurementRecorder::onStart()
    {
        const bool status = driver.start();
        return status;
    }

    bool WiFiMeasurementRecorder::onStop()
    {
        const bool status = driver.stop();
        return status;
    }

    bool WiFiMeasurementRecorder::onReset()
    {
        const bool status = driver.reset();
        return status;
    }

    bool WiFiMeasurementRecorder::flush()
    {
        const bool status = true;
        return status;
    }

    bool WiFiMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        bool status = false;

        std::size_t msgLength = 0u;

        status = serializedMessage.generate(
            measurement,
            encodedBuffer.data(),
            encodedBuffer.size(),
            msgLength);

        if (status)
        {
            const std::size_t outLength = CobsEncoder::encode(
                encodedBuffer.data(),
                msgLength,
                dataLinkBuffer.data(),
                dataLinkBuffer.size());

            if (outLength != 0)
            {
                // Transmit the encoded data
                const Driver::UartExchangeStatus result = driver.transmit(
                    dataLinkBuffer.data(),
                    static_cast<std::uint16_t>(outLength),
                    UartTxTimeout);

                status = (result == Driver::UartExchangeStatus::Ok);
            }
            else
            {
                status = false;
            }
        }

        return status;
    }
}
