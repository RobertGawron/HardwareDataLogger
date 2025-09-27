#ifndef MeasurementType_h
#define MeasurementType_h

#include "Device/Inc/MeasurementDeviceId.hpp"

#include <variant>
#include <cstdint>

namespace Device
{
    /**
     * @struct MeasurementTypeStruct
     * @brief Represents a single measurement with its source device and value.
     *
     * This struct combines measurement data with its source identification.
     * The measurement value can be one of several integer types depending on
     * the precision required by the measurement device.
     */
    struct MeasurementTypeStruct
    {
        /**
         * @brief Measurement value stored in a type-safe variant container.
         *
         * Can hold one of the following integer types:
         * - std::uint8_t (for 8-bit measurements)
         * - std::uint16_t (for 16-bit measurements)
         * - std::uint32_t (for 32-bit measurements)
         */
        std::variant<std::uint8_t, std::uint16_t, std::uint32_t> data;
        
        /**
         * @brief Identifier of the measurement source device.
         *
         * Specifies which physical device generated this measurement.
         */
        MeasurementDeviceId source;
    };

    /**
     * @typedef MeasurementType
     * @brief Alias for MeasurementTypeStruct for cleaner usage in interfaces.
     */
    using MeasurementType = MeasurementTypeStruct;
}

#endif
