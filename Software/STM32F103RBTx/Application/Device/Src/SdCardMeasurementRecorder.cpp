#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"
#include "Driver/Interface/SdCardStatus.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <charconv>
#include <variant>

namespace Device
{
    SdCardMeasurementRecorder::SdCardMeasurementRecorder(Driver::ISdCardDriver &_driver)
        : driver(_driver)
    {
    }

    [[nodiscard]] bool SdCardMeasurementRecorder::onInitialize()
    {
        return driver.initialize();
    }

    [[nodiscard]] bool SdCardMeasurementRecorder::onStart()
    {
        using FileOpenMode = Driver::ISdCardDriver::FileOpenMode;

        constexpr std::string_view filename = "measurements.txt";
        constexpr FileOpenMode mode = FileOpenMode::APPEND;

        return driver.start() &&
               (driver.openFile(filename, mode) == Driver::SdCardStatus::OK);
    }

    [[nodiscard]] bool SdCardMeasurementRecorder::onStop()
    {
        return driver.stop();
    }

    [[nodiscard]] bool SdCardMeasurementRecorder::onReset()
    {
        return driver.reset();
    }

    bool SdCardMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        bool status = false;

        // Convert measurement to CSV format: "sourceId,measurement\n"
        std::array<char, 64> csvBuffer{};
        std::size_t offset = 0;

        // Convert source ID to string
        auto sourceResult = std::to_chars(
            csvBuffer.data() + offset,
            csvBuffer.data() + csvBuffer.size(),
            static_cast<std::uint8_t>(measurement.source));

        if (sourceResult.ec == std::errc{})
        {
            offset = sourceResult.ptr - csvBuffer.data();

            // Add comma separator
            if (offset < csvBuffer.size())
            {
                csvBuffer[offset++] = ',';

                // Visit the variant and convert the measurement data to string
                bool conversionSuccess = std::visit([&](auto value) -> bool
                                                    {
                            auto dataResult = std::to_chars(
                                csvBuffer.data() + offset,
                                csvBuffer.data() + csvBuffer.size(),
                                value);

                            if (dataResult.ec == std::errc{})
                            {
                                offset = dataResult.ptr - csvBuffer.data();
                                return true;
                            }
                            return false; }, measurement.data);

                if (conversionSuccess)
                {
                    // Add newline
                    if (offset < csvBuffer.size())
                    {
                        csvBuffer[offset++] = '\n';

                        // Write to SD card
                        const std::span<const std::uint8_t> writeData{
                            reinterpret_cast<const std::uint8_t *>(csvBuffer.data()),
                            offset};

                        status = (driver.write(writeData) == Driver::SdCardStatus::OK);
                    }
                }
            }
        }

        return status;
    }
}