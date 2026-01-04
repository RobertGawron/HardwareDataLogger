module Device.UartRecorder;

namespace Device
{
    auto UartRecorder::notify([[maybe_unused]] const MeasurementType &measurement) noexcept -> bool
    {
        return true;
    }

    auto UartRecorder::onInit() noexcept -> bool
    {
        //  return driver.init();
        return true;
    }

    auto UartRecorder::onStart() noexcept -> bool
    {
        // return driver.start();
        return true;
    }

    auto UartRecorder::onStop() noexcept -> bool
    {
        // return driver.stop();
        return true;
    }

} // namespace Device