/**
 * @file WiFiRecorder.cppm
 * @brief Defines the WiFiRecorder class responsible for sending measurement data
 *        to an ESP module via UART, which then sends the data over WiFi.
 */
module;

#include <array>
#include <cstdint>

export module Device.WiFiRecorder;

import Device.DeviceComponent;
import Device.MeasurementRecorder;
import Device.WiFiSerializer;
import Device.MeasurementType;
import Device.CobsEncoder;

import Driver.UartDriver;

export namespace Device
{
    /**
     * @class WiFiRecorder
     * @brief Responsible for sending data to an ESP module, which forwards it via WiFi.
     *
     * Despite its name, the WiFiRecorder class uses UART to communicate with the ESP module.
     * The ESP module, in turn, sends the data over WiFi. The class handles the transmission of measurement
     * data via UART but does not handle the WiFi network name or password, which are managed by the ESP module.
     */
    class WiFiRecorder final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a WiFiRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver used to communicate with the ESP module.
         */
        explicit constexpr WiFiRecorder(Driver::UartDriver &driver) noexcept : driver{driver} {}

        ~WiFiRecorder() = default;

        WiFiRecorder() = delete;
        WiFiRecorder(const WiFiRecorder &) = delete;
        WiFiRecorder &operator=(const WiFiRecorder &) = delete;
        WiFiRecorder(WiFiRecorder &&) = delete;
        WiFiRecorder &operator=(WiFiRecorder &&) = delete;

        [[nodiscard]] auto notify(const MeasurementType &measurement) noexcept -> bool;

        [[nodiscard]] auto onInit() noexcept -> bool;

        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;

    private:
        Driver::UartDriver &driver;

        // Compile-time buffer size calculations
        static constexpr std::size_t MAX_SERIALIZED_SIZE{
            WiFiSerializer::getMaxSerializedSize()};

        static constexpr std::size_t MAX_COBS_ENCODED_SIZE{
            CobsEncoder::getMaxEncodedSize(MAX_SERIALIZED_SIZE)};

        static constexpr std::uint32_t UART_TX_TIMEOUT_MS{1000};

        // Buffers with compile-time calculated sizes
        std::array<std::uint8_t, MAX_SERIALIZED_SIZE> serializedBuffer{};
        std::array<std::uint8_t, MAX_COBS_ENCODED_SIZE> cobsEncodedBuffer{};
    };

    // Compile-time verification
    static_assert(MeasurementRecorder<WiFiRecorder>,
                  "WiFiRecorder must satisfy MeasurementRecorder concept");

} // namespace Device