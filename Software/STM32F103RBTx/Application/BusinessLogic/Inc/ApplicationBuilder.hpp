/**
 * @file ApplicationBuilder.hpp
 * @brief Defines the ApplicationBuilder class responsible for building and initializing
 *        all main objects of the application.
 */

#ifndef APPLICATIONBUILDER_H_
#define APPLICATIONBUILDER_H_

#include "BusinessLogic/Interfaces/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"

#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"

#include "BusinessLogic/Inc/MeasurementSourcesFactory.hpp"
#include "BusinessLogic/Inc/MeasurementStoresFactory.hpp"

#include "BusinessLogic/Inc/HmiFactory.hpp"

namespace BusinessLogic
{
    /**
     * @class ApplicationBuilder
     * @brief Implements the builder pattern and is responsible for correctly building and
     *        initializing all the main objects of the application.
     *
     * The ApplicationBuilder class coordinates the initialization and registration of various
     * components, such as measurement sources, data storage mechanisms, and peripheral drivers.
     * It does not create any objects by itself but relies on objects passed through the
     * IPlatformFactory interface.
     */
    class ApplicationBuilder : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs an ApplicationBuilder with a reference to an IPlatformFactory.
         *
         * @param factory Reference to a platform-specific factory that provides the necessary objects.
         */
        explicit ApplicationBuilder(IPlatformFactory &factory);

        /**
         * @brief Deleted default constructor to prevent instantiation without a platform factory.
         */
        ApplicationBuilder() = delete;

        /**
         * @brief Default destructor for ApplicationBuilder.
         */
        virtual ~ApplicationBuilder() = default;

        /**
         * @brief Deleted copy constructor to prevent copying of ApplicationBuilder.
         */
        ApplicationBuilder(const ApplicationBuilder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment of ApplicationBuilder.
         *
         * @return Reference to the ApplicationBuilder instance.
         */
        ApplicationBuilder &operator=(const ApplicationBuilder &) = delete;

        /**
         * @brief Initializes the components of the application.
         *
         * This method initializes the necessary components, such as measurement sources,
         * data stores, and the HMI (Human Machine Interface).
         *
         * @return true if the initialization was successful, false otherwise.
         */
        virtual bool initialize() override;

        /**
         * @brief Starts the application and its components.
         *
         * This method starts the operation of all application components.
         *
         * @return true if the components started successfully, false otherwise.
         */
        virtual bool start();

        /**
         * @brief Stops the application and its components.
         *
         * This method halts the operation of all application components.
         *
         * @return true if the components stopped successfully, false otherwise.
         */
        virtual bool stop();

        /**
         * @brief Ticks the application, providing periodic updates.
         *
         * This method is called periodically to update the application state.
         *
         * @return true if the tick operation was successful, false otherwise.
         */
        virtual bool tick();

    private:
        /** @brief Object responsible for building measurement sources. */
        MeasurementSourcesFactory sourceBuilder;

        /** @brief Object responsible for building measurement stores. */
        MeasurementStoresFactory storesBuilder;

        /** @brief Object responsible for storing measurement data. */
        MeasurementDataStore dataStore;

        /** @brief Object responsible for coordinating measurement sources and storage. */
        MeasurementCoordinator measurementCoordinator;

        HmiFactory hmiFactory;
    };
}

#endif // APPLICATIONBUILDER_H_