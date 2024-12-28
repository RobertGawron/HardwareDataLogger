#include "Device/Inc/UartMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <cstring>
#include <array>
#include <iostream>
namespace Device
{

    UartMeasurementRecorder::UartMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool UartMeasurementRecorder::flush()
    {
        return true;
    }

    bool UartMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        //  auto data = "MEAS:VOLT:DATA \"2024-12-28T11:16:36Z,8.23\"";
        //  auto size = std::strlen(data);
        /*
                std::cout << "********************************** CALLED ***************************************" << std::endl;

                const char *data = "MEAS:VOLT:DATA \"2024-12-28T11:16:36Z,8.23\"";
                constexpr size_t maxSize = 256;
                auto size = std::strlen(data);

                // Create an std::array with maxSize
                std::array<uint8_t, maxSize> data2 = {};

                // Set the first element to the length of the data
                data2[0] = static_cast<uint8_t>(size);

                // Copy the data into the array starting at the second position
                std::memcpy(data2.data() + 1, data, size);

                // driver.transmit((data), size, 1000);
                // driver.transmit(const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(data2)), size, 1000);

                // driver.transmit(data2.data(), size + 1, 1000);

                //  driver.transmit(const_cast<uint8_t *>(data), size, 1000);
                //   MEAS : VOLT : DATA "2024-12-28T11:16:36Z,8.23"

                //               (void)measurement; // Explicitly suppresses "unused parameter" warning
        */
        return true;
    }

}
