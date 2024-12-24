/**
 * @file MeasurementSourcesFactory.hpp
 * @brief Declares the MeasurementSourcesFactory class for creating measurement data sources.
 */

#ifndef MeasurementSourcesFactory_h
#define MeasurementSourcesFactory_h

#include "BusinessLogic/Interfaces/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/UartMeasurementSource.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
#include <array>

namespace BusinessLogic
{
    /**
     * @class MeasurementSourcesFactory
     * @brief Creates and manages measurement data source components.
     *
     * Constructs and initializes pulse counter and UART-based measurement sources.
     * Implements the IApplicationComponentFactory interface for system initialization.
     */
    class MeasurementSourcesFactory : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs factory with required drivers.
         * @param pulseCounterDriver1 Driver for pulse counter 1
         * @param pulseCounterDriver2 Driver for pulse counter 2
         * @param pulseCounterDriver3 Driver for pulse counter 3
         * @param pulseCounterDriver4 Driver for pulse counter 4
         * @param uart Driver for UART communication
         */
        explicit MeasurementSourcesFactory(
            Driver::IPulseCounterDriver &pulseCounterDriver1,
            Driver::IPulseCounterDriver &pulseCounterDriver2,
            Driver::IPulseCounterDriver &pulseCounterDriver3,
            Driver::IPulseCounterDriver &pulseCounterDriver4,
            Driver::IUartDriver &uart);

        /**
         * @brief Default destructor.
         */
        ~MeasurementSourcesFactory() override = default;

        /**
         * @brief Deleted copy constructor.
         */
        MeasurementSourcesFactory(const MeasurementSourcesFactory &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        MeasurementSourcesFactory &operator=(const MeasurementSourcesFactory &) = delete;

        /**
         * @brief Initializes all measurement sources.
         * @return true if all sources initialized successfully, false otherwise
         */
        bool initialize() override;

        /**
         * @brief Registers all sources with the measurement coordinator.
         * @param coordinator Reference to the measurement coordinator
         * @return true if all sources registered successfully, false otherwise
         */
        bool registerSources(MeasurementCoordinator &coordinator);

    private:
        /** @brief Number of pulse counter sources */
        static constexpr std::size_t PulseCounterAmount{4};

        /** @brief Array of pulse counter measurement sources */
        std::array<Device::PulseCounterMeasurementSource, PulseCounterAmount> pulseCounter;

        /** @brief UART driver reference for measurement source */
        Driver::IUartDriver &uart;

        /** @brief UART-based measurement source */
        Device::UartMeasurementSource uartMeasurementSource;
    };
}

#endif // MeasurementSourcesFactory_h
