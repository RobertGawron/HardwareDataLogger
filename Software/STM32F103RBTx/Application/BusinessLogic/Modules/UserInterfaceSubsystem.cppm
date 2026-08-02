module;

#include <cstdint>

export module BusinessLogic.UserInterfaceSubsystem;

import BusinessLogic.ApplicationComponent;
import Device;
import Driver.PlatformFactory;

export namespace BusinessLogic
{
    /**
     * @brief Subsystem responsible for managing user interaction devices.
     *
     * Owns and manages the lifecycle of the Display, DisplayBrightness,
     * and Keyboard. Handles UI state updates and input processing.
     */
    class UserInterfaceSubsystem final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs the subsystem using platform-provided drivers.
         */
        explicit UserInterfaceSubsystem(Driver::PlatformFactory &factory) noexcept;

        ~UserInterfaceSubsystem() = default;

        UserInterfaceSubsystem() = delete;
        UserInterfaceSubsystem(const UserInterfaceSubsystem &) = delete;
        UserInterfaceSubsystem(UserInterfaceSubsystem &&) = delete;
        UserInterfaceSubsystem &operator=(const UserInterfaceSubsystem &) = delete;
        UserInterfaceSubsystem &operator=(UserInterfaceSubsystem &&) = delete;

        /**
         * @brief Initializes UI devices.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts UI devices.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops UI devices.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

        /**
         * @brief Executes one tick of the UI logic (e.g., reading keyboard, updating display).
         */
        [[nodiscard]] auto onTick() noexcept -> bool;

    private:
        Device::Display display;
        Device::DisplayBrightness brightness;
        Device::Keyboard keyboard;
    };

} // namespace BusinessLogic