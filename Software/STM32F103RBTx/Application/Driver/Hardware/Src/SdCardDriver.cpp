module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "ff.h"
#include "diskio.h"

#include <string_view>
#include <cstdint>
#include <cstring>

module Driver.SdCardDriver;

namespace Driver
{
    static_assert(sizeof(std::uint16_t) <= sizeof(UINT),
                  "std::uint16_t must not exceed UINT size for f_write()");

    SdCardDriver::~SdCardDriver()
    {
        if (isFileOpen)
        {
            closeFile();
        }
    }

    bool SdCardDriver::onInit() noexcept
    {
        GPIO_InitTypeDef GPIO_InitStruct{};

        // Enable GPIO clocks
        __HAL_RCC_GPIOA_CLK_ENABLE(); // SCK, MISO, MOSI
        __HAL_RCC_GPIOB_CLK_ENABLE(); // CS

        // Free PB4 from JTAG (CRITICAL for CS pin!)
        __HAL_AFIO_REMAP_SWJ_NOJTAG(); // Disable JTAG, keep SWD

        // Configure SPI pins
        // SCK (PA5) - Alternate Function Push-Pull
        GPIO_InitStruct.Pin = GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // MOSI (PA7) - Alternate Function Push-Pull
        GPIO_InitStruct.Pin = GPIO_PIN_7;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // MISO (PA6) - Input with Pull-up
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // CS (PB4) - Output Push-Pull (High = Inactive)
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); // CS high (inactive)

        HAL_Delay(POWER_UP_DELAY_MS);

        return true;
    }

    bool SdCardDriver::onStart() noexcept
    {
        const FRESULT result = f_mount(&fileSystem, SD_CARD_VOLUME, MOUNT_NOW_FLAG);

        isFileSystemMounted = (result == FR_OK);
        const auto status = isFileSystemMounted;

        return status;
    }

    bool SdCardDriver::onStop() noexcept
    {
        bool status = true;

        // Close any open file before unmounting
        if (isFileOpen)
        {
            if (closeFile() != SdCardStatus::OK)
            {
                status = false;
            }
        }

        // Unmount filesystem (empty string unmounts)
        const auto result = f_mount(nullptr, SD_CARD_UNMOUNT_VOLUME, MOUNT_NOW_FLAG);

        if (result != FR_OK)
        {
            status = false;
        }
        else
        {
            isFileSystemMounted = false;
        }

        return status;
    }

    SdCardStatus SdCardDriver::openFile(std::string_view filename,
                                        FileOpenMode mode) noexcept
    {
        if (filename.empty()) [[unlikely]]
        {
            return SdCardStatus::INVALID_PARAMETER;
        }

        if (!isFileSystemMounted) [[unlikely]]
        {
            return SdCardStatus::FILESYSTEM_NOT_MOUNTED;
        }

        if (isFileOpen) [[unlikely]]
        {
            return SdCardStatus::FILE_ALREADY_OPEN;
        }

        // FatFs requires a null-terminated C-string.
        // std::string_view is NOT guaranteed to be null-terminated.
        // We use a stack buffer to avoid dynamic allocation.
        // (FF_MAX_LFN is typically 255 in FatFs, so 256 is a safe bound).
        static constexpr std::size_t MAX_PATH_LEN = 256U;

        if (filename.size() >= MAX_PATH_LEN) [[unlikely]]
        {
            return SdCardStatus::INVALID_PARAMETER; // Prevents buffer overflow
        }

        char pathBuffer[MAX_PATH_LEN];
        std::memcpy(pathBuffer, filename.data(), filename.size());
        pathBuffer[filename.size()] = '\0'; // Null-terminate for FatFs

        const BYTE fatFsMode = (mode == FileOpenMode::OVERWRITE)
                                   ? (FA_WRITE | FA_CREATE_ALWAYS)
                                   : (FA_WRITE | FA_OPEN_ALWAYS);

        auto result = f_open(&file, pathBuffer, fatFsMode);

        if (result != FR_OK)
        {
            return SdCardStatus::FILE_OPEN_ERROR;
        }

        // For append mode, seek to end of file
        if (mode == FileOpenMode::APPEND)
        {
            result = f_lseek(&file, f_size(&file));
            if (result != FR_OK)
            {
                f_close(&file);
                return SdCardStatus::FILE_OPEN_ERROR;
            }
        }

        isFileOpen = true;
        return SdCardStatus::OK;
    }

    SdCardStatus SdCardDriver::closeFile() noexcept
    {
        if (!isFileOpen) [[unlikely]]
        {
            return SdCardStatus::NO_FILE_OPEN;
        }

        const auto result = f_close(&file);

        if (result != FR_OK)
        {
            return SdCardStatus::FILE_CLOSE_ERROR;
        }

        isFileOpen = false;
        return SdCardStatus::OK;
    }

    SdCardStatus SdCardDriver::write(std::string_view data) noexcept
    {
        if (data.empty()) [[unlikely]]
        {
            return SdCardStatus::INVALID_PARAMETER;
        }

        if (!isFileSystemMounted) [[unlikely]]
        {
            return SdCardStatus::FILESYSTEM_NOT_MOUNTED;
        }

        if (!isFileOpen) [[unlikely]]
        {
            return SdCardStatus::NO_FILE_OPEN;
        }

        UINT bytesWritten = 0U;

        // f_write expects const void*. data.data() returns const char*,
        // which implicitly and safely converts to const void*.
        const UINT sizeToWrite = static_cast<UINT>(data.size());
        auto result = f_write(&file, data.data(), sizeToWrite, &bytesWritten);

        if (result != FR_OK)
        {
            return SdCardStatus::WRITE_ERROR;
        }

        if (bytesWritten != sizeToWrite)
        {
            return SdCardStatus::INCOMPLETE_WRITE;
        }

        // Ensure data is physically written to SD card
        result = f_sync(&file);
        if (result != FR_OK)
        {
            return SdCardStatus::SYNC_ERROR;
        }

        return SdCardStatus::OK;
    }

} // namespace Driver