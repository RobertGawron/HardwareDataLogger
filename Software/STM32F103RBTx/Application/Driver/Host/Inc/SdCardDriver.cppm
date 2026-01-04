/**
 * @file SdCardDriver.hpp
 * @brief Defines the SdCardDriver class for interacting with SD cards.
 */

#ifndef SdCardDriver_H_
#define SdCardDriver_H_

#include "Driver/Interface/SdCardDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/SdCardStatus.hpp"
#include "Driver/Interface/FileOpenMode.hpp"

#include <string_view>
#include <span>
#include <cstdint>

namespace Driver
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
        [[nodiscard]] bool onInit() noexcept;

        /**
         * @brief Starts the SD card driver by mounting the filesystem.
         *
         * Mounts the FatFs filesystem on the SD card, making it ready for
         * file operations. The filesystem is mounted immediately (not deferred).
         *
         * @return True if filesystem was mounted successfully, false otherwise.
         *
         * @pre onInit() must have been called successfully.
         * @post If successful, filesystem is mounted and file operations are available.
         *
         * @note After this call succeeds, openFile() can be used.
         */
        [[nodiscard]] bool onStart() noexcept;

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
        [[nodiscard]] bool onStop() noexcept;

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
        [[nodiscard]] bool onReset() noexcept;

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
        SdCardStatus openFile(std::string_view filename, FileOpenMode mode) noexcept;

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
        SdCardStatus write(std::span<const std::uint8_t> data) noexcept;

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
        SdCardStatus closeFile() noexcept;
    };

    static_assert(Driver::Concepts::SdCardDriverConcept<SdCardDriver>,
                  "SdCardDriverConcept must satisfy the concept requirements");
}

#endif // SdCardDriver_H_
