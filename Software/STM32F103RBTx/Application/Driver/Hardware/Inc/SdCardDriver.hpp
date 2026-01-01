/**
 * @file SdCardDriver.hpp
 * @brief Defines the SdCardDriver class for interacting with SD cards.
 */

#ifndef SDCARDDRIVER_H_
#define SDCARDDRIVER_H_

#include "Driver/Interface/ISdCardDriver.hpp"
#include "Driver/Interface/SdCardStatus.hpp"

#include "ff.h"
#include <string_view>
#include <span>

namespace Driver
{
    /**
     * @class SdCardDriver
     * @brief Low-level driver for SD card operations using FatFs filesystem.
     *
     * This class implements the ISdCardDriver interface to provide low-level
     * SD card operations including filesystem mounting, file management, and
     * data writing capabilities.
     *
     * The driver manages the complete lifecycle of SD card operations:
     * - Hardware initialization (GPIO, SPI configuration)
     * - Filesystem mounting and unmounting
     * - File opening (with overwrite or append modes)
     * - Data writing with synchronization
     * - Proper cleanup and resource management
     *
     * @note This class is NOT thread-safe and must be used sequentially from
     *       a single thread or with external synchronization.
     * @note Only one file can be open at a time.
     * @note The filesystem must be mounted before any file operations.
     *
     * @warning Destroying the driver while a file is open will automatically
     *          close the file, but proper shutdown via onStop() is recommended.
     */
    // destructor calls virtual method
    class SdCardDriver final : public ISdCardDriver
    {
    public:
        /**
         * @brief Default constructor for SdCardDriver.
         *
         * Initializes the driver in a non-operational state. onInitialize()
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
        ~SdCardDriver() override;

        /**
         * @brief Deleted copy constructor to prevent copying.
         *
         * SdCardDriver manages hardware resources and cannot be safely copied.
         */
        SdCardDriver(const SdCardDriver &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent assignment.
         *
         * SdCardDriver manages hardware resources and cannot be safely copied.
         */
        SdCardDriver &operator=(const SdCardDriver &) = delete;

        /**
         * @brief Initializes the SD card hardware.
         *
         * Configures GPIO pins for SPI communication:
         * - PA5: SPI SCK (clock)
         * - PA6: SPI MISO (data in)
         * - PA7: SPI MOSI (data out)
         * - PB4: CS (chip select)
         *
         * This method also disables JTAG on PB4 and waits for the SD card
         * to power up and stabilize (10ms delay).
         *
         * @return Always returns true (HAL functions don't report errors).
         *
         * @note This must be called before onStart().
         * @note This method does not mount the filesystem.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the SD card driver by mounting the filesystem.
         *
         * Mounts the FatFs filesystem on the SD card, making it ready for
         * file operations. The filesystem is mounted immediately (not deferred).
         *
         * @return True if filesystem was mounted successfully, false otherwise.
         *
         * @pre onInitialize() must have been called successfully.
         * @post If successful, filesystem is mounted and file operations are available.
         *
         * @note After this call succeeds, openFile() can be used.
         */
        bool onStart() override;

        /**
         * @brief Stops the SD card driver by unmounting the filesystem.
         *
         * Closes any open file and unmounts the FatFs filesystem. After this
         * call, no file operations can be performed until onStart() is called again.
         *
         * @return True if all operations (close file + unmount) succeeded,
         *         false if any operation failed.
         *
         * @post Filesystem is unmounted and no files are open.
         * @post isFileSystemMounted and isFileOpen flags are set to false.
         *
         * @note If a file is open, it will be closed first.
         * @note This should be called before destroying the driver.
         */
        bool onStop() override;

        /**
         * @brief Resets the SD card driver.
         *
         * Currently a no-op placeholder that always succeeds. No actual
         * reset operation is performed.
         *
         * @return Always returns true.
         *
         * @note This method is provided for interface compliance but does
         *       not perform any reset operations.
         */
        bool onReset() override;

        /**
         * @brief Opens a file on the SD card.
         *
         * Opens the specified file in either overwrite or append mode.
         * Only one file can be open at a time.
         *
         * @param filename Name of the file to open (null-terminated string view).
         *                 Must not be empty.
         * @param mode FileOpenMode::OVERWRITE to create/truncate the file,
         *             or FileOpenMode::APPEND to append to existing file.
         *
         * @return SdCardStatus::OK if file opened successfully.
         * @return SdCardStatus::INVALID_PARAMETER if filename is empty.
         * @return SdCardStatus::FILESYSTEM_NOT_MOUNTED if filesystem not mounted.
         * @return SdCardStatus::FILE_ALREADY_OPEN if another file is already open.
         * @return SdCardStatus::FILE_OPEN_ERROR if FatFs open/seek operation failed.
         *
         * @pre Filesystem must be mounted (onStart() called successfully).
         * @pre No other file must be open.
         * @post If successful, file is open and ready for writing.
         *
         * @note In APPEND mode, the file pointer is automatically positioned
         *       at the end of the file.
         * @note The filename must remain valid only for the duration of this call.
         */
        SdCardStatus openFile(std::string_view filename, FileOpenMode mode) override;

        /**
         * @brief Writes data to the currently open file.
         *
         * Writes the provided data to the file and syncs to ensure it's
         * physically written to the SD card.
         *
         * @param data Span of bytes to write. Must not be empty.
         *
         * @return SdCardStatus::OK if all data written and synced successfully.
         * @return SdCardStatus::INVALID_PARAMETER if data is empty.
         * @return SdCardStatus::FILESYSTEM_NOT_MOUNTED if filesystem not mounted.
         * @return SdCardStatus::NO_FILE_OPEN if no file is currently open.
         * @return SdCardStatus::WRITE_ERROR if FatFs write operation failed.
         * @return SdCardStatus::INCOMPLETE_WRITE if not all bytes were written.
         * @return SdCardStatus::SYNC_ERROR if sync operation failed.
         *
         * @pre Filesystem must be mounted.
         * @pre A file must be open (via openFile()).
         * @post If successful, data is written and synced to SD card.
         *
         * @note This method ensures data persistence by calling f_sync().
         * @note The write is atomic - either all data is written or an error is returned.
         */
        SdCardStatus write(std::span<const std::uint8_t> data) override;

        /**
         * @brief Closes the currently open file.
         *
         * Closes the file handle and marks no file as open.
         *
         * @return SdCardStatus::OK if file closed successfully.
         * @return SdCardStatus::NO_FILE_OPEN if no file is currently open.
         * @return SdCardStatus::FILE_CLOSE_ERROR if FatFs close operation failed.
         *
         * @pre A file must be open.
         * @post File is closed and isFileOpen flag is set to false.
         *
         * @note After closing, another file can be opened with openFile().
         */
        SdCardStatus closeFile() override;

    private:
        /// FatFs filesystem object for managing the SD card filesystem
        FATFS fileSystem;

        /// FatFs file object for the currently open file
        FIL file;

        /// Tracks whether the filesystem is currently mounted
        bool isFileSystemMounted = false;

        /// Tracks whether a file is currently open
        bool isFileOpen = false;

        /// SD card volume identifier for FatFs (logical drive number)
        static constexpr const char *SD_CARD_VOLUME = "0:";

        /// Flag to mount filesystem immediately (not deferred)
        static constexpr uint8_t MOUNT_NOW_FLAG = 1;

        /// Power-up delay in milliseconds for SD card stabilization
        /// SD cards need time to power up and stabilize (typically 1-10ms)
        static constexpr uint32_t POWER_UP_DELAY_MS = 10;
    };
}

#endif // SDCARDDRIVER_H_
