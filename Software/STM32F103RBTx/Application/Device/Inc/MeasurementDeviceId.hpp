#ifndef MeasurementDeviceId_H_
#define MeasurementDeviceId_H_

#include <cstdint>

namespace Device
{
    // Identify rom which device the data comes from.
    enum class MeasurementDeviceId : std::uint8_t
    {
        DEVICE_PULSE_COUNTER_1 = 0u,
        DEVICE_PULSE_COUNTER_2 = 1u,
        DEVICE_PULSE_COUNTER_3 = 2u,
        DEVICE_PULSE_COUNTER_4 = 3u,
        DEVICE_UART_1 = 4u,
        LAST_NOT_USED
    };

}

#endif
