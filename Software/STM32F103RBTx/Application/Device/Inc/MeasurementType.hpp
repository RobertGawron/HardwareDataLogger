

#ifndef MeasurementType_h
#define MeasurementType_h

#include "Device/Inc/MeasurementDeviceId.hpp"

#include <variant>
#include <cstdint>

namespace Device
{
    struct MeasurementTypeStruct
    {
        std::variant<std::uint8_t, std::uint16_t, std::uint32_t> data; // Variant to hold the measurement value
        MeasurementDeviceId source;                                    // Source of the measurement
    };

    using MeasurementType = MeasurementTypeStruct;
}

#endif
