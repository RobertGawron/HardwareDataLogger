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

#include <cstring>
#include <array>
// #include <iostream>

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

    bool WiFiMeasurementRecorder::write(Device::MeasurementType &measurement)
    {
        bool status = false;
        // todo typedefs
        std::array<std::uint8_t, MaxBufferSize> scpiBuffer = {0}; // Maximum possible size for data with terminators
        std::array<std::uint8_t, MaxBufferSize> dataLinkBuffer = {0};

        std::size_t dataIndex = dataLink.msgStart(); // Start position after reserved space for length and crc

        scpiMessageGenerator.generateMessage(measurement, scpiBuffer, dataIndex);
        auto MessageLength = dataIndex - dataLink.msgStart();
        std::size_t outLength = 0;
        dataLink.generateMessage(scpiBuffer, MessageLength, dataLinkBuffer, outLength);
        /*   constexpr std::size_t MaxBufferSize = 100; // Increased size for additional metadata
           constexpr std::uint8_t ByteMask = 0xFF;
           constexpr std::uint8_t ByteShift24 = 24;
           constexpr std::uint8_t ByteShift16 = 16;
           constexpr std::uint8_t ByteShift8 = 8;

           // Using std::array instead of C-style array
           std::array<std::uint8_t, MaxBufferSize> data = {0}; // Maximum possible size for data with terminators
           std::size_t dataIndex = 0;                          // Start position after reserved space for length

           // Determine the device ID prefix and message metadata
           auto addDeviceIdAndMetadata = [&](const char *deviceId)
           {
               const char *metadata = "MEAS:";
               for (const char *c = metadata; *c != '\0'; ++c)
               {
                   data[dataIndex++] = *c;
               }

               for (const char *c = deviceId; *c != '\0'; ++c)
               {
                   data[dataIndex++] = *c;
               }

               const char *dataLabel = ":DATA \"2024-12-28T11:16:36Z,"; // Hardcoded timestamp
               for (const char *c = dataLabel; *c != '\0'; ++c)
               {
                   data[dataIndex++] = *c;
               }
           };

           switch (measurement.source)
           {
           case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1:
               addDeviceIdAndMetadata("DEVICE01");
               break;
           case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2:
               addDeviceIdAndMetadata("DEVICE02");
               break;
           case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3:
               addDeviceIdAndMetadata("DEVICE03");
               break;
           case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_4:
               addDeviceIdAndMetadata("DEVICE04");
               break;
           case Device::MeasurementDeviceId::DEVICE_UART_1:
               addDeviceIdAndMetadata("DEVICE05");
               break;
           default:
               return false; // Unsupported device ID
           }

           auto appendDataWithTerminator = [&](auto value)
           {
               using T = std::decay_t<decltype(value)>;
               if constexpr (std::is_same_v<T, std::uint8_t>)
               {
                   data[dataIndex++] = value;
               }
               else if constexpr (std::is_same_v<T, std::uint16_t>)
               {
                   data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask); // High byte
                   data[dataIndex++] = static_cast<std::uint8_t>(value & ByteMask);                 // Low byte
               }
               else if constexpr (std::is_same_v<T, std::uint32_t>)
               {
                   data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift24) & ByteMask); // Byte 3
                   data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift16) & ByteMask); // Byte 2
                   data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask);  // Byte 1
                   data[dataIndex++] = static_cast<std::uint8_t>(value & ByteMask);                  // Byte 0
               }
           };

           data[dataIndex++] = static_cast<std::uint8_t>((len >> ByteShift8) & ByteMask); // High byte of length
           data[dataIndex++] = static_cast<std::uint8_t>(len & ByteMask);                 // Low byte of length

           // Calculate CRC for data[1] to dataIndex
           const std::size_t crcStartPosition = 1;                     // Start from data[1]
           const std::size_t crcLength = dataIndex - crcStartPosition; // Length of the data for CRC
           std::uint32_t crcValue = crc.calculateCrc32(&data[crcStartPosition], crcLength);

           // Append CRC to the data
           data[dataIndex++] = static_cast<std::uint8_t>((crcValue >> ByteShift24) & ByteMask); // Byte 3
           data[dataIndex++] = static_cast<std::uint8_t>((crcValue >> ByteShift16) & ByteMask); // Byte 2
           data[dataIndex++] = static_cast<std::uint8_t>((crcValue >> ByteShift8) & ByteMask);  // Byte 1
           data[dataIndex++] = static_cast<std::uint8_t>(crcValue & ByteMask);                  // Byte 0

           // Encode the data using the encoder
           std::array<std::uint8_t, MaxBufferSize> encodedData = {0}; // Buffer for encoded data
           const std::size_t encodedLength = encoder.encode(data.data(), dataIndex, encodedData.data(), MaxBufferSize);

           if (encodedLength == 0)
           {
               return false; // Encoding failed
           }

           // Transmit the encoded data
           auto timeout = 1000;
           Driver::UartExchangeStatus result = driver.transmit(encodedData.data(), static_cast<std::uint16_t>(encodedLength), timeout);
           status = (result == Driver::UartExchangeStatus::Ok);
   */
        return status;
    }

#if 0
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
          std::size_t dataIndex = 2;                // Start position after reserved space for length

          // Add the source ID as the first byte in the data buffer
          data[dataIndex++] = static_cast<std::uint8_t>(measurement.source);

          auto appendDataWithTerminator = [&](auto value)
          {
              using T = std::decay_t<decltype(value)>;
              if constexpr (std::is_same_v<T, std::uint8_t>)
              {
                  data[dataIndex++] = value;
              }
              else if constexpr (std::is_same_v<T, std::uint16_t>)
              {
                  data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask); // High byte
                  data[dataIndex++] = static_cast<std::uint8_t>(value & ByteMask);                 // Low byte
              }
              else if constexpr (std::is_same_v<T, std::uint32_t>)
              {
                  data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift24) & ByteMask); // Byte 3
                  data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift16) & ByteMask); // Byte 2
                  data[dataIndex++] = static_cast<std::uint8_t>((value >> ByteShift8) & ByteMask);  // Byte 1
                  data[dataIndex++] = static_cast<std::uint8_t>(value & ByteMask);                  // Byte 0
              }
              data[dataIndex++] = CarriageReturn;
              data[dataIndex++] = LineFeed;
          };

          // Use std::visit to safely handle the variant type in MeasurementType
          std::visit(
              [&](auto &&value)
              {
                  appendDataWithTerminator(value);
              },
              measurement.data);

          // Calculate the message length (excluding the length bytes themselves)
          const std::uint16_t len = static_cast<std::uint16_t>(dataIndex - 2);

          // Store the length in the first two bytes
          data[0] = static_cast<std::uint8_t>((len >> ByteShift8) & ByteMask); // High byte of length
          data[1] = static_cast<std::uint8_t>(len & ByteMask);                 // Low byte of length

          const Driver::UartExchangeStatus driverStatus = driver.transmit(
              data.data(),
              static_cast<std::uint16_t>(dataIndex),
              Driver::IUartDriver::MaxDelay);

          status = (driverStatus == Driver::UartExchangeStatus::Ok);

          return status;

        // std::cout << "********************************** CALLED ***************************************" << std::endl;
#if 1
        const char *data = "MEAS:VOLT:DATA \"2024-12-28T11:16:36Z,555\"";
        constexpr size_t maxSize = 256;
        auto size = std::strlen(data);

        // Create an std::array with maxSize
        std::array<uint8_t, maxSize> data2 = {};

        // Set the first element to the length of the data
        data2[0] = static_cast<uint8_t>(size);

        // Copy the data into the array starting at the second position
        std::memcpy(data2.data() + 1, data, size);

        // driver.transmit((data), size, 1000);
        // driver.transmit(const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(data2)), size, 1000);

        //    driver.transmit(data2.data(), size + 1, 1000);

        //  driver.transmit(const_cast<uint8_t *>(data), size, 1000);
        //   MEAS : VOLT : DATA "2024-12-28T11:16:36Z,8.23"

        //               (void)measurement; // Explicitly suppresses "unused parameter" warning
#endif
        return true;
    }
#endif

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
