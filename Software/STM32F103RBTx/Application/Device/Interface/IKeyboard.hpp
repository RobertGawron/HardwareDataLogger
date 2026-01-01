#ifndef IKEYBOARD_HPP
#define IKEYBOARD_HPP

#include "Device/Inc/KeyActionState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include <cstdint>

namespace Device
{
    /**
     * @class IKeyboard
     * @brief Interface for keyboard functionality.
     *
     * The IKeyboard class defines an interface for interacting with keyboard hardware. It provides methods for
     * initializing the keyboard, processing periodic updates, and retrieving the state of individual keys. This
     * interface serves as a contract for any keyboard implementation, allowing different hardware or virtual keyboards
     * to be used interchangeably.
     */
    class IKeyboard
    {
    public:
        constexpr IKeyboard() noexcept = default;
        virtual ~IKeyboard() = default;

        // Non-copyable and non-movable
        IKeyboard(const IKeyboard &) = delete;
        IKeyboard(IKeyboard &&) = delete;
        IKeyboard &operator=(const IKeyboard &) = delete;
        IKeyboard &operator=(IKeyboard &&) = delete;

        /**
         * @brief Initializes the keyboard.
         *
         * This method performs any necessary setup and initialization of the keyboard hardware or virtual device.
         *
         * @return true if initialization was successful, false otherwise.
         */
        [[nodiscard]] virtual bool init() noexcept = 0;

        /**
         * @brief Processes periodic updates for the keyboard.
         *
         * This method should be called regularly to handle key state changes and other keyboard-related updates.
         *
         * @return true if the tick operation was successful, false otherwise.
         */
        [[nodiscard]] virtual bool tick() noexcept = 0;

        /**
         * @brief Retrieves the state of a specific key.
         *
         * This method provides the current action state of a given key on the keyboard.
         *
         * @param key The identifier of the key whose state is to be retrieved.
         * @return The action state of the specified key.
         */
        [[nodiscard]] virtual KeyActionState getKeyState(Driver::KeyIdentifier key) const noexcept = 0;
    };

} // namespace Device

#endif // IKEYBOARD_HPP