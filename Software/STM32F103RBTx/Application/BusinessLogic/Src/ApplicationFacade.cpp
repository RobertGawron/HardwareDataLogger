#include "BusinessLogic/Inc/ApplicationFacade.hpp"
#include "PlatformFactory.hpp"

namespace BusinessLogic
{
    ApplicationFacade::ApplicationFacade(Driver::PlatformFactory &drivers) noexcept
        : pulseCounter1{Device::MeasurementDeviceId::PULSE_COUNTER_1, drivers.counter1},
          pulseCounter2{Device::MeasurementDeviceId::PULSE_COUNTER_2, drivers.counter2},
          pulseCounter3{Device::MeasurementDeviceId::PULSE_COUNTER_3, drivers.counter3},
          pulseCounter4{Device::MeasurementDeviceId::PULSE_COUNTER_4, drivers.counter4},
          uartReceiver{Device::MeasurementDeviceId::DEVICE_UART_1, drivers.measurementUart},
          sources{std::ref(pulseCounter1), std::ref(pulseCounter2),
                  std::ref(pulseCounter3), std::ref(pulseCounter4),
                  std::ref(uartReceiver)},
          wifiRecorder{drivers.wifiUart},
          sdCardRecorder{drivers.sdCard},
          recorders{std::ref(wifiRecorder), std::ref(sdCardRecorder)},
          measurementCoordinator{sources, recorders},
          display{drivers.display},
          brightnessRegulator{drivers.LightSensor, drivers.displayBrightness},
          keyboard{drivers.keyboard},
          hmi{display, brightnessRegulator, keyboard}
    {
    }

    bool ApplicationFacade::onInit() noexcept
    {
        return measurementCoordinator.init();
    }

    bool ApplicationFacade::onStart() noexcept
    {
        return measurementCoordinator.start();
    }

    bool ApplicationFacade::onStop() noexcept
    {
        return measurementCoordinator.stop();
    }

    bool ApplicationFacade::onTick() noexcept
    {
        return measurementCoordinator.tick();
    }

} // namespace BusinessLogic