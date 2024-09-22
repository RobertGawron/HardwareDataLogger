/**
 * @file MeasurementSourcesBuilder.hpp
 * @brief Declares the MeasurementSourcesBuilder class responsible for building and managing measurement sources.
 */

#ifndef MeasurementSourcesBuilder_h
#define MeasurementSourcesBuilder_h

#include <stdint.h>
#include "IApplicationComponentBuilder.hpp"
// Driver
#include "IPulseCounterDriver.hpp"
#include "IUartDriver.hpp"
// Device
#include "PulseCounterMeasurementSource.hpp"
#include "UartMeasurementSource.hpp"
// High-level components
#include "MeasurementCoordinator.hpp"

namespace BusinessLogic
{
    /**
     * @class MeasurementSourcesBuilder
     * @brief Responsible for building and managing measurement sources.
     *
     * The MeasurementSourcesBuilder class constructs and manages components related to measurement sources.
     * It requires drivers for pulse counters and UART to build the measurement sources, which can be platform-specific,
     * depending on whether the application is running in firmware or simulation.
     */
    class MeasurementSourcesBuilder : public IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Constructs the MeasurementSourcesBuilder with platform-specific drivers.
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
        explicit MeasurementSourcesBuilder(
            Driver::IPulseCounterDriver &pulseCounterDriver1,
            Driver::IPulseCounterDriver &pulseCounterDriver2,
            Driver::IPulseCounterDriver &pulseCounterDriver3,
            Driver::IPulseCounterDriver &pulseCounterDriver4,
            Driver::IUartDriver &uart);

        /**
         * @brief Default destructor.
         */
        virtual ~MeasurementSourcesBuilder() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementSourcesBuilder(const MeasurementSourcesBuilder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementSourcesBuilder& The assigned object.
         */
        MeasurementSourcesBuilder &operator=(const MeasurementSourcesBuilder &) = delete;

        /**
         * @brief Initializes the measurement sources.
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() override;

        /**
         * @brief Starts the measurement sources.
         * @return true if the components started successfully, false otherwise.
         */
        virtual bool start() override;

        /**
         * @brief Stops the measurement sources.
         * @return true if the components stopped successfully, false otherwise.
         */
        virtual bool stop() override;

        /**
         * @brief Ticks the measurement sources for periodic updates.
         * @return true if the tick operation was successful, false otherwise.
         */
        virtual bool tick() override;

        /**
         * @brief Registers the measurement sources with a data coordinator.
         *
         * This function registers the pulse counter and UART measurement sources with the provided
         * MeasurementCoordinator, enabling coordination between the measurement sources.
         *
         * @param coordinator Reference to the MeasurementCoordinator.
         * @return true if the sources were successfully registered, false otherwise.
         */
        virtual bool registerSources(MeasurementCoordinator &coordinator);

    private:
        /** @brief Number of pulse counters available for measurement. */
        static const uint8_t PulseCounterAmount{4};

        /** @brief Array of pulse counter measurement sources. */
        Device::PulseCounterMeasurementSource pulseCounter[PulseCounterAmount];

        /** @brief Reference to the UART driver used for receiving measurement data. */
        Driver::IUartDriver &uart;

        /** @brief UART measurement source for receiving measurements over UART. */
        Device::UartMeasurementSource uartMeasurementSource;
    };
}

#endif // MeasurementSourcesBuilder_h