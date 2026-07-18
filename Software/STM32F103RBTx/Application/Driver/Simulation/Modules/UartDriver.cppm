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
        [[nodiscard]] auto transmit(std::span<const std::uint8_t> data,
                                    std::uint32_t timeout) noexcept -> UartStatus;

        [[nodiscard]] auto receive(std::span<std::uint8_t> data,
                                   std::uint32_t timeout) noexcept -> UartStatus;

        // Lifecycle methods
        [[nodiscard]] auto onInit() noexcept -> bool { return true; }
        [[nodiscard]] auto onStart() noexcept -> bool { return true; }
        [[nodiscard]] auto onStop() noexcept -> bool { return true; }

    private:
        Driver::UartId uartId;
    };

    static_assert(Driver::Concepts::UartDriverConcept<UartDriver>,
                  "UartDriver must satisfy the concept requirements");
}