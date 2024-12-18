

#ifndef MeasurementType_h
#define MeasurementType_h

#include <variant>
#include <cstdint>
#include <cstdint>

namespace Device
{
    // Define a type alias for measurement types
    using MeasurementType = std::variant<std::uint8_t, std::uint16_t, std::uint32_t>;

}

#endif
