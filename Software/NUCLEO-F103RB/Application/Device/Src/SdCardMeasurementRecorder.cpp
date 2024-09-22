#include "SdCardMeasurementRecorder.hpp"

namespace Device
{

    SdCardMeasurementRecorder::SdCardMeasurementRecorder(Driver::ISdCardDriver &_driver) : driver(_driver)
    {
    }

    bool SdCardMeasurementRecorder::onInitialize()
    {
        bool status = driver.initialize();
        return status;
    }

    bool SdCardMeasurementRecorder::onStart()
    {
        bool status = driver.start();
        return status;
    }

    bool SdCardMeasurementRecorder::onStop()
    {
        bool status = driver.stop();
        return status;
    }

    bool SdCardMeasurementRecorder::onReset()
    {
        bool status = driver.reset();
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
