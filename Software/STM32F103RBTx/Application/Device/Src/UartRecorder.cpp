#include "Device/Inc/UartRecorder.hpp"

namespace Device
{
    bool UartRecorder::notify([[maybe_unused]] const MeasurementType &measurement) noexcept
    {
        return true;
    }

    bool UartRecorder::onInit() noexcept
    {
        //  return driver.init();
        return true;
    }

    bool UartRecorder::onStart() noexcept
    {
        // return driver.start();
        return true;
    }

    bool UartRecorder::onStop() noexcept
    {
        // return driver.stop();
        return true;
    }

} // namespace Device