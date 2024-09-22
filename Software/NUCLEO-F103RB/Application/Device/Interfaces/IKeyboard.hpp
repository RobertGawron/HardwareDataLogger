#ifndef IKeyboard_h
#define IKeyboard_h

#include "IKeyboardDriver.hpp"
#include "KeyboardKeyActionState.hpp"
#include "KeyboardKeyIdentifier.hpp"

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
        /**
         * @brief Default constructor.
         *
         * Initializes an instance of IKeyboard. The default constructor is provided for compatibility and
         * does not perform any specific initialization.
         */
        IKeyboard() = default;

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived classes. The destructor is virtual to support polymorphic deletion.
         */
        virtual ~IKeyboard() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of IKeyboard instances.
         */
        IKeyboard(const IKeyboard &) = delete;

        /**
         * @brief Deleted assignment operator.
         *
         * Prevents assignment of IKeyboard instances.
         * @return IKeyboard& Reference to this object.
         */
        IKeyboard &operator=(const IKeyboard &) = delete;

        /**
         * @brief Initializes the keyboard.
         *
         * This method performs any necessary setup and initialization of the keyboard hardware or virtual device.
         *
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool init() = 0;

        /**
         * @brief Processes periodic updates for the keyboard.
         *
         * This method should be called regularly to handle key state changes and other keyboard-related updates.
         */
        virtual bool tick() = 0;

        /**
         * @brief Retrieves the state of a specific key.
         *
         * This method provides the current action state of a given key on the keyboard.
         *
         * @param key The identifier of the key whose state is to be retrieved.
         * @return The action state of the specified key.
         */
        virtual KeyboardKeyActionState getKeyState(Driver::KeyboardKeyIdentifier key) const = 0;
    };

}

#endif // IKeyboard_h