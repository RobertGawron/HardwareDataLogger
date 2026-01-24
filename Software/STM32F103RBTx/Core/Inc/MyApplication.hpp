#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    bool app_init(void);
    bool app_start(void);
    bool app_stop(void);

    /**
     * Called frequently from the main loop.
     * Executes up to the configured number of pending scheduler slots.
     */
    bool app_tick(void);

    /**
     * Called from a periodic timer ISR (or HAL timer callback).
     * Must be short and ISR-safe: only signals the scheduler that one time slot elapsed.
     */
    void app_timeSlotIsr(void);

#ifdef __cplusplus
}
#endif
