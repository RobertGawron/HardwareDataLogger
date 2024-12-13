/**
 * @file KeyboardFourPushButtonsDriver.hpp
 * @brief Defines the KeyboardFourPushButtonsDriver class for reading the state of four push buttons via GPIO.
 */

#ifndef DRIVER_KeyboardFourPushButtonsDriver_H_
#define DRIVER_KeyboardFourPushButtonsDriver_H_

#include "Driver/Interfaces/IKeyboardDriver.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h" // for KEY_UP_*_Port, KEY_*_Pin

namespace Driver
{
    /**
     * @class KeyboardFourPushButtonsDriver
     * @brief Periodically reads the state of four push buttons via GPIO.
     *
     * This class represents the raw state of keys read from GPIO pins on a microcontroller to which the buttons are connected. Note that there is no HW debouncing circuit and there is no pull-up resistor o the pCB (the pull-up resistor is configured in CubeMX)
     */
    class KeyboardFourPushButtonsDriver : public IKeyboardDriver
    {
    public:
        /**
         * @brief Default constructor for KeyboardFourPushButtonsDriver.
         */
        KeyboardFourPushButtonsDriver() = default;

        /**
         * @brief Default destructor for KeyboardFourPushButtonsDriver.
         */
        virtual ~KeyboardFourPushButtonsDriver() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        KeyboardFourPushButtonsDriver(const KeyboardFourPushButtonsDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return KeyboardFourPushButtonsDriver& The assigned object.
         */
        KeyboardFourPushButtonsDriver &operator=(const KeyboardFourPushButtonsDriver &) = delete;

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

        /**
         * @brief Number of keys supported by the keyboard.
         *
         * This constant defines the total number of keys that are supported by the keyboard driver.
         * It is derived from the last unused key identifier.
         */
        static constexpr uint8_t AmountOfKeys = static_cast<uint8_t>(Driver::KeyboardKeyIdentifier::LastNotUsed);

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

    private:
        /**
         * @brief Reads the state of a specific GPIO pin.
         *
         * This function is private because it relies on STM32-specific macros. It should not be used directly
         * by other classes to maintain platform agnosticism. Instead, use `getState` which provides a
         * platform-independent interface.
         *
         * @param GPIOx The GPIO port where the button is connected.
         * @param GPIO_Pin The GPIO pin number where the button is connected.
         * @return The state of the button connected to the specified GPIO pin (`KeyboardKeyState`).
         */
        Driver::KeyboardKeyState getKeyStateFromHW(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) const;

        /**
         * @brief Structure representing the state of a key.
         *
         * This structure holds information about the current state of a GPIO pin connected to a button.
         * It contains the state of the GPIO (either pressed or not pressed), as well as the low-level
         * access details to the GPIO peripheral, including the port and pin number.
         */
        typedef struct KeyState
        {
            KeyboardKeyState state;  /**< State of the GPIO connected to the button, either pressed (low) or not pressed (high). */
            GPIO_TypeDef *GPIO_Port; /**< Pointer to the GPIO port associated with the key. */
            uint16_t GPIO_Pin;       /**< GPIO pin number associated with the key. */
        } KeyState;

        /**
         * @brief Array holding the state and configuration for each key.
         *
         * This array contains the initial state and GPIO configuration for each key supported by the keyboard.
         * Each entry corresponds to a key, including its initial state (not pressed) and the associated
         * GPIO port and pin number.
         */
        KeyState keyState[AmountOfKeys] = {
            {KeyboardKeyState::NotPressed, KEY_UP_GPIO_Port, KEY_UP_Pin},      /**< Key Up: Not pressed, associated GPIO port and pin. */
            {KeyboardKeyState::NotPressed, KEY_DOWN_GPIO_Port, KEY_DOWN_Pin},  /**< Key Down: Not pressed, associated GPIO port and pin. */
            {KeyboardKeyState::NotPressed, KEY_LEFT_GPIO_Port, KEY_LEFT_Pin},  /**< Key Left: Not pressed, associated GPIO port and pin. */
            {KeyboardKeyState::NotPressed, KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin} /**< Key Right: Not pressed, associated GPIO port and pin. */
        };
    };

}

#endif // DRIVER_KeyboardFourPushButtonsDriver_H_