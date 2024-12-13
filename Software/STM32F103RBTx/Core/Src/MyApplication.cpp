#include "MyApplication.hpp"
#include "PlatformFactoryStm32.hpp"
#include "BusinessLogic/Inc/ApplicationBuilder.hpp"

BusinessLogic::PlatformFactoryStm32 platform;
BusinessLogic::ApplicationBuilder builder{platform};

void app_init()
{
    builder.initialize();
}

void app_start()
{
    builder.start();
}

void app_tick()
{
    builder.tick();
}
