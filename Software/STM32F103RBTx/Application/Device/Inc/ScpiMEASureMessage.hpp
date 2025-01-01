#ifndef ScpiMEASureMessage_hpp
#define ScpiMEASureMessage_hpp

#include "Device/Inc/MeasurementType.hpp"
#include <array>
#include <cstring>
#include <variant>
#include <cstdio>

namespace Device
{
    template <std::size_t BufferSize>
    class ScpiMEASureMessage
    {
    public:
        bool generate(
            Device::MeasurementType &measurement,
            std::array<std::uint8_t, BufferSize> &data,
            std::size_t offset,
            std::size_t &msgLength)
        {
            bool status = true;
            std::size_t currentIndex = offset;
            char deviceId[16] = {0};

            if (!getDeviceId(measurement.source, deviceId))
            {
                status = false;
            }

            if (status)
            {
                status = addScpiHeader(deviceId, data, currentIndex);
            }

            if (status)
            {
                if (measurement.data.index() == 0)
                {
                    status = false;
                }
            }

            if (status)
            {
                std::visit(
                    [&](auto &&value)
                    {
                        status = status && addMeasurement(data, currentIndex, value);
                    },
                    measurement.data);
            }

            if (status)
            {
                status = finalizeScpiMessage(data, currentIndex);
            }

            if (status)
            {
                msgLength = currentIndex - offset;
            }
            else
            {
                msgLength = 0;
            }

            return status;
        }

    private:
        bool addScpiHeader(const char *deviceId, std::array<std::uint8_t, BufferSize> &data, std::size_t &currentIndex)
        {
            int written = snprintf(reinterpret_cast<char *>(data.data() + currentIndex),
                                   BufferSize - currentIndex,
                                   "MEASure:%s:DATA \"2024-12-28T11:16:36Z,",
                                   deviceId);
            if (written < 0 || static_cast<std::size_t>(written) >= BufferSize - currentIndex)
            {
                return false;
            }

            currentIndex += static_cast<std::size_t>(written);
            return true;
        }

        template <typename T>
        bool addMeasurement(std::array<std::uint8_t, BufferSize> &data, std::size_t &currentIndex, T value)
        {
            int written = 0;
            if constexpr (std::is_same_v<T, std::uint8_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + currentIndex),
                                   BufferSize - currentIndex,
                                   "%u", value);
            }
            else if constexpr (std::is_same_v<T, std::uint16_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + currentIndex),
                                   BufferSize - currentIndex,
                                   "%hu", value);
            }
            else if constexpr (std::is_same_v<T, std::uint32_t>)
            {
                written = snprintf(reinterpret_cast<char *>(data.data() + currentIndex),
                                   BufferSize - currentIndex,
                                   "%u", value);
            }
            else
            {
                return false;
            }

            if ((written < 0) || (static_cast<std::size_t>(written) >= BufferSize - currentIndex))
            {
                return false;
            }

            currentIndex += static_cast<std::size_t>(written);
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

        bool finalizeScpiMessage(std::array<std::uint8_t, BufferSize> &data, std::size_t &currentIndex) const
        {
            if (currentIndex + 1 >= data.size())
            {
                return false;
            }
            data[currentIndex++] = '"';
            return true;
        }
    };
}

#endif
