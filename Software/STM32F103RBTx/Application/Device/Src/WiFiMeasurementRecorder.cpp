#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/CobsEncoder.hpp"

#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>

namespace Device
{
    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver)
        : driver(_driver)
    {
    }

    bool WiFiMeasurementRecorder::onInitialize()
    {
        return driver.initialize();
    }

    bool WiFiMeasurementRecorder::onStart()
    {
        return driver.start();
    }

    bool WiFiMeasurementRecorder::onStop()
    {
        return driver.stop();
    }

    bool WiFiMeasurementRecorder::onReset()
    {
        return driver.reset();
    }

    bool WiFiMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        bool status = false;
        std::size_t msgLength = 0U;

        if (Device::WiFiMeasurementSerializer::generate(measurement, encodedBuffer, msgLength))
        {
            const auto result = CobsEncoder::encode(encodedBuffer, msgLength, dataLinkBuffer);

            if (result.has_value())
            {
                const std::span<const std::uint8_t> txData{dataLinkBuffer.data(), result.value()};
                status = (driver.transmit(txData, UartTxTimeout) == Driver::UartStatus::Ok);
            }
        }

        return status;
    }
}
