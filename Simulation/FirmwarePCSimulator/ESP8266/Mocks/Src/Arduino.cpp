#include "Arduino.h"
#include <stdint.h> // for comptibility with Arduino library
#include <chrono>
#include <thread>
#include <iostream>

#include "HmiEventHandlers.hpp"

void pinMode(uint8_t pin, uint8_t mode)
{
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    setPinState(static_cast<GPIO_ID>(pin), val);
}

int digitalRead(uint8_t pin)
{
    // dummy value
    const int value = 0;
    return value;
}

int analogRead(uint8_t pin)
{
    // dummy value
    const int value = 0;
    return value;
}

void analogReference(uint8_t mode)
{
}

void analogWrite(uint8_t pin, int val)
{
}

void analogWriteMode(uint8_t pin, int val, bool openDrain)
{
}

void analogWriteFreq(uint32_t freq)
{
}

void analogWriteResolution(int res)
{
}

void analogWriteRange(uint32_t range)
{
}

// Simulated Arduino millis() function for PC
// Original in .platformio\packages\framework-arduinoespressif8266\cores\esp8266\core_esp8266_features.h
unsigned long millis()
{
    static auto start_time = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
    return static_cast<unsigned long>(elapsed);
}

// Simulated Arduino delay() function for PC
// Original in .platformio\packages\framework-arduinoespressif8266\cores\esp8266\core_esp8266_features.h
void delay(unsigned long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
