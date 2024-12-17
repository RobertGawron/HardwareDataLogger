#ifndef MeasurementSource_H_
#define MeasurementSource_H_

#include <cstdint>

namespace Device
{
    // Identify rom which device the data comes from.
    enum class MeasurementSource : std::uint8_t
    {
        DEVICE_GPIO_1 = 1u,
        DEVICE_GPIO_2 = 2u,
        DEVICE_GPIO_3 = 3u,
        DEVICE_GPIO_4 = 4u,
        DEVICE_UART = 1u
    };

}

#endif
