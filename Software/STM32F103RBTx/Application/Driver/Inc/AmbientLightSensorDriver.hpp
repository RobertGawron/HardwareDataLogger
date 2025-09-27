#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"
#include "stm32f1xx_hal.h"

#include <cstdint>
#include <cstddef>


namespace Driver
{
    /**
     * @class AmbientLightSensorDriver
     * @brief Provides functionality to interact with an ambient light sensor using ADC and DMA.
     *
     * This class interfaces with an ADC connected to a voltage divider circuit containing
     * a phototransistor. Light level readings depend on the photoelement sensor characteristics
     * and resistor values chosen experimentally. The driver uses DMA for efficient data acquisition
     * to minimize CPU load during continuous light level monitoring.
     */
    class AmbientLightSensorDriver : public IAmbientLightSensorDriver
    {
    public:
        /**
         * @brief Constructs an AmbientLightSensorDriver with an ADC handle.
         * @param hadc Reference to the STM32 HAL ADC handle.
         */
        explicit AmbientLightSensorDriver(ADC_HandleTypeDef &hadc);

        AmbientLightSensorDriver() = default; ///< Default constructor.

        /**
         * @brief Destructor for AmbientLightSensorDriver.
         */
        ~AmbientLightSensorDriver() override = default;

        AmbientLightSensorDriver(const AmbientLightSensorDriver &) = delete; ///< Deleted copy constructor prevents copying.
        AmbientLightSensorDriver &operator=(const AmbientLightSensorDriver &) = delete; ///< Deleted assignment operator prevents assignment.

        /**
         * @brief Retrieves the current ambient light level.
         *
         * This method returns the current ambient light level measured by the sensor.
         * The value range depends on hardware configuration and sensor characteristics.
         * @return std::uint16_t The current ambient light level.
         */
        [[nodiscard]] std::uint16_t getAmbientLightLevel() const override;

    protected:
        /**
         * @brief Initializes the Ambient Light Sensor Driver.
         *
         * Configures ADC and DMA but doesn't start conversions. Called during driver initialization.
         * @return true if initialization succeeds, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts ADC conversions and DMA transfers.
         *
         * Begins continuous ambient light measurements. Called when driver starts.
         * @return true if ADC/DMA start successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops ADC conversions and DMA transfers.
         *
         * Halts light measurements. Called when driver stops.
         * @return true if ADC/DMA stop successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the driver to initial state.
         *
         * Stops any ongoing operations and resets hardware. Called during driver reset.
         * @return true if reset succeeds, false otherwise.
         */
        bool onReset() override;

        /**
         * @brief Configures and starts ADC conversion with DMA.
         *
         * Enables efficient data transfer without CPU involvement.
         * @return true if ADC/DMA start successfully, false otherwise.
         */
        bool startAdcWithDma();

        /**
         * @brief Stops ADC conversion and DMA transfers.
         *
         * Halts all data acquisition. Typically called before shutdown or reset.
         * @return true if ADC/DMA stop successfully, false otherwise.
         */
        bool stopAdcWithDma();

    private:
        /** 
         * @brief Reference to STM32 HAL ADC handle.
         *
         * Used to configure and control the ADC peripheral.
         */
        ADC_HandleTypeDef &hadc;

        /**
 * @brief Size of the ADC buffer for light level measurements.
 */
static constexpr std::size_t AdcBufferSize = 10;

/**
 * @brief Buffer storing raw ADC values for ambient light measurements.
 */
 std::uint16_t adcBuffer[AdcBufferSize];
    };

}

#endif // AMBIENTLIGHTSENSORDRIVER_H_
