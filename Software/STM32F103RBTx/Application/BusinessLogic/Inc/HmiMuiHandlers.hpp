#ifndef HmiMuiHandlers_h
#define HmiMuiHandlers_h

/**
 * @file HmiMuiHandlers.hpp
 * @brief Declaration of MUI callback functions and registration utilities for HMI elements.
 *
 * This file contains declarations for callback functions that interface with the MUI library
 * to display measurement data on the HMI, and a function to register these callbacks with
 * their corresponding display objects.
 */

#include "BusinessLogic/Inc/HmiMeasurementModel.hpp"
#include "Device/Interface/IDisplay.hpp"
#include "MUIU8g2.h"
#include <cstdint>

namespace BusinessLogic
{
    /**
     * @brief Raw function (becuse that's what MUI library uses), used for last reading from device 1.
     * @param muiHandler Pointer to the MUI handler structure
     * @param muiMessage MUI message indicating the rendering phase
     * @return std::uint8_t MUI status code (0 in current implementation)
     */
    std::uint8_t device1_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    /**
     * @brief Raw function (becuse that's what MUI library uses), used for last reading from device 2.
     * @param muiHandler Pointer to the MUI handler structure
     * @param muiMessage MUI message indicating the rendering phase
     * @return std::uint8_t MUI status code (0 in current implementation)
     */
    std::uint8_t device2_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    /**
     * @brief Raw function (becuse that's what MUI library uses), used for last reading from device 3.
     * @param muiHandler Pointer to the MUI handler structure
     * @param muiMessage MUI message indicating the rendering phase
     * @return std::uint8_t MUI status code (0 in current implementation)
     */
    std::uint8_t device3_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    /**
     * @brief Raw function (becuse that's what MUI library uses), used for last reading from device 4.
     * @param muiHandler Pointer to the MUI handler structure
     * @param muiMessage MUI message indicating the rendering phase
     * @return std::uint8_t MUI status code (0 in current implementation)
     */
    std::uint8_t device4_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    /**
     * @brief Raw function (becuse that's what MUI library uses), used for last reading from device 5.
     * @param muiHandler Pointer to the MUI handler structure
     * @param muiMessage MUI message indicating the rendering phase
     * @return std::uint8_t MUI status code (0 in current implementation)
     */
    std::uint8_t device5_printLastReading(mui_t *muiHandler, std::uint8_t muiMessage);

    /**
     * @brief Registers MUI handlers with their required components.
     * @param ui Pointer to the MUI handler structure
     * @param display Pointer to the display interface for rendering
     * @param model Pointer to the measurement model providing data
     * @return true if registration succeeded, false if no slots available
     */
    bool registerMuiToItsObjects(mui_t *ui, Device::IDisplay *display, BusinessLogic::HmiMeasurementModel *model);

} // namespace BusinessLogic

#endif // HmiMuiHandlers_h
