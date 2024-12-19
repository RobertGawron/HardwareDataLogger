/**
 * @file MeasurementSourcesFactory.hpp
 * @brief Declares the MeasurementSourcesFactory class responsible for building and managing measurement sources.
 */

#ifndef MeasurementSourcesFactory_h
#define MeasurementSourcesFactory_h

#include "BusinessLogic/Interfaces/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/UartMeasurementSource.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <cstdint>
#include <array>

namespace BusinessLogic
{
    /**
     * @class MeasurementSourcesFactory
     * @brief Responsible for building and managing measurement sources.
     *
     * The MeasurementSourcesFactory class constructs and manages components related to measurement sources.
     * It requires drivers for pulse counters and UART to build the measurement sources, which can be platform-specific,
     * depending on whether the application is running in firmware or simulation.
     */
    class MeasurementSourcesFactory : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs the MeasurementSourcesFactory with platform-specific drivers.
         *
         * The constructor requires pulse counter drivers for measurement collection and a UART driver for UART-based
         * measurements. Other components are constructed internally.
         *
         * @param pulseCounterDriver1 Reference to the first pulse counter driver.
         * @param pulseCounterDriver2 Reference to the second pulse counter driver.
         * @param pulseCounterDriver3 Reference to the third pulse counter driver.
         * @param pulseCounterDriver4 Reference to the fourth pulse counter driver.
         * @param uart Reference to the UART driver for receiving measurement data.
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
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementSourcesFactory(const MeasurementSourcesFactory &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementSourcesFactory& The assigned object.
         */
        MeasurementSourcesFactory &operator=(const MeasurementSourcesFactory &) = delete;

        /**
         * @brief Initializes the measurement sources.
         * @return true if initialization was successful, false otherwise.
         */
        bool initialize() override;

        /**
         * @brief Registers the measurement sources with a data coordinator.
         *
         * This function registers the pulse counter and UART measurement sources with the provided
         * MeasurementCoordinator, enabling coordination between the measurement sources.
         *
         * @param coordinator Reference to the MeasurementCoordinator.
         * @return true if the sources were successfully registered, false otherwise.
         */
        bool registerSources(MeasurementCoordinator &coordinator);

    private:
        /** @brief Number of pulse counters available for measurement. */
        static constexpr std::size_t PulseCounterAmount{4};

        std::array<Device::PulseCounterMeasurementSource, PulseCounterAmount> pulseCounter;

        /** @brief Reference to the UART driver used for receiving measurement data. */
        Driver::IUartDriver &uart;

        /** @brief UART measurement source for receiving measurements over UART. */
        Device::UartMeasurementSource uartMeasurementSource;
    };
}

#endif // MeasurementSourcesFactory_h
