/*
 Arduino.h - Main include file for the Arduino SDK
 Copyright (c) 2005-2013 Arduino Team.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef Arduino_h
#define Arduino_h

// codechecker_suppress [all] excluded from CodeChecker analysis because i need compatibility with the Arduino code

#include <cstdint>

#define HIGH 0x1 // codechecker_suppress [modernize-macro-to-enum]
#define LOW 0x0  // codechecker_suppress [modernize-macro-to-enum]

// GPIO FUNCTIONS
#define INPUT 0x00 // codechecker_suppress [modernize-macro-to-enum]

#define INPUT_PULLUP 0x02
#define INPUT_PULLDOWN_16 0x04 // PULLDOWN only possible for pin16
#define OUTPUT 0x01
#define OUTPUT_OPEN_DRAIN 0x03
#define WAKEUP_PULLUP 0x05
#define WAKEUP_PULLDOWN 0x07
#define SPECIAL 0xF8 // defaults to the usable BUSes uart0rx/tx uart1tx and hspi
#define FUNCTION_0 0x08
#define FUNCTION_1 0x18
#define FUNCTION_2 0x28
#define FUNCTION_3 0x38
#define FUNCTION_4 0x48

// Why not just use bool? anyway to be aligned with Arduino code we need this
typedef bool boolean;

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int val);
void analogWriteMode(uint8_t pin, int val, bool openDrain);
void analogWriteFreq(uint32_t freq);
void analogWriteResolution(int res);
void analogWriteRange(uint32_t range);

// C:\Users\rober\.platformio\packages\framework-arduinoespressif8266\cores\esp8266\core_esp8266_features.h
unsigned long millis();

// C:\Users\rober\.platformio\packages\framework-arduinoespressif8266\cores\esp8266\core_esp8266_features.h
void delay(unsigned long);

#endif