/**
 * @file SdCardDriver.hpp
 * @brief Defines the SdCardDriver class for interacting with SD cards.
 */

#ifndef SDCARDDRIVER_H_
#define SDCARDDRIVER_H_

#include "Driver/Interfaces/ISdCardDriver.hpp"

namespace Driver
{
    /**
     * @class SdCardDriver
     * @brief Low-level driver for SD card operations.
     *
     * This class implements the `ISdCardDriver` interface to handle low-level
     * operations related to storing data on an SD card. This includes tasks like
     * mounting/unmounting the file system, opening/closing files, and writing data.
     *
     * Note: This class does not manage the content or metadata of the files. Its
     * primary concern is to provide low-level access to the SD card.
     */
    class SdCardDriver : public ISdCardDriver
    {
    public:
        /**
         * @brief Default constructor for SdCardDriver.
         */
        explicit SdCardDriver();

        /**
         * @brief Virtual destructor for SdCardDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~SdCardDriver() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        SdCardDriver(const SdCardDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return SdCardDriver& The assigned object.
         */
        SdCardDriver &operator=(const SdCardDriver &) = delete;

        /**
         * @brief Initializes the SD card driver.
         *
         * Prepares the SD card for use.
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the SD card driver.
         *
         * Begins the operation of the SD card for reading and writing.
         * @return True if the driver started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the SD card driver.
         *
         * Stops SD card operations.
         * @return True if the driver stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the SD card driver.
         *
         * Resets the SD card hardware and reinitializes the system if needed.
         * @return True if the driver reset successfully, false otherwise.
         */
        bool onReset() override;

        /**
         * @brief Mounts the file system on the SD card.
         *
         * This function initializes and mounts the file system to prepare for file operations.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void mountFileSystem() override;

        /**
         * @brief Unmounts the file system from the SD card.
         *
         * This function unmounts the file system, closing any open files and ensuring that
         * all data is properly written to the SD card.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void unmountFileSystem() override;

        /**
         * @brief Opens a file on the SD card.
         *
         * This function prepares a file for reading or writing.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void openFile() override;

        /**
         * @brief Closes a file on the SD card.
         *
         * This function finalizes file operations and ensures that all data is written.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void closeFile() override;

        /**
         * @brief Synchronizes the file system.
         *
         * This function ensures that all file operations are committed and no data is lost.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void sync() override;

        /**
         * @brief Writes data to a file on the SD card.
         *
         * This function writes data to the currently open file on the SD card.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void writeToFile() override;
    };

}

#endif // SDCARDDRIVER_H_