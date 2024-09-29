#ifndef Simulation_h
#define Simulation_h

#include <stdint.h>
#include "MyApplication.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
    // TODO add Doxygen

    void Simulation_Init();
    void Simulation_Tick();
    uint8_t Simulation_GetDisplayWidth();
    uint8_t Simulation_GetDisplayHeight();

    typedef struct PixelValue
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } PixelValue;

    PixelValue Simulation_GetPixelValue(uint8_t x, uint8_t y);

#ifdef __cplusplus
}
#endif

#endif
