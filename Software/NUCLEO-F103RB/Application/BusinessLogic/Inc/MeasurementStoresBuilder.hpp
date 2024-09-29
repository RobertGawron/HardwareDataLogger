/**
 * @file MeasurementStoresBuilder.hpp
 * @brief Declares the MeasurementStoresBuilder class responsible for constructing and managing measurement data stores.
 */

#ifndef MeasurementStoresBuilder_h
#define MeasurementStoresBuilder_h

#include <stdint.h>
#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"

// Driver
#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Interfaces/ISdCardDriver.hpp"
// Device
#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/SdCardMeasurementRecorder.hpp"
// High-level components
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"

#include "BusinessLogic/Interfaces/IApplicationComponentBuilder.hpp"
#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementRecorder.hpp"
namespace BusinessLogic
{
    class MeasurementDataStore;
}
namespace Driver
{
    class ISdCardDriver;
}
namespace Driver
{
    class IUartDriver;
}

namespace BusinessLogic
{
    /**
     * @class MeasurementStoresBuilder
     * @brief Responsible for building and managing measurement data stores.
     *
     * The MeasurementStoresBuilder class constructs and manages components related to storing measurement data.
     * It requires drivers for the UART and SD card interfaces and constructs other components by itself.
     * This class is configurable based on the platform, whether it's running on firmware or in a simulation.
     */
    class MeasurementStoresBuilder : public IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Constructs the MeasurementStoresBuilder with platform-specific drivers.
         *
         * This constructor requires a UART driver for WiFi communication and an SD card driver to handle data storage.
         * The class constructs the measurement recorders and other components by itself.
         *
         * @param uartForWiFi Reference to the UART driver used for WiFi communication.
         * @param sdCard Reference to the SD card driver used for data storage.
         */
        explicit MeasurementStoresBuilder(
            Driver::IUartDriver &uartForWiFi,
            Driver::ISdCardDriver &sdCard);

        /**
         * @brief Default destructor.
         */
        virtual ~MeasurementStoresBuilder() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementStoresBuilder(const MeasurementStoresBuilder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementStoresBuilder& The assigned object.
         */
        MeasurementStoresBuilder &operator=(const MeasurementStoresBuilder &) = delete;

        /**
         * @brief Initializes the measurement data stores.
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() override;

        /**
         * @brief Starts the measurement data stores.
         * @return true if the components started successfully, false otherwise.
         */
        virtual bool start() override;

        /**
         * @brief Stops the measurement data stores.
         * @return true if the components stopped successfully, false otherwise.
         */
        virtual bool stop() override;

        /**
         * @brief Ticks the measurement data stores for periodic updates.
         * @return true if the tick operation was successful, false otherwise.
         */
        virtual bool tick() override;

        /**
         * @brief Registers the measurement data stores with a data coordinator.
         *
         * This function registers the WiFi and SD card measurement recorders with the provided
         * MeasurementDataStore coordinator.
         *
         * @param coordinator Reference to the MeasurementDataStore coordinator.
         * @return true if the stores were successfully registered, false otherwise.
         */
        virtual bool registerStores(MeasurementDataStore &coordinator);

    private:
        /** @brief WiFi measurement recorder used for storing measurements via WiFi. */
        Device::WiFiMeasurementRecorder wifiRecorder;

        /** @brief SD card measurement recorder used for storing measurements on an SD card. */
        Device::SdCardMeasurementRecorder sdCardRecorder;
    };
}

#endif // MeasurementStoresBuilder_h