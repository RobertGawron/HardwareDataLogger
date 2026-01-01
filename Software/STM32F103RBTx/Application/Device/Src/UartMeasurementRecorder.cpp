#include "Device/Inc/UartMeasurementRecorder.hpp"

namespace Device
{
    bool UartMeasurementRecorder::notify([[maybe_unused]] const MeasurementType &measurement) noexcept
    {
        // TODO: Implement UART transmission of measurement data
        return true;
    }

    bool UartMeasurementRecorder::onInitialize() noexcept
    {
        return driver.initialize();
    }

    bool UartMeasurementRecorder::onStart() noexcept
    {
        return driver.start();
    }

    bool UartMeasurementRecorder::onStop() noexcept
    {
        return driver.stop();
    }

    bool UartMeasurementRecorder::onReset() noexcept
    {
        return driver.reset();
    }

} // namespace Device