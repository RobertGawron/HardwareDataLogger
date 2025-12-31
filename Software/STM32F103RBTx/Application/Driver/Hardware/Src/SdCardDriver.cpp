#include "Driver/Hardware/Inc/SdCardDriver.hpp"

namespace Driver
{
    // Ensure size types are compatible
    static_assert(sizeof(std::uint16_t) <= sizeof(UINT),
                  "std::uint16_t must not be larger than UINT for safe conversion in f_write()");

    SdCardDriver::~SdCardDriver()
    {
        if (isFileOpen)
        {
            closeFile();
        }
    }

    bool SdCardDriver::onInitialize()
    {
        // not possible to get status from HAL methods, all are void
        const bool status = true;

        GPIO_InitTypeDef GPIO_InitStruct = {0};

        /* 1. Enable GPIO Clocks */
        __HAL_RCC_GPIOA_CLK_ENABLE(); // For SCK, MISO, MOSI
        __HAL_RCC_GPIOB_CLK_ENABLE(); // For CS

        /* 2. Free PB4 from JTAG (CRITICAL!) */
        __HAL_AFIO_REMAP_SWJ_NOJTAG(); // Disable JTAG, keep SWD

        /* 3. Configure SPI Pins */
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
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); // Set CS high

        HAL_Delay(POWER_UP_DELAY_MS);

        return status;
    }

    bool SdCardDriver::onStart()
    {
        // Mount the filesystem
        const FRESULT libStatus = f_mount(&fileSystem, SD_CARD_VOLUME, MOUNT_NOW_FLAG);

        if (libStatus == FR_OK)
        {
            isFileSystemMounted = true;
        }

        return (libStatus == FR_OK);
    }

    bool SdCardDriver::onStop()
    {
        bool status = true;

        // Close any open file before unmounting
        if (isFileOpen)
        {
            const SdCardStatus closeStatus = closeFile();
            if (closeStatus != SdCardStatus::OK)
            {
                status = false;
            }
        }

        // Unmount the filesystem
        // the library is made in a way that passing empty string is unmounting volume
        // it's a third party lib, that's how it is
        static constexpr const char *SD_CARD_UNMOUNT_VOLUME = "";

        const FRESULT libStatus = f_mount(0, SD_CARD_UNMOUNT_VOLUME, MOUNT_NOW_FLAG);

        if (libStatus != FR_OK)
        {
            status = false;
        }
        else
        {
            isFileSystemMounted = false;
        }

        return status;
    }

    bool SdCardDriver::onReset()
    {
        const bool status = true;
        return status;
    }

    SdCardStatus SdCardDriver::openFile(std::string_view filename, FileOpenMode mode)
    {
        SdCardStatus status = SdCardStatus::OK;

        if (filename.empty())
        {
            status = SdCardStatus::INVALID_PARAMETER;
        }
        else if (!isFileSystemMounted)
        {
            status = SdCardStatus::FILESYSTEM_NOT_MOUNTED;
        }
        else if (isFileOpen)
        {
            status = SdCardStatus::FILE_ALREADY_OPEN;
        }
        else
        {
            BYTE fatFsMode;

            if (mode == FileOpenMode::OVERWRITE)
            {
                fatFsMode = FA_WRITE | FA_CREATE_ALWAYS;
            }
            else // FileOpenMode::APPEND
            {
                fatFsMode = FA_WRITE | FA_OPEN_ALWAYS;
            }

            // FatFs requires null-terminated string
            FRESULT result = f_open(&file, filename.data(), fatFsMode);

            if (result != FR_OK)
            {
                status = SdCardStatus::FILE_OPEN_ERROR;
            }
            else
            {
                // For append mode, seek to end of file
                if (mode == FileOpenMode::APPEND)
                {
                    result = f_lseek(&file, f_size(&file));
                    if (result != FR_OK)
                    {
                        f_close(&file);
                        isFileOpen = false;
                        status = SdCardStatus::FILE_OPEN_ERROR;
                    }
                    else
                    {
                        isFileOpen = true;
                    }
                }
                else
                {
                    isFileOpen = true;
                }
            }
        }

        return status;
    }

    SdCardStatus SdCardDriver::closeFile()
    {
        SdCardStatus status = SdCardStatus::OK;

        if (!isFileOpen)
        {
            status = SdCardStatus::NO_FILE_OPEN;
        }
        else
        {
            FRESULT result = f_close(&file);

            if (result != FR_OK)
            {
                status = SdCardStatus::FILE_CLOSE_ERROR;
            }
            else
            {
                isFileOpen = false;
            }
        }

        return status;
    }

    SdCardStatus SdCardDriver::write(std::span<const std::uint8_t> data)
    {
        // Empty check is automatic - span knows its size!
        if (data.empty())
        {
            return SdCardStatus::INVALID_PARAMETER;
        }

        if (!isFileSystemMounted)
        {
            return SdCardStatus::FILESYSTEM_NOT_MOUNTED;
        }

        if (!isFileOpen)
        {
            return SdCardStatus::NO_FILE_OPEN;
        }

        UINT bytesWritten = 0;

        // span.data() and span.size() replace your pointer + size
        FRESULT result = f_write(&file, data.data(), data.size(), &bytesWritten);

        if (result != FR_OK)
        {
            return SdCardStatus::WRITE_ERROR;
        }

        if (bytesWritten != data.size())
        {
            return SdCardStatus::INCOMPLETE_WRITE;
        }

        // Ensure data is physically written to the SD card
        result = f_sync(&file);
        if (result != FR_OK)
        {
            return SdCardStatus::SYNC_ERROR;
        }

        return SdCardStatus::OK;
    }

}