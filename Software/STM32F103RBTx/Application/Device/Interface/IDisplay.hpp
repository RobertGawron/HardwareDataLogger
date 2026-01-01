/**
 * @file IDisplay.hpp
 * @brief Defines the IDisplay interface for display device interaction.
 */

#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

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
        IDisplay() noexcept = default;
        virtual ~IDisplay() = default;

        // Non-copyable and non-movable
        IDisplay(const IDisplay &) = delete;
        IDisplay(IDisplay &&) = delete;
        IDisplay &operator=(const IDisplay &) = delete;
        IDisplay &operator=(IDisplay &&) = delete;

        /**
         * @brief Initializes the display.
         * @return True if initialization succeeds, false otherwise.
         */
        [[nodiscard]] virtual bool initialize() noexcept = 0;
    };

} // namespace Device

#endif // IDISPLAY_HPP