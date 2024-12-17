#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Driver/Interfaces/ISdCardDriver.hpp"

namespace Device
{

    SdCardMeasurementRecorder::SdCardMeasurementRecorder(Driver::ISdCardDriver &_driver) : driver(_driver)
    {
    }

    bool SdCardMeasurementRecorder::onInitialize()
    {
        const bool status = driver.initialize();
        return status;
    }

    bool SdCardMeasurementRecorder::onStart()
    {
        const bool status = driver.start();
        return status;
    }

    bool SdCardMeasurementRecorder::onStop()
    {
        const bool status = driver.stop();
        return status;
    }

    bool SdCardMeasurementRecorder::onReset()
    {
        const bool status = driver.reset();
        return status;
    }

    void SdCardMeasurementRecorder::write()
    {
    }

    void SdCardMeasurementRecorder::flush()
    {
    }

    void SdCardMeasurementRecorder::notify()
    {
    }
}
