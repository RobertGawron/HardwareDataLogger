#include "BusinessLogic/Inc/HmiViewManager.hpp"

// for test
#include <stdio.h>
#include "Driver/Inc/DisplayPixelColor.hpp"
#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
namespace BusinessLogic
{
    HmiViewManager::HmiViewManager(Driver::IDisplayDriver &_display)
        : display(_display)
    {
    }

    bool HmiViewManager::initialize()
    {
        volatile int x = 0;
        display.initialize();

        // for tests
        auto color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        display.drawHorizontalLine(1, 1, 20, color);
        printf("hello drawHorizontalLine\n");

        return true;
    }
    bool HmiViewManager::start()
    {
        display.start();
        return true;
    }
    bool HmiViewManager::stop()
    {
        display.stop();
        return true;
    }

    bool HmiViewManager::tick()
    {

        return true;
    }

}
