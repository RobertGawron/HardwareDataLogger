#ifndef HmiMui_h
#define HmiMui_h

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Interfaces/IHmi.hpp"

namespace BusinessLogic
{

    class HmiMui : public IHmi
    {
    public:
        HmiMui(Device::IDisplay &display,
               Device::IDisplayBrightnessRegulator &displayBrightnessRegulator,
               Device::IKeyboard &keyboard);

        HmiMui() = delete;
        virtual ~HmiMui() = default;

        virtual bool initialize() override;
        virtual bool start() override;

        virtual bool tick() override;

    private:
        Device::IDisplay &display;
        Device::IDisplayBrightnessRegulator &displayBrightnessRegulator;
        Device::IKeyboard &keyboard;
    };
}

#endif