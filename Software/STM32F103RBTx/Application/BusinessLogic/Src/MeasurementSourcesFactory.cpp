#include "BusinessLogic/Inc/MeasurementSourcesFactory.hpp"
#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <cstdint>

namespace BusinessLogic
{

    MeasurementSourcesFactory::MeasurementSourcesFactory(Driver::IPulseCounterDriver &_pulseCounterDriver1,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver2,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver3,
                                                         Driver::IPulseCounterDriver &_pulseCounterDriver4,
                                                         Driver::IUartDriver &_uart)
        : pulseCounter{
              Device::PulseCounterMeasurementSource(_pulseCounterDriver1),
              Device::PulseCounterMeasurementSource(_pulseCounterDriver2),
              Device::PulseCounterMeasurementSource(_pulseCounterDriver3),
              Device::PulseCounterMeasurementSource(_pulseCounterDriver4)},
          uart(_uart), uartMeasurementSource(uart)
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
