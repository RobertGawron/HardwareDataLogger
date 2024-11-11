#include "BusinessLogic/Inc/HmiViewManager.hpp"

// for test
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
        return true;
    }
    bool HmiViewManager::start()
    {
        uint16_t color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        display.fillScreen(color);

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

        // for tests
        uint16_t color = Driver::DisplayPixelColor::getColor(0x2f, 0xff, 0xff);
        display.fillScreen(color);

        return true;
    }

}
