#include "MyApplication.hpp"
#include "PlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationFacade.hpp"

#include <optional>

static std::optional<BusinessLogic::PlatformFactory> platform;
static std::optional<BusinessLogic::ApplicationFacade> facade;

void app_init()
{
    if (!platform.has_value())
    {
        platform.emplace();
    }

    if (!facade.has_value())
    {
        facade.emplace(platform.value());
    }

    facade.value().initialize();
}

void app_start()
{
    if (facade.has_value())
    {
        facade.value().start();
    }
}

void app_tick()
{
    if (facade.has_value())
    {
        facade.value().tick();
    }
}
