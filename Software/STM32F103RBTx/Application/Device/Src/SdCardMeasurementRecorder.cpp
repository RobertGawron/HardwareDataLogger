#include "Device/Inc/SdCardMeasurementRecorder.hpp"

#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <variant>

namespace Device
{
    bool SdCardMeasurementRecorder::onInitialize() noexcept
    {
        return driver.initialize();
    }

    bool SdCardMeasurementRecorder::onStart() noexcept
    {
        using FileOpenMode = Driver::ISdCardDriver::FileOpenMode;

        static constexpr std::string_view FILENAME{"measurements.txt"};
        static constexpr FileOpenMode MODE{FileOpenMode::APPEND};

        return driver.start() &&
               (driver.openFile(FILENAME, MODE) == Driver::SdCardStatus::OK);
    }

    bool SdCardMeasurementRecorder::onStop() noexcept
    {
        return driver.stop();
    }

    bool SdCardMeasurementRecorder::onReset() noexcept
    {
        return driver.reset();
    }

    bool SdCardMeasurementRecorder::notify(const MeasurementType &measurement) noexcept
    {
        static constexpr std::size_t BUFFER_SIZE{64};
        std::array<char, BUFFER_SIZE> csvBuffer{};
        std::size_t offset{0};
        bool status{false};

        // Convert source ID to string
        const auto sourceResult = std::to_chars(
            csvBuffer.data() + offset,
            csvBuffer.data() + csvBuffer.size(),
            static_cast<std::uint8_t>(measurement.source));

        if (sourceResult.ec == std::errc{}) [[likely]]
        {
            offset = sourceResult.ptr - csvBuffer.data();

            if (offset < csvBuffer.size()) [[likely]]
            {
                csvBuffer[offset++] = ',';

                // Convert measurement data to string
                const bool conversionSuccess = std::visit(
                    [&]<typename T>(const T &value) constexpr noexcept -> bool
                    {
                        const auto dataResult = std::to_chars(
                            csvBuffer.data() + offset,
                            csvBuffer.data() + csvBuffer.size(),
                            value);

                        if (dataResult.ec == std::errc{})
                        {
                            offset = dataResult.ptr - csvBuffer.data();
                            return true;
                        }
                        return false;
                    },
                    measurement.data);

                if (conversionSuccess) [[likely]]
                {
                    if (offset < csvBuffer.size()) [[likely]]
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

} // namespace Device