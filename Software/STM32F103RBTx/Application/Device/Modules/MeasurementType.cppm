module;

#include <cstdint>
#include <variant>

export module Device.MeasurementType;

import Device.MeasurementDeviceId;

export namespace Device
{
    struct MeasurementType final
    {
        using DataVariant = std::variant<std::uint16_t, std::uint32_t>;

        MeasurementDeviceId source;
        DataVariant data;
    };

} // namespace Device