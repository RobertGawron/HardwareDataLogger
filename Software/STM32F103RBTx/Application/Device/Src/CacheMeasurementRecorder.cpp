#include "Device/Inc/CacheMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <cstdint>
#include <cstddef>
#include <variant>     // Provides std::visit
#include <type_traits> // Provides std::decay_t

// #include <stdio.h>

namespace Device
{

    bool CacheMeasurementRecorder::onInitialize()
    {
        const bool status = true;
        return status;
    }

    bool CacheMeasurementRecorder::onStart()
    {
        const bool status = true;
        return status;
    }

    bool CacheMeasurementRecorder::onStop()
    {
        const bool status = true;
        return status;
    }

    bool CacheMeasurementRecorder::onReset()
    {
        const bool status = true;
        return status;
    }

    std::uint32_t CacheMeasurementRecorder::getLatestMeasurement(MeasurementDeviceId source) const
    {
        return lastMeasurement[static_cast<std::size_t>(source)];
    }

    bool CacheMeasurementRecorder::write(Device::MeasurementType &measurement)
    {

        //  printf("************* %d src: %d\n", measurement.data, measurement.source);
        // Safely extract the value from the variant and store it as std::uint32_t
        std::visit(
            [this, &measurement](auto &&value)
            {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_arithmetic_v<T>)
                {
                    lastMeasurement[static_cast<std::size_t>(measurement.source)] = static_cast<std::uint32_t>(value);
                }
            },
            measurement.data);

        const bool status = true;
        return status;
    }

    bool CacheMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        const bool status = write(measurement);
        return status;
    }
}
