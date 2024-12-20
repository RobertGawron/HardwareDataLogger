#include "BusinessLogic/Inc/MeasurementSourcesFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"

#include <cstdint>

namespace BusinessLogic
{

    MeasurementSourcesFactory::MeasurementSourcesFactory(Driver::IPulseCounterDriver &_pulseCounterDriver1,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver2,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver3,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver4,
                                                         Driver::IUartDriver &_uart)
        : pulseCounter{
              Device::PulseCounterMeasurementSource(
                  Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1,
                  _pulseCounterDriver1),
              Device::PulseCounterMeasurementSource(
                  Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2,
                  _pulseCounterDriver2),
              Device::PulseCounterMeasurementSource(
                  Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3,
                  _pulseCounterDriver3),
              Device::PulseCounterMeasurementSource(
                  Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_4,
                  _pulseCounterDriver4)},
          uart(_uart), uartMeasurementSource(Device::MeasurementDeviceId::DEVICE_UART_1, uart)
    {
    }

    bool MeasurementSourcesFactory::initialize()
    {

        return true;
    }

    bool MeasurementSourcesFactory::registerSources(MeasurementCoordinator &coordinator)
    {
        bool status = true;

        for (std::uint8_t i = 0u; i < PulseCounterAmount; i++)
        {
            if (!coordinator.addObserver(pulseCounter[i]))
            {
                status = false;
                break;
            }
        }

        if (status)
        {
            status = coordinator.addObserver(uartMeasurementSource);
        }

        return status;
    }
}
