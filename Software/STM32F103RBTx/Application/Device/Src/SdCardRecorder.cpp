module;

#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <span>
#include <string_view>
#include <variant>

module Device.SdCardRecorder;

import Driver.FileOpenMode;
import Driver.SdCardStatus;

namespace Device
{
    auto SdCardRecorder::onInit() noexcept -> bool
    {
        return driver.init();
    }

    auto SdCardRecorder::onStart() noexcept -> bool
    {
        using FileOpenMode = Driver::FileOpenMode;
        static constexpr std::string_view FILENAME{"measurements.txt"};
        static constexpr FileOpenMode MODE{FileOpenMode::APPEND};

        const bool status = driver.start() &&
                            (driver.openFile(FILENAME, MODE) == Driver::SdCardStatus::OK);

        return status;
    }

    auto SdCardRecorder::onStop() noexcept -> bool
    {
        return driver.stop();
    }

    auto SdCardRecorder::notify(const MeasurementType &measurement) noexcept -> bool
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