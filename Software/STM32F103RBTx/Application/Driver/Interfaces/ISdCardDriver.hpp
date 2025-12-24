#ifndef ISdCardDriver_H_
#define ISdCardDriver_H_

#include "Driver/Interfaces/DriverState.hpp"

namespace Driver
{
    /**
     * @class ISdCardDriver
     * @brief Interface for SD card drivers.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any SD card driver. It is designed to handle operations related to storing
     * measurement data on an SD card.
     */
    class ISdCardDriver : public DriverState
    {
    public:
        /**
         * @brief Default constructor for ISdCardDriver.
         */
        ISdCardDriver() = default;

        /**
         * @brief Virtual destructor for ISdCardDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~ISdCardDriver() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        ISdCardDriver(const ISdCardDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return ISdCardDriver& The assigned object.
         */
        ISdCardDriver &operator=(const ISdCardDriver &) = delete;

        /**
         * @brief Mounts the file system on the SD card.
         *
         * This function initializes and mounts the file system to prepare for file operations.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void mountFileSystem() = 0;

        /**
         * @brief Unmounts the file system from the SD card.
         *
         * This function unmounts the file system, closing any open files and ensuring that
         * all data is properly written to the SD card.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void unmountFileSystem() = 0;

        /**
         * @brief Opens a file on the SD card.
         *
         * This function prepares a file for reading or writing.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void openFile() = 0;

        /**
         * @brief Closes a file on the SD card.
         *
         * This function finalizes file operations and ensures that all data is written.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void closeFile() = 0;

        /**
         * @brief Synchronizes the file system.
         *
         * This function ensures that all file operations are committed and no data is lost.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void sync() = 0;

        /**
         * @brief Writes data to a file on the SD card.
         *
         * This function writes data to the currently open file on the SD card.
         *
         * @note This method is currently a placeholder and should ideally return a status.
         */
        virtual void writeToFile() = 0;
    };

}

#endif // ISdCardDriver_H_
