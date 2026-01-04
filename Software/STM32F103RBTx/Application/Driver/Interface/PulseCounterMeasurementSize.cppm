module;

#include <cstdint>

export module Driver.PulseCounterMeasurementSize;

export namespace Driver
{
    /**
     * @brief Type representing the counter value size.
     *
     * Defines the integer type used for storing pulse count values.
     */
    using PulseCounterMeasurementSize = std::uint32_t;

}