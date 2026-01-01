/**
 * @file WiFiMeasurementRecorder.hpp
 * @brief Defines the WiFiMeasurementRecorder class responsible for sending measurement data
 *        to an ESP module via UART, which then sends the data over WiFi.
 */

#ifndef WIFI_MEASUREMENT_RECORDER_HPP
#define WIFI_MEASUREMENT_RECORDER_HPP

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Inc/WiFiMeasurementSerializer.hpp"
#include "Device/Inc/CobsEncoder.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <array>
#include <cstdint>

namespace Device
{
    /**
     * @class WiFiMeasurementRecorder
     * @brief Responsible for sending data to an ESP module, which forwards it via WiFi.
     *
     * Despite its name, the WiFiMeasurementRecorder class uses UART to communicate with the ESP module.
     * The ESP module, in turn, sends the data over WiFi. The class handles the transmission of measurement
     * data via UART but does not handle the WiFi network name or password, which are managed by the ESP module.
     */
    class WiFiMeasurementRecorder final : public IMeasurementRecorder
    {
    public:
        /**
         * @brief Constructs a WiFiMeasurementRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver used to communicate with the ESP module.
         */
        explicit constexpr WiFiMeasurementRecorder(Driver::IUartDriver &driver) noexcept
            : driver{driver}
        {
        }

        ~WiFiMeasurementRecorder() override = default;

        WiFiMeasurementRecorder() = delete;
        WiFiMeasurementRecorder(const WiFiMeasurementRecorder &) = delete;
        WiFiMeasurementRecorder &operator=(const WiFiMeasurementRecorder &) = delete;
        WiFiMeasurementRecorder(WiFiMeasurementRecorder &&) = delete;
        WiFiMeasurementRecorder &operator=(WiFiMeasurementRecorder &&) = delete;

        [[nodiscard]] bool notify(const MeasurementType &measurement) noexcept override;

    protected:
        [[nodiscard]] bool onInitialize() noexcept override;
        [[nodiscard]] bool onStart() noexcept override;
        [[nodiscard]] bool onStop() noexcept override;
        [[nodiscard]] bool onReset() noexcept override;

    private:
        Driver::IUartDriver &driver;

        // Compile-time buffer size calculations
        static constexpr std::size_t MAX_SERIALIZED_SIZE{
            WiFiMeasurementSerializer::getMaxSerializedSize()};

        static constexpr std::size_t MAX_COBS_ENCODED_SIZE{
            CobsEncoder::getMaxEncodedSize(MAX_SERIALIZED_SIZE)};

        static constexpr std::uint32_t UART_TX_TIMEOUT_MS{1000};

        // Buffers with compile-time calculated sizes
        std::array<std::uint8_t, MAX_SERIALIZED_SIZE> serializedBuffer{};
        std::array<std::uint8_t, MAX_COBS_ENCODED_SIZE> cobsEncodedBuffer{};
    };

} // namespace Device

#endif // WIFI_MEASUREMENT_RECORDER_HPP