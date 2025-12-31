#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationFacade.hpp"

#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/UartMeasurementSource.hpp"

#include "Driver/Interface/IPulseCounterDriver.hpp"
#include "Driver/Interface/IUartDriver.hpp"

namespace BusinessLogic
{
    ApplicationFacade::ApplicationFacade(IPlatformFactory &platformFactory)
        : pulseCounter1(Device::MeasurementDeviceId::PULSE_COUNTER_1,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncA)),
          pulseCounter2(Device::MeasurementDeviceId::PULSE_COUNTER_2,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncB)),
          pulseCounter3(Device::MeasurementDeviceId::PULSE_COUNTER_3,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC)),
          pulseCounter4(Device::MeasurementDeviceId::PULSE_COUNTER_4,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncD)),
          uartReceiver(Device::MeasurementDeviceId::DEVICE_UART_1,
                       platformFactory.getUartDriver(Driver::UartId::MEASUREMENT_RECEIVER)),
          sources{std::ref(pulseCounter1), std::ref(pulseCounter2),
                  std::ref(pulseCounter3), std::ref(pulseCounter4),
                  std::ref(uartReceiver)},

          wifiRecorder(platformFactory.getUartDriver(Driver::UartId::TRANSMIT_VIA_WIFI)),
          sdCardRecorder(platformFactory.getSdCardDriver()),
          recorders{wifiRecorder, sdCardRecorder},

          measurementCoordinator(sources, recorders),

          display(platformFactory.getDisplayDriver()),
          brightnessRegulator(
              platformFactory.getAmbientLightSensorDriver(),
              platformFactory.getDisplayBrightnessDriver()),
          keyboard(platformFactory.getKeyboardDriver()),
          hmi(display,
              brightnessRegulator,
              keyboard)
    {
    }

    bool ApplicationFacade::initialize()
    {
        const bool status = measurementCoordinator.initialize();

        return status;
    }

    bool ApplicationFacade::start()
    {
        const bool status = measurementCoordinator.start();

        return status;
    }

    bool ApplicationFacade::stop()
    {
        const bool status = measurementCoordinator.stop();

        return status;
    }

    bool ApplicationFacade::tick()
    {

        const bool status = measurementCoordinator.tick();

        return status;
    }
} // namespace BusinessLogic
