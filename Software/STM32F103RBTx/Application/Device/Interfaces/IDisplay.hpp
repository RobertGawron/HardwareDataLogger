/**
 * @file IDisplay.hpp
 * @brief Defines the IDisplay interface for display device interaction.
 */

#ifndef IDisplay_h
#define IDisplay_h

#include "U8g2lib.h"
#include "u8g2.h"

namespace Device
{
    /**
     * @class IDisplay
     * @brief Interface for display devices based on the U8G2 graphics library.
     */
    class IDisplay : public U8G2
    {
    public:
        IDisplay() = default; ///< Default constructor.
        virtual ~IDisplay() = default; ///< Virtual destructor.

        /**
         * @brief Initializes the display.
         * @return True if initialization succeeds, false otherwise.
         */
        virtual bool initialize() = 0;
    };
}

#endif // IDisplay_h
