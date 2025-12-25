/**
 * @file MeasurementStoresFactory.hpp
 * @brief Declares the MeasurementStoresFactory class responsible for constructing and managing measurement data stores.
 */

#ifndef MeasurementStoresFactory_h
#define MeasurementStoresFactory_h

#include "BusinessLogic/Interface/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Device/Inc/CacheMeasurementRecorder.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"

#include <cstdint>

namespace BusinessLogic
{
    /**
     * @class MeasurementStoresFactory
     * @brief Factory for creating and managing measurement data storage components.
     *
     * Constructs and initializes concrete measurement recorder implementations (WiFi, SD Card, Cache)
     * and registers them with the measurement coordinator. Implements the IApplicationComponentFactory
     * interface for integration into the application component initialization system.
     */
    class MeasurementStoresFactory : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs a MeasurementStoresFactory with required recorders and drivers.
         *
         * @param cacheRecorder Reference to a pre-constructed cache recorder instance
         * @param uartForWiFi Reference to UART driver for WiFi communication
         * @param sdCard Reference to SD card driver for storage operations
         */
        explicit MeasurementStoresFactory(
            Device::CacheMeasurementRecorder &cacheRecorder,
            Driver::IUartDriver &uartForWiFi,
            Driver::ISdCardDriver &sdCard);

        /**
         * @brief Default destructor.
         */
        ~MeasurementStoresFactory() override = default;

        /**
         * @brief Deleted copy constructor.
         */
        MeasurementStoresFactory(const MeasurementStoresFactory &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        MeasurementStoresFactory &operator=(const MeasurementStoresFactory &) = delete;

        /**
         * @brief Initializes all measurement recorder components.
         *
         * Calls initialize() on each managed recorder (WiFi, SD Card, Cache).
         *
         * @return Always returns true (initialization errors handled internally)
         */
        bool initialize() override;

        /**
         * @brief Registers all recorders with the measurement data store.
         *
         * Adds WiFi, SD Card, and Cache recorders as observers to the coordinator.
         *
         * @param coordinator Reference to the measurement data coordinator
         * @return true if all recorders registered successfully, false otherwise
         */
        bool registerStores(MeasurementDataStore &coordinator);

    private:
        /** @brief Reference to the cache measurement recorder */
        Device::CacheMeasurementRecorder &cacheRecorder;

        /** @brief WiFi measurement recorder instance */
        Device::WiFiMeasurementRecorder wifiRecorder;

        /** @brief SD card measurement recorder instance */
        Device::SdCardMeasurementRecorder sdCardRecorder;
    };
}

#endif // MeasurementStoresFactory_h
