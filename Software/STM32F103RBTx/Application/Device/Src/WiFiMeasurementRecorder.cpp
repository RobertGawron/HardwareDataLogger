#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
// #include "Driver/Inc/UartExchangeStatus.hpp"

#include <cstdint>
#include <stdio.h>
namespace Device
{

    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool WiFiMeasurementRecorder::onInitialize()
    {
        const bool status = driver.initialize();
        return status;
    }

    bool WiFiMeasurementRecorder::onStart()
    {
        const bool status = driver.start();
        return status;
    }

    bool WiFiMeasurementRecorder::onStop()
    {
        const bool status = driver.stop();
        return status;
    }

    bool WiFiMeasurementRecorder::onReset()
    {
        const bool status = driver.reset();
        return status;
    }

    bool WiFiMeasurementRecorder::write(Device::MeasurementType &measurement)
    {

        printf("= START=, data %d\n", measurement);

        std::uint16_t len = 3; // TODO

        std::uint8_t data[6] = {0}; // Buffer to hold data + terminators

        // Use std::visit to safely extract the value from the variant
        std::visit([&](auto &&value)
                   {
        using T = std::decay_t<decltype(value)>;

        if constexpr (std::is_same_v<T, std::uint8_t>)
        {
            data[0] = value; // Single byte
            data[1] = '\r';
            data[2] = '\n';
          
printf("i am here 1, data %u\n", static_cast<unsigned int>(data[0]));
        }
        else if constexpr (std::is_same_v<T, std::uint16_t>)
        {
            data[0] = static_cast<std::uint8_t>((value >> 8) & 0xFF); // High byte
            data[1] = static_cast<std::uint8_t>(value & 0xFF);        // Low byte
            data[2] = '\r';
            data[3] = '\n';
            
            printf("i am here 2\n");    
        }
        else if constexpr (std::is_same_v<T, std::uint32_t>)
        {
            data[0] = static_cast<std::uint8_t>((value >> 24) & 0xFF); // Byte 3
            data[1] = static_cast<std::uint8_t>((value >> 16) & 0xFF); // Byte 2
            data[2] = static_cast<std::uint8_t>((value >> 8) & 0xFF);  // Byte 1
            data[3] = static_cast<std::uint8_t>(value & 0xFF);         // Byte 0
      
            data[4] = '\r';
            data[5] = '\n';
            
            len = 5;

            printf("i am here 4\n");      
        } }, measurement);

        printf("= STOP=, data %d\n", measurement);

        // Append terminator bytes
        // data[sizeof(data) - 2] = '\r';
        //  data[sizeof(data) - 1] = '\n';

        //  auto len = sizeof(data) / sizeof(data[0]);
        // std::uint16_t len = 3; // hack for now

        driver.transmit(data, len, Driver::IUartDriver::MaxDelay);

        /*
                    std::uint8_t data_rx[30] = {0};
                    auto len = 3;
                    status2 = driver.receive(data_rx, len, 0xFFFFU);

                    volatile int a;

        */

        const bool status = true;
        return status;
    }

    bool WiFiMeasurementRecorder::flush()
    {
        const bool status = true;
        return status;
    }

    bool WiFiMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        const bool status = write(measurement);
        return status;
    }
}
