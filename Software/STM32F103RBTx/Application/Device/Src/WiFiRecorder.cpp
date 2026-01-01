module;

#include <span>

module Device.WiFiRecorder;
import Device.MeasurementType;
import Device.WiFiSerializer;
import Device.CobsEncoder;

import Driver.DriverComponent;
import Driver.UartDriver;
import Driver.UartStatus;

namespace Device
{

    auto WiFiRecorder::onInit() noexcept -> bool
    {
        // return driver.init();

        return true;
    }

    auto WiFiRecorder::onStart() noexcept -> bool
    {
        //   return driver.start();
        return true;
    }

    auto WiFiRecorder::onStop() noexcept -> bool
    {
        // return driver.stop();
        return true;
    }

    auto WiFiRecorder::notify(const Device::MeasurementType &measurement) noexcept -> bool
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

        return true;
        // return success;
    }
}