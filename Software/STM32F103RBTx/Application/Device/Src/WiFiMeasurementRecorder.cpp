#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include "Driver/Inc/UartExchangeStatus.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <array>
#include <cstddef> // For std::size_t

#include <cstdint>
// #include <stdio.h>
#include <variant>     // Provides std::visit
#include <type_traits> // Provides std::decay_t

namespace Device
{

    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
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

    bool WiFiMeasurementRecorder::write(Device::MeasurementType &measurement)
    {
        bool status = false;

        constexpr std::size_t MaxBufferSize = 10;
        constexpr char CarriageReturn = '\r';
        constexpr char LineFeed = '\n';

        constexpr std::uint8_t ByteMask = 0xFF;
        constexpr std::uint8_t ByteShift24 = 24;
        constexpr std::uint8_t ByteShift16 = 16;
        constexpr std::uint8_t ByteShift8 = 8;

        // Using std::array instead of C-style array
        std::array<std::uint8_t, MaxBufferSize> data = {0}; // Maximum possible size for data with terminators
        std::size_t currentDataPosition = 2;                // Start position after reserved space for length

        // Add the source ID as the first byte in the data buffer
        data[currentDataPosition++] = static_cast<std::uint8_t>(measurement.source);

        auto appendDataWithTerminator = [&](auto value)
        {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, std::uint8_t>)
            {
                data[currentDataPosition++] = value;
            }
            else if constexpr (std::is_same_v<T, std::uint16_t>)
            {
                data[currentDataPosition++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask); // High byte
                data[currentDataPosition++] = static_cast<std::uint8_t>(value & ByteMask);                 // Low byte
            }
            else if constexpr (std::is_same_v<T, std::uint32_t>)
            {
                data[currentDataPosition++] = static_cast<std::uint8_t>((value >> ByteShift24) & ByteMask); // Byte 3
                data[currentDataPosition++] = static_cast<std::uint8_t>((value >> ByteShift16) & ByteMask); // Byte 2
                data[currentDataPosition++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask);  // Byte 1
                data[currentDataPosition++] = static_cast<std::uint8_t>(value & ByteMask);                  // Byte 0
            }
            data[currentDataPosition++] = CarriageReturn;
            data[currentDataPosition++] = LineFeed;
        };

        // Use std::visit to safely handle the variant type in MeasurementType
        std::visit(
            [&](auto &&value)
            {
                appendDataWithTerminator(value);
            },
            measurement.data);

        // Calculate the message length (excluding the length bytes themselves)
        const std::uint16_t len = static_cast<std::uint16_t>(currentDataPosition - 2);

        // Store the length in the first two bytes
        data[0] = static_cast<std::uint8_t>((len >> ByteShift8) & ByteMask); // High byte of length
        data[1] = static_cast<std::uint8_t>(len & ByteMask);                 // Low byte of length

        const Driver::UartExchangeStatus driverStatus = driver.transmit(
            data.data(),
            static_cast<std::uint16_t>(currentDataPosition),
            Driver::IUartDriver::MaxDelay);

        status = (driverStatus == Driver::UartExchangeStatus::Ok);

        return status;
    }

    bool WiFiMeasurementRecorder::flush()
    {
        const bool status = true;
        return status;
    }

    bool WiFiMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        const bool status = write(measurement);
        return status;
    }
}
