#ifndef MEASUREMENT_TYPE_HPP
#define MEASUREMENT_TYPE_HPP

#include "Device/Inc/MeasurementDeviceId.hpp"

#include <cstdint>
#include <variant>

namespace Device
{
    struct MeasurementType final
    {
        using DataVariant = std::variant<std::uint16_t, std::uint32_t>;

        MeasurementDeviceId source;
        DataVariant data;
    };

} // namespace Device

#endif // MEASUREMENT_TYPE_HPP