module;

#include <cstdint>
#include <type_traits>

// #include "stm32f1xx.h"
// #include "core_cm3.h" // DWT / CoreDebug

export module Driver.CycleClock;

import Driver.CycleCpu;

export namespace Driver
{

    /**
     * @brief Access to the CPU cycle counter (DWT->CYCCNT).
     *
     * This utility enables and reads the Cortex-M DWT cycle counter.
     * It is intended for profiling and time measurements in CPU cycles.
     */
    class CycleClock final
    {
    public:
        CycleClock() = delete;
        ~CycleClock() = delete;

        CycleClock(const CycleClock &) = delete;
        CycleClock &operator=(const CycleClock &) = delete;
        CycleClock(CycleClock &&) = delete;
        CycleClock &operator=(CycleClock &&) = delete;

        /**
         * @brief Enable the DWT cycle counter and reset it to zero.
         *
         * Precondition: DWT and CoreDebug are available for the selected target.
         * Note: Some MCUs/cores may prevent enabling CYCCNT (e.g., due to debug/lock settings).
         */
        static constexpr auto init() noexcept -> void
        {
            //   CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
            //   DWT->CYCCNT = 0U;
            //   DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
        }

        /**
         * @brief Read the current cycle counter value.
         *
         * @return Current value of DWT->CYCCNT converted to CycleCpu.
         */
        [[nodiscard]] static constexpr auto now() noexcept -> CycleCpu
        {
            const std::uint32_t counter = 0; // DWT->CYCCNT;
            return static_cast<CycleCpu>(counter);
        }

        /**
         * @brief Compute elapsed cycles between two readings.
         *
         * @param start Counter value at start.
         * @param end   Counter value at end.
         * @return Elapsed cycles from start to end.
         */
        [[nodiscard]] static constexpr auto elapsed(CycleCpu start,
                                                    CycleCpu end) noexcept -> CycleCpu
        {
            // Unsigned integer, will work correctly even if overflow happened.
            const CycleCpu result = end - start;
            return result;
        }
    };
} // namespace Driver