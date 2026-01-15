module;

#include <span>
#include <cstdint>

export module Driver.UartDriver;

import Driver.DriverComponent;
import Driver.UartDriverConcept;

import Driver.UartStatus;
import Driver.UartId;

export namespace Driver
{

    class UartDriver final : public DriverComponent
    {
    public:
        UartDriver() = delete;

        explicit UartDriver(Driver::UartId deviceId) noexcept;

        ~UartDriver() = default;

        // Non-copyable and non-movable
        UartDriver(const UartDriver &) = delete;
        UartDriver(UartDriver &&) = delete;
        UartDriver &operator=(const UartDriver &) = delete;
        UartDriver &operator=(UartDriver &&) = delete;

        // UART operations
        [[nodiscard]] UartStatus transmit(std::span<const std::uint8_t> data,
                                          std::uint32_t timeout) noexcept;

        [[nodiscard]] UartStatus receive(std::span<std::uint8_t> data,
                                         std::uint32_t timeout) noexcept;

        // Lifecycle methods
        [[nodiscard]] bool onInit() noexcept { return true; }
        [[nodiscard]] bool onStart() noexcept { return true; }
        [[nodiscard]] bool onStop() noexcept { return true; }

    private:
        Driver::UartId uartId;
    };

    static_assert(Driver::Concepts::UartDriverConcept<UartDriver>,
                  "UartDriver must satisfy the concept requirements");
}