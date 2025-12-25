#ifndef ISdCardDriver_H_
#define ISdCardDriver_H_

#include "Driver/Interface/DriverState.hpp"
#include "Driver/Interface/SdCardStatus.hpp"

#include <string_view>
#include <span>

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
        enum class FileOpenMode : std::uint8_t
        {
            OVERWRITE, // Create new or overwrite existing file
            APPEND     // Append to existing file, create if doesn't exist
        };

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

        virtual SdCardStatus openFile(std::string_view filename, FileOpenMode mode) = 0;

        virtual SdCardStatus write(std::span<const std::uint8_t> data) = 0;

        virtual SdCardStatus closeFile() = 0;
    };

}

#endif // ISdCardDriver_H_
