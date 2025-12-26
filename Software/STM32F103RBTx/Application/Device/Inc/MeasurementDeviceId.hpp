#ifndef MeasurementDeviceId_H_
#define MeasurementDeviceId_H_

#include <cstdint>

namespace Device
{
    /**
     * @enum MeasurementDeviceId
     * @brief Identifies the source device for measurement data.
     */
    enum class MeasurementDeviceId : std::uint8_t
    {
        PULSE_COUNTER_1 = 0u, ///< First pulse counter device.
        PULSE_COUNTER_2 = 1u, ///< Second pulse counter device.
        PULSE_COUNTER_3 = 2u, ///< Third pulse counter device.
        PULSE_COUNTER_4 = 3u, ///< Fourth pulse counter device.
        DEVICE_UART_1 = 4u,   ///< UART device.
        LAST_NOT_USED = 5u    ///< Placeholder for upper bound or unused value.
    };
}

#endif // MeasurementDeviceId_H_
