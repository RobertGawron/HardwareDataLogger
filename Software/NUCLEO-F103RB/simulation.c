#include <stdio.h>
#include <stdint.h>
/*
#include "gm_display_updater.h"
#include "gm_measurement_calculator.h"
#include "gm_logger.h"
#include "gm_keyboard_keys.h"
#include "gm_keyboard.h"

#include "DriversPCSimulation/gm_logger_sim.h"
#include "DriversPCSimulation/ssd1306_i2c_sim.h"
*/
__declspec(dllexport) void Lib_Simulation_Init()
{
    /*GMDisplayUpdater_Init();
    DataLoggerShield_Init();
    GMLogger_Init();*/
}

__declspec(dllexport) void Lib_DataLoggerShield_OnGMPulseObserved()
{
    //DataLoggerShield_OnGMPulseObserved();
}

__declspec(dllexport) void Lib_DataLoggerShield_OnSamplingDone()
{
    /*DataLoggerShield_OnSamplingDone();
    GMDisplayUpdater_UpdateMeasurements();
    GMLogger_LogMeasurement();*/
}

__declspec(dllexport) void Lib_DataLoggerShield_GetLoggedData(uint8_t** buffer, uint16_t* size)
{
    //GMLoggerSIM_GetLoggedData(buffer, size);
}

__declspec(dllexport) void Lib_DataLoggerShield_KeyPress()
{
    //GMKeyboard_OnKeyPressDetection(GMKEYBOARD_KEY_UP);
}

__declspec(dllexport) uint8_t Lib_DataLoggerShield_GetDisplayLength()
{
    return 0;//SSD1306I2CSIM_GetDisplayLength();
}

__declspec(dllexport) uint8_t Lib_DataLoggerShield_GetDisplayHeight()
{
    return 0;//SSD1306I2CSIM_GetDisplayHeight();
}

__declspec(dllexport) uint8_t* Lib_DataLoggerShield_GetDisplayContent()
{
    return 0;//SSD1306I2CSIM_GetDisplayContent();
}

 