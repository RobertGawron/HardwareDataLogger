module;

#include <cstdint>
#include <type_traits>

#include "stm32f1xx.h"
#include "core_cm3.h" // DWT / CoreDebug

export module Driver.CycleClock;

import Driver.CycleCpu;

export namespace Driver
{
#if !defined(DWT)
    static_assert(false, "CycleClock requires DWT to be defined.");
#endif

#if !defined(CoreDebug)
    static_assert(false,
                  "CycleClock requires CoreDebug to be defined.");
#endif

#if !defined(DWT_CTRL_CYCCNTENA_Msk)
    static_assert(false,
                  "CycleClock requires DWT_CTRL_CYCCNTENA_Msk.");
#endif

#if !defined(CoreDebug_DEMCR_TRCENA_Msk)
    static_assert(false,
                  "CycleClock requires CoreDebug_DEMCR_TRCENA_Msk.");
#endif

    static_assert(std::is_integral_v<CycleCpu>,
                  "CycleCpu must be an integral type. It represents a hardware counter value.");

    static_assert(std::is_unsigned_v<CycleCpu>,
                  "CycleCpu must be unsigned. Wrap-around elapsed computation relies on modulo arithmetic.");

    static_assert(sizeof(CycleCpu) >= sizeof(std::uint32_t),
                  "CycleCpu must be at least 32-bit. DWT->CYCCNT is a 32-bit counter.");

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
            CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
            DWT->CYCCNT = 0U;
            DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
        }

        /**
         * @brief Read the current cycle counter value.
         *
         * @return Current value of DWT->CYCCNT converted to CycleCpu.
         */
        [[nodiscard]] static constexpr auto now() noexcept -> CycleCpu
        {
            const std::uint32_t counter = DWT->CYCCNT;
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