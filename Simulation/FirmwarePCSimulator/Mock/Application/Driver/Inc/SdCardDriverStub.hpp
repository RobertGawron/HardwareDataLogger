/**
 * @file SdCardDriverStub.hpp
 * @brief Defines the SdCardDriverStub class for interacting with SD cards.
 */

#ifndef SdCardDriverStub_H_
#define SdCardDriverStub_H_

#include "Driver/Interfaces/ISdCardDriver.hpp"

namespace Driver
{
    /**
     * @class SdCardDriverStub
     * @brief Low-level driver for SD card operations.
     *
     * This class implements the `ISdCardDriver` interface to handle low-level
     * operations related to storing data on an SD card. This includes tasks like
     * mounting/unmounting the file system, opening/closing files, and writing data.
     *
     * Note: This class does not manage the content or metadata of the files. Its
     * primary concern is to provide low-level access to the SD card.
     */
    class SdCardDriverStub : public ISdCardDriver
    {
    public:
        /**
         * @brief Default constructor for SdCardDriverStub.
         */
        explicit SdCardDriverStub();

        /**
         * @brief Virtual destructor for SdCardDriverStub.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~SdCardDriverStub() = default;

        // Delete copy constructor and assignment operator
        SdCardDriverStub(const SdCardDriverStub &) = delete;
        SdCardDriverStub &operator=(const SdCardDriverStub &) = delete;

        bool onInitialize() override;

        bool onStart() override;

        bool onStop() override;

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

#endif // SdCardDriverStub_H_