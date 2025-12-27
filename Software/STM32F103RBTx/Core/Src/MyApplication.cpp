#include "MyApplication.hpp"
#include "PlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationFacade.hpp"

BusinessLogic::PlatformFactory platform;
BusinessLogic::ApplicationFacade facade{platform};

void app_init()
{
    facade.initialize();
}

void app_start()
{
    facade.start();
}

void app_tick()
{
    facade.tick();
}
