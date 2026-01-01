#include "BusinessLogic/Inc/ApplicationFacade.hpp"
#include "BusinessLogic/Interface/IPlatformFactory.hpp"

namespace BusinessLogic
{
    ApplicationFacade::ApplicationFacade(IPlatformFactory &platformFactory) noexcept
        : pulseCounter1{Device::MeasurementDeviceId::PULSE_COUNTER_1,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncA)},
          pulseCounter2{Device::MeasurementDeviceId::PULSE_COUNTER_2,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncB)},
          pulseCounter3{Device::MeasurementDeviceId::PULSE_COUNTER_3,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC)},
          pulseCounter4{Device::MeasurementDeviceId::PULSE_COUNTER_4,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncD)},
          uartReceiver{Device::MeasurementDeviceId::DEVICE_UART_1,
                       platformFactory.getUartDriver(Driver::UartId::MEASUREMENT_RECEIVER)},
          sources{std::ref(pulseCounter1), std::ref(pulseCounter2),
                  std::ref(pulseCounter3), std::ref(pulseCounter4),
                  std::ref(uartReceiver)},
          wifiRecorder{platformFactory.getUartDriver(Driver::UartId::TRANSMIT_VIA_WIFI)}, sdCardRecorder{platformFactory.getSdCardDriver()}, recorders{std::ref(wifiRecorder), std::ref(sdCardRecorder)}, measurementCoordinator{sources, recorders}, display{platformFactory.getDisplayDriver()}, brightnessRegulator{platformFactory.getAmbientLightSensorDriver(),
                                                                                                                                                                                                                                                                                                                       platformFactory.getDisplayBrightnessDriver()},
          keyboard{platformFactory.getKeyboardDriver()}, hmi{display, brightnessRegulator, keyboard}
    {
    }

    bool ApplicationFacade::initialize() noexcept
    {
        return measurementCoordinator.initialize();
    }

    bool ApplicationFacade::start() noexcept
    {
        return measurementCoordinator.start();
    }

    bool ApplicationFacade::stop() noexcept
    {
        return measurementCoordinator.stop();
    }

    bool ApplicationFacade::tick() noexcept
    {
        return measurementCoordinator.tick();
    }

} // namespace BusinessLogic