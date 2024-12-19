#ifndef MeasurementSource_H_
#define MeasurementSource_H_

#include <cstdint>

namespace Device
{
    // Identify rom which device the data comes from.
    enum class MeasurementSource : std::uint8_t
    {
        DEVICE_PULSE_COUNTER_1 = 1u,
        DEVICE_PULSE_COUNTER_2 = 2u,
        DEVICE_PULSE_COUNTER_3 = 3u,
        DEVICE_PULSE_COUNTER_4 = 4u,
        DEVICE_UART_1 = 5u
    };

}

#endif
