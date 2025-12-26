#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/CobsEncoder.hpp"

#include "Driver/Interface/UartExchangeStatus.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <array>
#include <cstddef>
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

        std::size_t msgLength = 0U;

        status = Device::WiFiMeasurementSerializer::generate(
            measurement,
            encodedBuffer,
            msgLength);

        if (status)
        {
            const auto result = CobsEncoder::encode(
                encodedBuffer,
                msgLength,
                dataLinkBuffer);

            if (result.has_value())
            {
                const std::size_t outLength = result.value();

                // Transmit the encoded data
                const Driver::UartExchangeStatus txResult = driver.transmit(
                    dataLinkBuffer.data(),
                    static_cast<std::uint16_t>(outLength),
                    UartTxTimeout);

                status = (txResult == Driver::UartExchangeStatus::Ok);
            }
            else
            {
                status = false;
            }
        }

        return status;
    }
}
