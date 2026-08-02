module;

#include <cstdint>

module BusinessLogic.UserInterfaceSubsystem;

import BusinessLogic.ApplicationComponent;
import Device;
import Driver.PlatformFactory;

namespace BusinessLogic
{
    UserInterfaceSubsystem::UserInterfaceSubsystem(Driver::PlatformFactory &factory) noexcept
        : display{factory.display},
          brightness{factory.lightSensor, factory.displayBrightness},
          keyboard{factory.keyboard}
    {
    }

    auto UserInterfaceSubsystem::onInit() noexcept -> bool
    {
        const bool statusDisplay = display.init();
        const bool statusBrightness = brightness.init();
        const bool statusKeyboard = keyboard.init();

        return (statusDisplay && statusBrightness && statusKeyboard);
    }

    auto UserInterfaceSubsystem::onStart() noexcept -> bool
    {
        const bool statusDisplay = display.start();
        const bool statusBrightness = brightness.start();
        const bool statusKeyboard = keyboard.start();

        return (statusDisplay && statusBrightness && statusKeyboard);
    }

    auto UserInterfaceSubsystem::onStop() noexcept -> bool
    {
        const bool statusDisplay = display.stop();
        const bool statusBrightness = brightness.stop();
        const bool statusKeyboard = keyboard.stop();

        return (statusDisplay && statusBrightness && statusKeyboard);
    }

    auto UserInterfaceSubsystem::onTick() noexcept -> bool
    {

        return keyboard.tick();
    }

} // namespace BusinessLogic