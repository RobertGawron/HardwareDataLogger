#ifndef HmiMuiHandlers_h
#define HmiMuiHandlers_h

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interfaces/IDisplay.hpp"

#include "MUIU8g2.h"

#include <cstdint>

namespace BusinessLogic
{
    // Those are raw C functions, that needs to have signature based on what MUI lib requires.
    std::uint8_t device1_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);
    std::uint8_t device2_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);
    std::uint8_t device3_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);
    std::uint8_t device4_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);
    std::uint8_t device5_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    bool registerMuiToItsObjects(mui_t *ui, Device::IDisplay *display, BusinessLogic::HmiMeasurementModel *model);

}

#endif // HmiMuiHandlers_h
