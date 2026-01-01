#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/CobsEncoder.hpp"

#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <span>

namespace Device
{

    bool WiFiMeasurementRecorder::onInitialize() noexcept
    {
        return driver.initialize();
    }

    bool WiFiMeasurementRecorder::onStart() noexcept
    {
        return driver.start();
    }

    bool WiFiMeasurementRecorder::onStop() noexcept
    {
        return driver.stop();
    }

    bool WiFiMeasurementRecorder::onReset() noexcept
    {
        return driver.reset();
    }

    bool WiFiMeasurementRecorder::notify(const Device::MeasurementType &measurement) noexcept
    {
        bool success = false;

        // Step 1: Serialize the measurement
        auto serializeResult = WiFiMeasurementSerializer::serialize(
            measurement,
            std::span{serializedBuffer});

        if (serializeResult)
        {
            const std::size_t serializedSize = *serializeResult;

            // Step 2: COBS encode the serialized data
            auto encodeResult = CobsEncoder::encode(
                std::span{serializedBuffer.data(), serializedSize},
                std::span{cobsEncodedBuffer});

            if (encodeResult)
            {
                const std::size_t encodedSize = *encodeResult;

                // Step 3: Transmit via UART
                success = (driver.transmit(
                               std::span{cobsEncodedBuffer.data(), encodedSize},
                               UART_TX_TIMEOUT_MS) == Driver::UartStatus::Ok);
            }
        }

        return success;
    }
}