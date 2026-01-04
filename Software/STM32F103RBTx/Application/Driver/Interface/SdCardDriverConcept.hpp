#pragma once

#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/SdCardStatus.hpp"
#include "Driver/Interface/FileOpenMode.hpp"

#include <concepts>
#include <span>
#include <string_view>
#include <cstdint>

namespace Driver::Concepts
{
    /**
     * @concept SdCardDriverConcept
     * @brief Defines requirements for SD card storage drivers
     */
    template <typename T>
    concept SdCardDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver,
                 std::string_view filename,
                 FileOpenMode mode,
                 std::span<const std::uint8_t> data) {
            // File operations
            { driver.openFile(filename, mode) } noexcept -> std::same_as<SdCardStatus>;
            { driver.write(data) } noexcept -> std::same_as<SdCardStatus>;
            { driver.closeFile() } noexcept -> std::same_as<SdCardStatus>;
        };
}