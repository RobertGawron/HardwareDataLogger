#ifndef ISdCardDriver_H_
#define ISdCardDriver_H_

#include "DriverState.hpp"

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
        virtual ~ISdCardDriver() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        ISdCardDriver(const ISdCardDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return ISdCardDriver& The assigned object.
         */
        ISdCardDriver &operator=(const ISdCardDriver &) = delete;
    };

}

#endif // ISdCardDriver_H_