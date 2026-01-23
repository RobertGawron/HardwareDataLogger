module;

#include <cstdint>

export module Driver.PulseCount;

export namespace Driver
{
    /**
     * @brief Type alias for pulse counter values.
     *
     * Defines the storage type for pulse count measurements from hardware counters.
     * Uses 32-bit unsigned integer providing a range of 0 to 4,294,967,295 pulses.
     *
     */
    using PulseCount = std::uint32_t;
}