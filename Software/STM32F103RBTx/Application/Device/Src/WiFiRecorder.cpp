#include "Device/Inc/WiFiRecorder.hpp"
#include "Device/Inc/WiFiSerializer.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/CobsEncoder.hpp"

#include "Driver/Interface/UartStatus.hpp"
#include "UartDriver.hpp"

#include <span>

namespace Device
{

    bool WiFiRecorder::onInit() noexcept
    {
        // return driver.init();

        return true;
    }

    bool WiFiRecorder::onStart() noexcept
    {
        //   return driver.start();
        return true;
    }

    bool WiFiRecorder::onStop() noexcept
    {
        // return driver.stop();
        return true;
    }

    bool WiFiRecorder::notify(const Device::MeasurementType &measurement) noexcept
    {
        bool success = false;

        // Step 1: Serialize the measurement
        auto serializeResult = WiFiSerializer::serialize(
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