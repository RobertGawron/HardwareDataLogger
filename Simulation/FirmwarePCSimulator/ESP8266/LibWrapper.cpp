#include "LibWrapper.hpp"
#include "HmiEventHandlers.hpp"
#include "main.h"

#include <cstdint>

void LibWrapper_Init()
{
    // From platformIO main.cpp
    setup();
}

void LibWrapper_Tick()
{
    // From platformIO main.cpp
    loop();
}

void LibWrapper_RegisterOnSerialTx(void (*callback)(char *))
{
    registerOnSerialTx(callback);
}

void LibWrapper_RegisterOnGpioChange(void (*callback)(GPIO_ID, bool))
{
    registerOnGpioChange(callback);
}

HAL_StatusTypeDef LibWrapper_OnSerialRx(const std::uint8_t *pData, std::uint16_t Size, std::uint32_t Timeout)
{
    return serialRx(pData, Size, Timeout);
}
