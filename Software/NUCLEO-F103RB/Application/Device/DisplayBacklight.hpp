#ifndef DISPLAYBACKLIGHT_H_
#define DISPLAYBACKLIGHT_H_

#include "IAmbientLightSensorDriver.hpp"
#include "IDisplayBacklightDriver.hpp"

namespace Device
{
    /// @brief set backlight of the LCD display according
    ///  ambient light and user preferences
    class DisplayBacklight
    {
    public:
        DisplayBacklight(
            Driver::IAmbientLightSensorDriver &_ambientLightSensorDriver,
            Driver::IDisplayBacklightDriver &_displayBacklightDriver);
        virtual ~DisplayBacklight() = default;

        void init();
        void tick();
        uint8_t getBrightnessPercentage();
        void setBrightnessPercentage(uint8_t level);

    private:
        Driver::IAmbientLightSensorDriver &ambientLightSensorDriver;
        Driver::IDisplayBacklightDriver &displayBacklightDriver;

        uint8_t level = 0u;
    };

}

#endif
