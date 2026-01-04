#pragma once

#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/UartStatus.hpp"
#include <concepts>
#include <span>
#include <cstdint>

namespace Driver::Concepts
{
    /**
     * @concept UartDriver
     * @brief Defines requirements for UART communication drivers
     */
    template <typename T>
    concept UartDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver,
                 std::span<const std::uint8_t> txData,
                 std::span<std::uint8_t> rxData,
                 std::uint32_t timeout) {
            { driver.transmit(txData, timeout) } noexcept -> std::same_as<UartStatus>;
            { driver.receive(rxData, timeout) } noexcept -> std::same_as<UartStatus>;
        };
}