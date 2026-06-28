module;

#include "ff.h"

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
    /**
     * @class SdCardDriver
     * @brief Hardware driver for SD card operations via SPI and FatFs
     *
     * Manages complete SD card lifecycle: initialization, filesystem mounting,
     * file operations, and cleanup. Only one file open at a time.
     *
     * @note NOT thread-safe - use from single thread or with external sync
     * @warning Destructor auto-closes open files, but prefer explicit onStop()
     */
    class SdCardDriver final : public DriverComponent
    {
    public:
        SdCardDriver() = default;
        ~SdCardDriver();

        SdCardDriver(const SdCardDriver &) = delete;
        SdCardDriver &operator=(const SdCardDriver &) = delete;
        SdCardDriver(SdCardDriver &&) = delete;
        SdCardDriver &operator=(SdCardDriver &&) = delete;

        [[nodiscard]] SdCardStatus openFile(std::string_view filename,
                                            FileOpenMode mode) noexcept;
        [[nodiscard]] SdCardStatus write(std::span<const std::uint8_t> data) noexcept;
        [[nodiscard]] SdCardStatus closeFile() noexcept;

        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept;
        [[nodiscard]] bool onStop() noexcept;

    private:
        // Hardware configuration constants
        static constexpr std::uint32_t POWER_UP_DELAY_MS = 10U;
        static constexpr std::uint8_t MOUNT_NOW_FLAG = 1U;
        static constexpr const char *SD_CARD_VOLUME = "0:";
        static constexpr const char *SD_CARD_UNMOUNT_VOLUME = "";

        FATFS fileSystem{};
        FIL file{};
        bool isFileSystemMounted{false};
        bool isFileOpen{false};
    };

    static_assert(Driver::Concepts::SdCardDriverConcept<SdCardDriver>,
                  "SdCardDriverConcept must satisfy the concept requirements");

} // namespace Driver