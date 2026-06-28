module;

#include <cstdint>

export module Device.MeasurementDeviceId;

export namespace Device
{
    /**
     * @enum MeasurementDeviceId
     * @brief Identifies the source device for measurement data.
     */
    enum class MeasurementDeviceId : std::uint8_t
    {
        PULSE_COUNTER_1 = 0U, ///< First pulse counter device.
        PULSE_COUNTER_2 = 1U, ///< Second pulse counter device.
        PULSE_COUNTER_3 = 2U, ///< Third pulse counter device.
        PULSE_COUNTER_4 = 3U, ///< Fourth pulse counter device.
        DEVICE_UART_1 = 4U,   ///< UART device.
        LAST_NOT_USED = 5U    ///< Placeholder for upper bound or unused value.
    };
}