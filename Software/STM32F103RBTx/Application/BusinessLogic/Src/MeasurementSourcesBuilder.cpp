#include "BusinessLogic/Inc/MeasurementSourcesBuilder.hpp"

namespace BusinessLogic
{

    MeasurementSourcesBuilder::MeasurementSourcesBuilder(Driver::IPulseCounterDriver &_pulseCounterDriver1,
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

    bool MeasurementSourcesBuilder::initialize()
    {

        return true;
    }

    bool MeasurementSourcesBuilder::registerSources(MeasurementCoordinator &coordinator)
    {
        bool status = true;
        for (uint8_t i = 0u; (i < PulseCounterAmount) && status; i++)
        {
            status = coordinator.addObserver(pulseCounter[i]);
        }

        if (status)
        {
            coordinator.addObserver(uartMeasurementSource);
        }

        return status;
    }
}
