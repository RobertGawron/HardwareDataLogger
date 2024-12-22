#include "BusinessLogic/Inc/HmiMuiHandlers.hpp"
#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Interfaces/IDisplay.hpp"

#include <array>
#include <algorithm> // For std::find_if
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cinttypes> // for PRIu32

#include "mui.h"
#include "mui_u8g2.h"

namespace BusinessLogic
{
    // Struct for mapping MUI to display and model entries
    struct DisplayMapEntry
    {
        mui_t *ui = nullptr;
        Device::IDisplay *display = nullptr;
        BusinessLogic::HmiMeasurementModel *model = nullptr;
    };

    DisplayMapEntry *findEntryByMui(mui_t *muiHandler);
    uint8_t printLastReading(mui_t *muiHandler, uint8_t muiMessage, Device::MeasurementDeviceId source);

    namespace
    {
        // Define a constant for maximum displays, change if needed
        constexpr std::size_t MAX_MUI_AMOUNT = 1u;
        std::array<DisplayMapEntry, MAX_MUI_AMOUNT> muiMap{};

        constexpr std::size_t LabelTextBufferSize = 10;
        char labelTextBuffer[LabelTextBufferSize];
    }

    uint8_t device1_printLastReading(mui_t *muiHandler, uint8_t muiMessage)
    {
        return printLastReading(muiHandler,
                                muiMessage,
                                Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_1);
    }

    uint8_t device2_printLastReading(mui_t *muiHandler, uint8_t muiMessage)
    {
        return printLastReading(muiHandler,
                                muiMessage,
                                Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_2);
    }

    uint8_t device3_printLastReading(mui_t *muiHandler, uint8_t muiMessage)
    {
        return printLastReading(muiHandler,
                                muiMessage,
                                Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_3);
    }

    uint8_t device4_printLastReading(mui_t *muiHandler, uint8_t muiMessage)
    {
        return printLastReading(muiHandler,
                                muiMessage,
                                Device::MeasurementDeviceId::DEVICE_PULSE_COUNTER_4);
    }

    uint8_t device5_printLastReading(mui_t *muiHandler, uint8_t muiMessage)
    {
        return printLastReading(muiHandler,
                                muiMessage,
                                Device::MeasurementDeviceId::DEVICE_UART_1);
    }

    DisplayMapEntry *findEntryByMui(mui_t *muiHandler)
    {
        // The std::find_if function returns an iterator, which is an object (not a raw pointer) in modern STL containers.
        // codechecker_suppress [readability-qualified-auto]
        auto it = std::find_if(
            muiMap.begin(),
            muiMap.end(),
            [muiHandler](const DisplayMapEntry &entry)
            {
                return entry.ui != nullptr && entry.ui == muiHandler;
            });

        if (it != muiMap.end())
        {
            return &(*it); // Return a pointer to the found entry
        }

        return nullptr; // Return nullptr if no matching entry is found
    }

    // Method to register a new MUI object
    bool registerMuiToItsObjects(mui_t *ui, Device::IDisplay *display, BusinessLogic::HmiMeasurementModel *model)
    {
        bool status = false;

        for (auto &entry : muiMap)
        {
            if (entry.ui == nullptr) // Find the first available slot
            {
                entry.ui = ui;
                entry.display = display;
                entry.model = model;
                status = true;
            }
        }
        return status;
    }

    uint8_t printLastReading(mui_t *muiHandler, uint8_t muiMessage, Device::MeasurementDeviceId source)
    {

        if (muiMessage == MUIF_MSG_DRAW)
        {
            DisplayMapEntry *entry = findEntryByMui(muiHandler);

            if (entry != nullptr)
            {
                const int result = std::snprintf(
                    labelTextBuffer,
                    LabelTextBufferSize,
                    "%" PRIu32,
                    entry->model->getLatestMeasurement(source));

                if (result >= 0)
                {
                    const std::uint16_t x = mui_get_x(muiHandler);
                    const std::uint16_t y = mui_get_y(muiHandler);

                    entry->display->setCursor(x, y);
                    entry->display->drawUTF8(x, y, labelTextBuffer);
                }
            }
        }

        return 0; // TODO what should this function return?
    }
}
