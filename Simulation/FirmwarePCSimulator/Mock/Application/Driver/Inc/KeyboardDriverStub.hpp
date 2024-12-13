/**
 * @file KeyboardDriverStub.hpp
 * @brief Defines the KeyboardDriverStub class for reading the state of four push buttons via GPIO.
 */

#ifndef KeyboardDriverStub_H_
#define KeyboardDriverStub_H_

#include "Driver/Interfaces/IKeyboardDriver.hpp"
#include "Driver/Inc/KeyboardKeyState.hpp"

namespace Driver
{
    /**
     * @class KeyboardDriverStub
     * @brief Periodically reads the state of four push buttons via GPIO.
     *
     * This class represents the raw state of keys read from GPIO pins on a microcontroller to which the buttons are connected. Note that there is no HW debouncing circuit and there is no pull-up resistor o the pCB (the pull-up resistor is configured in CubeMX)
     */
    class KeyboardDriverStub : public IKeyboardDriver
    {
    public:
        /**
         * @brief Default constructor for KeyboardDriverStub.
         */
        KeyboardDriverStub() = default;

        /**
         * @brief Default destructor for KeyboardDriverStub.
         */
        virtual ~KeyboardDriverStub() = default;

        // Delete copy constructor and assignment operator
        KeyboardDriverStub(const KeyboardDriverStub &) = delete;
        KeyboardDriverStub &operator=(const KeyboardDriverStub &) = delete;

        /**
         * @brief Periodically checks the state of the push buttons.
         *
         * This function should be called regularly (e.g., in a timer interrupt or main loop) to update
         * the state of the buttons.
         */
        virtual bool tick() override;

        /**
         * @brief Gets the current state of a specified button.
         *
         * This function returns the state (pressed or not pressed) of a given button identified by `key`.
         *
         * @param key The identifier of the button whose state is requested.
         * @return The current state of the button (`KeyboardKeyState`).
         */
        virtual KeyboardKeyState getKeyState(const KeyboardKeyIdentifier key) const override;
        // virtual KeyboardKeyState getKeyState(const KeyboardKeyIdentifier key) const = 0;

        /**
         * @brief Number of keys supported by the keyboard.
         *
         * This constant defines the total number of keys that are supported by the keyboard driver.
         * It is derived from the last unused key identifier.
         */
        static constexpr uint8_t AmountOfKeys = static_cast<uint8_t>(Driver::KeyboardKeyIdentifier::LastNotUsed);

        KeyboardKeyState keyState[AmountOfKeys] = {KeyboardKeyState::NotPressed};

    protected:
        /**
         * @brief Handles the initialization of the driver.
         *
         * Since initialization is already managed in `main()` by CubeMX-generated code,
         * this method does not perform any additional initialization tasks.
         *
         * @return true to indicate that the driver is ready to move to the Initialized state.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the driver.
         *
         * This method is provided to fulfill the interface requirement, but no specific
         * actions are needed to start the driver since it only reads GPIO inputs.
         *
         * @return true, indicating the driver is effectively "running" by being ready to read GPIO inputs.
         */
        bool onStart() override;

        /**
         * @brief Stops the driver.
         *
         * This method is provided to fulfill the interface requirement, but no specific
         * actions are needed to stop the driver since it only reads GPIO inputs.
         *
         * @return true, as stopping does not involve any action beyond stopping the read operations.
         */
        bool onStop() override;

        /**
         * @brief Resets the driver.
         *
         * This method is provided to fulfill the interface requirement, but no specific
         * actions are needed to reset the driver since it only reads GPIO inputs.
         *
         * @return true, as the reset does not involve any action beyond reinitializing the read state.
         */
        bool onReset() override;
    };

}

#endif // DRIVER_KeyboardFourPushButtonsDriver_H_