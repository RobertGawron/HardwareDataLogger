

#ifndef MeasurementType_h
#define MeasurementType_h

#include "Device/Inc/MeasurementSource.hpp"

#include <variant>
#include <cstdint>

namespace Device
{
    // Define a type alias for measurement types
    //  using MeasurementType = std::variant<std::uint8_t, std::uint16_t, std::uint32_t>;

    struct MeasurementTypeStruct
    {
        std::variant<std::uint8_t, std::uint16_t, std::uint32_t> data; // Variant to hold the measurement value
        MeasurementSource source;                                      // Source of the measurement
    };

    using MeasurementType = MeasurementTypeStruct;

}

#endif
