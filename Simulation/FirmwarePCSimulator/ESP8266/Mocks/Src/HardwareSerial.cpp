#include "HardwareSerial.h"

#include <queue>
#include <vector>
#include <cstdint>
#include <cstring>
#include <optional>
#include <thread>
#include <chrono>

// #include <stdio.h>
#include <iostream>

#include "HmiEventHandlers.hpp"

extern std::deque<uint8_t> uartQueueTx; // Queue for UART transmission

HardwareSerial::HardwareSerial(int uart_nr)
{
    //  printf("HardwareSerial::HardwareSerial(%d)\n", uart_nr);

    std::cout << "HardwareSerial::HardwareSerial " << uart_nr << std::endl;
}

HardwareSerial::~HardwareSerial()
{
}

void HardwareSerial::begin(unsigned long baud)
{
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config)
{
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode)
{
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin)
{
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin, bool invert)
{
}

void HardwareSerial::end()
{
}

void HardwareSerial::updateBaudRate(unsigned long baud)
{
}

size_t HardwareSerial::setRxBufferSize(size_t size)
{
}

size_t HardwareSerial::getRxBufferSize()
{
}

bool HardwareSerial::swap()
{
}

bool HardwareSerial::swap(uint8_t tx_pin)
{
}

bool HardwareSerial::set_tx(uint8_t tx_pin)
{
}

bool HardwareSerial::pins(uint8_t tx, uint8_t rx)
{
}

int HardwareSerial::available()
{
    return static_cast<int>(uartQueueTx.size());
}

int HardwareSerial::peek()
{
}

bool HardwareSerial::hasPeekBufferAPI() const
{
}

const char *HardwareSerial::peekBuffer()
{
}

size_t HardwareSerial::peekAvailable()
{
}

void HardwareSerial::peekConsume(size_t consume)
{
}

int HardwareSerial::read()
{
    std::cout << "===========================================HardwareSerial::read " << (char)uartQueueTx.front() << ")" << std::endl;
    while (uartQueueTx.empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for 500ms if the queue is empty
    }
    uint8_t value = uartQueueTx.front();
    uartQueueTx.pop_front();
    return value;
    //  return 'c';
}

int HardwareSerial::read(char *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    /*
         size_t readCount = 0;
       while (!uartQueueTx.empty() && readCount < size) {
           buffer.push_back(uartQueueTx.front());
           uartQueueTx.pop();
           ++readCount;
       }
       return readCount;
       */
    return 0;
}

int HardwareSerial::read(uint8_t *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    return 0;
}

size_t HardwareSerial::readBytes(char *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    size_t readCount = 0;

    for (int i = 0; i < size; i++)
    {
        buffer[i] = uartQueueTx.front();
        uartQueueTx.pop_front();
        ++readCount;
    }

    return 0;
}

size_t HardwareSerial::readBytes(uint8_t *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << std::endl;
    return 0;
}

int HardwareSerial::availableForWrite()
{
}

void HardwareSerial::flush()
{
}

size_t HardwareSerial::write(uint8_t c)
{
    std::cout << __func__ << " " << __LINE__ << "  " << c << std::endl;

    std::string hack = std::to_string(c);

    char *txData = const_cast<char *>(hack.c_str());

    serialTx(txData);

    return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
    std::cout << __func__ << " " << __LINE__ << buffer << std::endl;

    serialTx((char *)buffer);

    return size;
}

HardwareSerial::operator bool() const
{
}

void HardwareSerial::setDebugOutput(bool)
{
}

bool HardwareSerial::isTxEnabled()
{
}

bool HardwareSerial::isRxEnabled()
{
}

int HardwareSerial::baudRate()
{
}

bool HardwareSerial::hasOverrun()
{
}

bool HardwareSerial::hasRxError()
{
}

void HardwareSerial::startDetectBaudrate()
{
}

unsigned long HardwareSerial::testBaudrate()
{
}

unsigned long HardwareSerial::detectBaudrate(time_t timeoutMillis)
{
}

// Define the global Serial object
HardwareSerial Serial(0);