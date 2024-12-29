#ifndef ScpiMEASureMessage_hpp
#define ScpiMEASureMessage_hpp

#include "Device/Inc/MeasurementType.hpp"
#include <array>
#include <cstring>
#include <variant>
#include <cstdio>

namespace Device
{
    // We have buffer in only one length so only one instance will be generated.
    template <std::size_t BufferSize>
    class ScpiMEASureMessage
    {
    public:
        bool generateMessage(Device::MeasurementType &measurement, std::array<std::uint8_t, BufferSize> &data, std::size_t &dataIndex)
        {
            bool status = true; // Track overall status
            // dataIndex = 0;           // We start writing at index 0
            char deviceId[16] = {0}; // Temporary buffer for device ID

            // 1) Resolve Device ID string
            if (!getDeviceId(measurement.source, deviceId))
            {
                status = false;
            }

            // 2) If still OK, add the SCPI header
            if (status)
            {
                status = addScpiHeader(deviceId, data, dataIndex);
            }

            // 3) Check that the variant actually holds valid measurement data
            //    (Assumes index() == 0 means "no data"; adjust if your variant uses a different scheme.)
            if (status)
            {
                if (measurement.data.index() == 0)
                {
                    status = false;
                }
            }

            // 4) If still OK, add the measurement value itself
            if (status)
            {
                // std::visit calls the matching lambda for whichever type is held in the variant
                std::visit(
                    [&](auto &&value)
                    {
                        // Combine the returned bool with our status
                        status = status && addMeasurement(data, dataIndex, value);
                    },
                    measurement.data);
            }

            // 5) If still OK, finalize the SCPI message (closing quote, etc.)
            if (status)
            {
                status = finalizeScpiMessage(data, dataIndex);
            }

            // If any step above failed, zero out dataIndex
            if (!status)
            {
                dataIndex = 0;
            }

            // 6) Single return statement
            return status;
        }

    private:
        bool addScpiHeader(const char *deviceId, std::array<std::uint8_t, BufferSize> &data, std::size_t &dataIndex)
        {
            int written = snprintf(reinterpret_cast<char *>(data.data() + dataIndex),
                                   BufferSize - dataIndex,
                                   "MEASure:%s:DATA \"2024-12-28T11:16:36Z,",
                                   deviceId);
            if (written < 0 || static_cast<std::size_t>(written) >= BufferSize - dataIndex)
            {
                return false; // Buffer overflow or error
            }

            dataIndex += static_cast<std::size_t>(written);
            return true;
        }

        template <typename T>
        bool addMeasurement(std::array<std::uint8_t, BufferSize> &data, std::size_t &dataIndex, T value)
        {
            int written = 0;
            if constexpr (std::is_same_v<T, std::uint8_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + dataIndex),
                                   BufferSize - dataIndex,
                                   "%u", value);
            }
            else if constexpr (std::is_same_v<T, std::uint16_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + dataIndex),
                                   BufferSize - dataIndex,
                                   "%hu", value);
            }
            else if constexpr (std::is_same_v<T, std::uint32_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + dataIndex),
                                   BufferSize - dataIndex,
                                   "%u", value);
            }
            else
            {
                // unknow data format
                return false;
            }

            if ((written < 0) || (static_cast<std::size_t>(written) >= BufferSize - dataIndex))
            {
                return false; // Buffer overflow or error
            }

            dataIndex += static_cast<std::size_t>(written);
            return true;
        }

        bool getDeviceId(Device::MeasurementDeviceId source, char *device)
        {
            bool status = true;
            switch (source)
            {
            case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1:
                strcpy(device, "DEVICE01");
                break;
            case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2:
                strcpy(device, "DEVICE02");
                break;
            case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3:
                strcpy(device, "DEVICE03");
                break;
            case Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_4:
                strcpy(device, "DEVICE04");
                break;
            case Device::MeasurementDeviceId::DEVICE_UART_1:
                strcpy(device, "DEVICE05");
                break;
            default:
                status = false;
            }
            return status;
        }

        bool finalizeScpiMessage(std::array<std::uint8_t, BufferSize> &data, std::size_t &dataIndex) const
        {
            if (dataIndex + 1 >= data.size())
            {
                return false; // Buffer overflow
            }
            data[dataIndex++] = '"'; // Close the quoted part
            return true;
        }

        constexpr static std::uint8_t ByteMask = 0xFF;
        constexpr static std::uint8_t ByteShift24 = 24;
        constexpr static std::uint8_t ByteShift16 = 16;
        constexpr static std::uint8_t ByteShift8 = 8;
    };

}

#endif
