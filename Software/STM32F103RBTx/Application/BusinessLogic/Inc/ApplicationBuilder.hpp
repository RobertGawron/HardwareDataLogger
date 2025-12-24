/**
 * @file ApplicationBuilder.hpp
 * @brief Defines the ApplicationBuilder class responsible for orchestrating application component initialization.
 */

#ifndef APPLICATIONBUILDER_H_
#define APPLICATIONBUILDER_H_

#include "BusinessLogic/Interface/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "BusinessLogic/Inc/MeasurementSourcesFactory.hpp"
#include "BusinessLogic/Inc/MeasurementStoresFactory.hpp"
#include "BusinessLogic/Inc/HmiFactory.hpp"

namespace BusinessLogic
{
    /**
     * @class ApplicationBuilder
     * @brief Orchestrates construction and initialization of core application components.
     *
     * Implements the builder pattern to coordinate initialization and registration of:
     * - Measurement sources (data producers)
     * - Data stores (data consumers)
     * - Human-Machine Interface (HMI)
     * - Core coordination mechanisms
     *
     * Relies on platform-specific factory implementations to provide concrete components.
     * Implements the IApplicationComponentFactory interface for system initialization.
     */
    class ApplicationBuilder : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs an ApplicationBuilder with platform-specific component factory.
         * @param factory Reference to platform factory providing concrete implementations
         */
        explicit ApplicationBuilder(IPlatformFactory &factory);

        /**
         * @brief Deleted default constructor.
         */
        ApplicationBuilder() = delete;

        /**
         * @brief Default destructor.
         */
        ~ApplicationBuilder() override = default;

        /**
         * @brief Deleted copy constructor.
         */
        ApplicationBuilder(const ApplicationBuilder &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        ApplicationBuilder &operator=(const ApplicationBuilder &) = delete;

        /**
         * @brief Initializes all application components.
         *
         * Calls initialize() on all managed factories and components.
         *
         * @return true if all components initialized successfully, false otherwise
         */
        bool initialize() override;

        /**
         * @brief Starts all application components.
         * @return true if all components started successfully, false otherwise
         */
        virtual bool start();

        /**
         * @brief Stops all application components.
         * @return true if all components stopped successfully, false otherwise
         */
        virtual bool stop();

        /**
         * @brief Performs periodic update of application components.
         * @return true if tick was processed successfully, false otherwise
         */
        virtual bool tick();

    private:
        /** @brief Factory for measurement data sources */
        MeasurementSourcesFactory sourceBuilder;

        /**
         * @brief Cache measurement recorder (directly managed)
         *
         * Required by both stores factory and HMI, managed directly
         * here rather than through stores factory.
         */
        Device::CacheMeasurementRecorder cacheRecorder;

        /** @brief Factory for measurement data stores */
        MeasurementStoresFactory storesBuilder;

        /** @brief Central repository for measurement data */
        MeasurementDataStore dataStore;

        /** @brief Coordinates data flow between sources and stores */
        MeasurementCoordinator measurementCoordinator;

        /** @brief Factory for Human-Machine Interface components */
        HmiFactory hmiFactory;
    };
}

#endif // APPLICATIONBUILDER_H_
