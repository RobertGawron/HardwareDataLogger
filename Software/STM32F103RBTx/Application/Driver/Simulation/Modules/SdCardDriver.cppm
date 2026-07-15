module;

#include <string_view>
#include <span>
#include <cstdint>

export module Driver.SdCardDriver;

import Driver.DriverComponent;
import Driver.SdCardDriverConcept;
import Driver.SdCardStatus;
import Driver.FileOpenMode;

export namespace Driver
{
    class SdCardDriver : public DriverComponent
    {
    public:
        /**
         * @brief Default constructor for SdCardDriver.
         *
         * Initializes the driver in a non-operational state. onInit()
         * and onStart() must be called before using file operations.
         */
        explicit SdCardDriver() = default;

        /**
         * @brief Virtual destructor for SdCardDriver.
         *
         * Automatically closes any open file before destruction to prevent
         * resource leaks. However, it does not unmount the filesystem.
         *
         * @note For proper cleanup, call onStop() before destruction.
         */
        ~SdCardDriver() = default;

        // Non-copyable and non-movable
        SdCardDriver(const SdCardDriver &) = delete;
        SdCardDriver(SdCardDriver &&) = delete;
        SdCardDriver &operator=(const SdCardDriver &) = delete;
        SdCardDriver &operator=(SdCardDriver &&) = delete;

        [[nodiscard]] auto onInit() noexcept -> bool;
        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;
        [[nodiscard]] auto onReset() noexcept -> bool;

        [[nodiscard]] auto openFile(std::string_view filename, FileOpenMode mode) noexcept -> SdCardStatus;
        [[nodiscard]] auto write(std::span<const std::uint8_t> data) noexcept -> SdCardStatus;
        [[nodiscard]] auto closeFile() noexcept -> SdCardStatus;
    };

    static_assert(Driver::Concepts::SdCardDriverConcept<SdCardDriver>,
                  "SdCardDriverConcept must satisfy the concept requirements");
}