module;

#include <cstdint>
#include <limits>

export module Driver.CycleBudget;

import Driver.CycleCpu;
import Driver.CoreClockConfig;

export namespace Driver
{
    /**
     * @brief Compile-time conversion helpers from time units to CPU cycles.
     *
     * @details
     * Converts human-readable time budgets (microseconds/milliseconds) into cycle counts
     * used with the CPU cycle counter. All conversions are performed at compile time.
     *
     * The returned value is expressed as @ref CycleCpu.
     */
    class CycleBudget final
    {
    public:
        CycleBudget() = delete;
        ~CycleBudget() = delete;

        CycleBudget(const CycleBudget &) = delete;
        CycleBudget &operator=(const CycleBudget &) = delete;
        CycleBudget(CycleBudget &&) = delete;
        CycleBudget &operator=(CycleBudget &&) = delete;

        /**
         * @brief Converts microseconds to CPU cycles using the configured coreHz.
         */
        static constexpr auto fromUs(std::uint32_t us) -> CycleCpu
        {
            const CycleCpu result = fromUs(coreHz, us);
            return result;
        }

        /**
         * @brief Converts milliseconds to CPU cycles using the configured coreHz.
         */
        static constexpr auto fromMs(std::uint32_t ms) -> CycleCpu
        {
            const CycleCpu result = fromMs(coreHz, ms);
            return result;
        }

        /**
         * @brief Converts microseconds to CPU cycles using an explicit frequency.
         * @param coreHzValue CPU core frequency in Hz (compile-time constant).
         * @param us Time budget in microseconds.
         */
        static constexpr auto fromUs(std::uint32_t coreHzValue, std::uint32_t us) -> CycleCpu
        {
            static_assert(sizeof(CycleCpu) == sizeof(std::uint32_t),
                          "CycleCpu must be a 32-bit unsigned integer type.");

            const std::uint64_t cycles64 =
                (static_cast<std::uint64_t>(coreHzValue) * static_cast<std::uint64_t>(us)) / 1'000'000ULL;

            const CycleCpu result = static_cast<CycleCpu>(cycles64);
            return result;
        }

        /**
         * @brief Converts milliseconds to CPU cycles using an explicit frequency.
         * @param coreHzValue CPU core frequency in Hz (compile-time constant).
         * @param ms Time budget in milliseconds.
         */
        static constexpr auto fromMs(std::uint32_t coreHzValue, std::uint32_t ms) -> CycleCpu
        {
            static_assert(sizeof(CycleCpu) == sizeof(std::uint32_t),
                          "CycleCpu must be a 32-bit unsigned integer type.");

            const std::uint64_t cycles64 =
                (static_cast<std::uint64_t>(coreHzValue) * static_cast<std::uint64_t>(ms)) / 1'000ULL;

            const CycleCpu result = static_cast<CycleCpu>(cycles64);
            return result;
        }
    };
}