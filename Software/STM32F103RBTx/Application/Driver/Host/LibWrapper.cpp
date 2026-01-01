#include "LibWrapper.hpp"
#include "PlatformFactory.hpp"

#include "BusinessLogic/Inc/ApplicationFacade.hpp"

#include "Driver/Interface/KeyState.hpp"
#include "Driver/Interface/KeyIdentifier.hpp"

#include "PulseCounterDriverStub.hpp"
#include "KeyboardDriverStub.hpp"
#include "St7735DisplayDriverStub.hpp"

#include "EventHandlers.hpp"

#include <array>
#include <cstdint>
#include <cstdio>
#include <optional>
#include <functional>

namespace
{
    // codechecker_suppress [clang-diagnostic-global-constructors,clang-diagnostic-exit-time-destructors]
    std::optional<BusinessLogic::PlatformFactory> platform;
    // codechecker_suppress [clang-diagnostic-global-constructors,clang-diagnostic-exit-time-destructors]
    std::optional<BusinessLogic::ApplicationFacade> facade;
}

std::optional<std::reference_wrapper<BusinessLogic::PlatformFactory>> getPlatform();
std::optional<std::reference_wrapper<BusinessLogic::ApplicationFacade>> getFacade();

std::optional<std::reference_wrapper<BusinessLogic::PlatformFactory>> getPlatform()
{
    std::optional<std::reference_wrapper<BusinessLogic::PlatformFactory>> result;

    if (!platform.has_value())
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized!\n"));
    }
    else
    {
        result = std::ref(platform.value());
    }

    return result;
}

std::optional<std::reference_wrapper<BusinessLogic::ApplicationFacade>> getFacade()
{
    std::optional<std::reference_wrapper<BusinessLogic::ApplicationFacade>> result;

    if (!facade.has_value())
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Facade not initialized!\n"));
    }
    else
    {
        result = std::ref(facade.value());
    }

    return result;
}

void LibWrapper_Init()
{
    if (!platform.has_value())
    {
        platform.emplace();
    }

    if (!facade.has_value())
    {
        facade.emplace(platform.value());
    }

    if (facade.has_value())
    {
        facade.value().initialize();
        facade.value().start();
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Failed to initialize facade!\n"));
    }
}

void LibWrapper_Tick()
{
    if (facade.has_value())
    {
        facade.value().tick();
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Facade not initialized in LibWrapper_Tick!\n"));
    }
}

void LibWrapper_KeyPressed(KeyIdentifier keyId)
{
    if (platform.has_value())
    {
        auto &keyboardStub = static_cast<Driver::KeyboardDriverStub &>(
            platform.value().getKeyboardDriver());

        keyboardStub.setKeyState(
            static_cast<Driver::KeyIdentifier>(keyId),
            Driver::KeyState::Pressed);
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized in LibWrapper_KeyPressed!\n"));
    }
}

void LibWrapper_KeyReleased(KeyIdentifier keyId)
{
    if (platform.has_value())
    {
        auto &keyboardStub = static_cast<Driver::KeyboardDriverStub &>(
            platform.value().getKeyboardDriver());

        keyboardStub.setKeyState(
            static_cast<Driver::KeyIdentifier>(keyId),
            Driver::KeyState::NotPressed);
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized in LibWrapper_KeyReleased!\n"));
    }
}

std::uint8_t LibWrapper_GetDisplayWidth()
{
    std::uint8_t width = 0U;

    if (platform.has_value())
    {
        const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(
            platform.value().getDisplayDriver());

        static_cast<void>(displayStub.getXSize(width));
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized in LibWrapper_GetDisplayWidth!\n"));
    }

    return width;
}

std::uint8_t LibWrapper_GetDisplayHeight()
{
    std::uint8_t height = 0U;

    if (platform.has_value())
    {
        const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(
            platform.value().getDisplayDriver());

        static_cast<void>(displayStub.getYSize(height));
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized in LibWrapper_GetDisplayHeight!\n"));
    }

    return height;
}

std::uint16_t LibWrapper_GetPixelValue(std::uint8_t xPosition, std::uint8_t yPosition)
{
    std::uint16_t value = 0U;

    if (platform.has_value())
    {
        const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(
            platform.value().getDisplayDriver());

        value = displayStub.getPixelValue(xPosition, yPosition);
    }
    else
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: Platform not initialized in LibWrapper_GetPixelValue!\n"));
    }

    return value;
}

void LibWrapper_UpdatePulseCounters(const std::array<std::uint32_t, PULSE_COUNTER_COUNT> &pulseCounters)
{
    for (std::uint8_t i = 0U; i < PULSE_COUNTER_COUNT; ++i)
    {
        setPulseCounter(i, pulseCounters[i]);
    }
}

void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback)
{
    registerSerialTxCallback(callback);
}

void LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback callback)
{
    registerSdCardOpenCallback(callback);
}

void LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback callback)
{
    registerSdCardWriteCallback(callback);
}

void LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback callback)
{
    registerSdCardCloseCallback(callback);
}

void LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback callback)
{
    registerSdCardInitializeCallback(callback);
}

void LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback callback)
{
    registerSdCardStartCallback(callback);
}

void LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback callback)
{
    registerSdCardStopCallback(callback);
}

void LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback callback)
{
    registerSdCardResetCallback(callback);
}
