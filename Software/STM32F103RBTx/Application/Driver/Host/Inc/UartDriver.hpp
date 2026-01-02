/**
 * @file UartDriver.hpp
 * @brief Defines the UartDriver class for UART communication using STM32 HAL.
 */

#ifndef UartDriver_h
#define UartDriver_h

#include "Driver/Interface/UartDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/UartStatus.hpp"
#include "Driver/Interface/UartId.hpp"

#include <span>
#include <cstdint>

namespace Driver
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

#endif // UartDriver_h