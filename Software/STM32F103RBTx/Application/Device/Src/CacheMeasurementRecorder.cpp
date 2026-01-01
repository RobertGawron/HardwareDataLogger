#include "Device/Inc/CacheMeasurementRecorder.hpp"

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <variant>

namespace Device
{
    bool CacheMeasurementRecorder::onInitialize() noexcept
    {
        return true;
    }

    bool CacheMeasurementRecorder::onStart() noexcept
    {
        return true;
    }

    bool CacheMeasurementRecorder::onStop() noexcept
    {
        return true;
    }

    bool CacheMeasurementRecorder::onReset() noexcept
    {
        return true;
    }

    std::uint32_t CacheMeasurementRecorder::getLatestMeasurement(MeasurementDeviceId source) const noexcept
    {
        return lastMeasurement[static_cast<std::size_t>(source)];
    }

    bool CacheMeasurementRecorder::write(const MeasurementType &measurement) noexcept
    {
        std::visit(
            [this, &measurement]<typename T>(const T &value) constexpr noexcept
            {
                if constexpr (std::is_arithmetic_v<T>)
                {
                    lastMeasurement[static_cast<std::size_t>(measurement.source)] =
                        static_cast<std::uint32_t>(value);
                }
            },
            measurement.data);

        return true;
    }

    bool CacheMeasurementRecorder::notify(const MeasurementType &measurement) noexcept
    {
        return write(measurement);
    }

} // namespace Device