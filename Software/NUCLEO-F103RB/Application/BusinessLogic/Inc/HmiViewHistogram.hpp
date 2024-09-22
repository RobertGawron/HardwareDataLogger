#ifndef HmiViewHistogram_h
#define HmiViewHistogram_h

#include "IHmiView.hpp"
#include "IDisplayDriver.hpp"

namespace BusinessLogic
{
    // display histogram data of colected data from user defined period
    class HmiViewHistogram : public IHmiView
    {
    public:
        HmiViewHistogram(Driver::IDisplayDriver &displayDriver);

        HmiViewHistogram() = delete;
        virtual ~HmiViewHistogram() = default;

        HmiViewHistogram(const HmiViewHistogram &) = delete;
        HmiViewHistogram &operator=(const HmiViewHistogram &) = delete;

        virtual void updateDisplay(const HmiDataModel &model) override;

        virtual void init() override;

    protected:
        Driver::IDisplayDriver &displayDriver;
    };
}

#endif
