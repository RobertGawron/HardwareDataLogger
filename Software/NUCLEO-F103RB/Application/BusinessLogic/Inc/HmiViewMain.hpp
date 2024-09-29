#ifndef HmiViewMain_h
#define HmiViewMain_h

#include "BusinessLogic/Interfaces/IHmiView.hpp"

namespace BusinessLogic
{
    // initial layout that display main summary of meassurements fromm all sensors.

    class HmiViewMain : public IHmiView
    {
    public:
        HmiViewMain(Driver::IDisplayDriver &displayDriver);

        HmiViewMain() = delete;
        virtual ~HmiViewMain() = default;

        HmiViewMain(const HmiViewMain &) = delete;
        HmiViewMain &operator=(const HmiViewMain &) = delete;

        virtual void updateDisplay(const HmiDataModel &model) override;

        virtual void init() override;

    protected:
        Driver::IDisplayDriver &displayDriver;
    };

}

#endif
