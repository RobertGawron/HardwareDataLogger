#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include "Driver/Inc/UartExchangeStatus.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <array>
#include <cstddef> // For std::size_t

#include <cstdint>
// #include <stdio.h>
#include <variant>     // Provides std::visit
#include <type_traits> // Provides std::decay_t

#include <cstring>
#include <array>
// #include <iostream>

namespace Device
{

    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver)
        : driver(_driver)
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
        bool status = false;

        // we dont save scpi message at zero position because we need space for message header
        std::size_t offset = dataLink.HeaderLength;
        std::size_t msgLength = 0u;

        scpiMessage.generate(measurement, scpiBuffer, offset, msgLength);

        std::size_t outLength = 0;
        dataLink.generate(scpiBuffer, msgLength, dataLinkBuffer, outLength);
        /*
           // Transmit the encoded data
           auto timeout = 1000;
           Driver::UartExchangeStatus result = driver.transmit(encodedData.data(), static_cast<std::uint16_t>(encodedLength), timeout);
           status = (result == Driver::UartExchangeStatus::Ok);
   */
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
