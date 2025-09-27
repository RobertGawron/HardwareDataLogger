#if 0

#ifndef ISerialInterface_h
#define ISerialInterface_h

#include <inttypes.h>
#include <string>
// #include "WString.h"
#include "HardwareSerial.h"
// #include <stdio.h>
// #include <iostream>
/*
enum SerialConfig
{
    SERIAL_5N1,
    SERIAL_6N1,
    SERIAL_7N1,
    SERIAL_8N1,
    SERIAL_5N2,
    SERIAL_6N2,
    SERIAL_7N2,
    SERIAL_8N2,
    SERIAL_5E1,
    SERIAL_6E1,
    SERIAL_7E1,
    SERIAL_8E1,
    SERIAL_5E2,
    SERIAL_6E2,
    SERIAL_7E2,
    SERIAL_8E2,
    SERIAL_5O1,
    SERIAL_6O1,
    SERIAL_7O1,
    SERIAL_8O1,
    SERIAL_5O2,
    SERIAL_6O2,
    SERIAL_7O2,
    SERIAL_8O2,
};

enum SerialMode
{
    SERIAL_FULL,
    SERIAL_RX_ONLY,
    SERIAL_TX_ONLY
};*/

// class HardwareSerial : public Stream
class ISerialInterface //: public Print

{
public:
    inline ISerialInterface(int /*uart_nr*/) {}
    inline virtual ~ISerialInterface() = default;

    virtual void begin(unsigned long baud) = 0;
    virtual void begin(unsigned long baud, SerialConfig config) = 0;
    virtual void begin(unsigned long baud, SerialConfig config, SerialMode mode) = 0;
    virtual void begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin) = 0;

    virtual void begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin, bool invert) = 0;

    virtual void end() = 0;

    virtual void updateBaudRate(unsigned long baud) = 0;

    virtual size_t setRxBufferSize(size_t size) = 0;
    virtual size_t getRxBufferSize() = 0;

    virtual bool swap() = 0;
    virtual bool swap(uint8_t tx_pin) = 0; // toggle between use of GPIO13/GPIO15 or GPIO3/GPIO(1/2) as RX and TX

    /*
     * Toggle between use of GPIO1 and GPIO2 as TX on UART 0.
     * Note: UART 1 can't be used if GPIO2 is used with UART 0!
     */
    virtual bool set_tx(uint8_t tx_pin) = 0;

    /*
     * UART 0 possible options are (1, 3), (2, 3) or (15, 13)
     * UART 1 allows only TX on 2 if UART 0 is not (2, 3)
     */
    virtual bool pins(uint8_t tx, uint8_t rx) = 0;

    virtual int available() = 0;

    virtual int peek() = 0;

    virtual bool hasPeekBufferAPI() const = 0;

    // return a pointer to available data buffer (size = available())
    // semantic forbids any kind of read() before calling peekConsume()
    virtual const char *peekBuffer() = 0;

    // return number of byte accessible by peekBuffer()
    virtual size_t peekAvailable() = 0;
    // consume bytes after use (see peekBuffer)
    virtual void peekConsume(size_t consume) = 0;

    virtual int read() = 0;
    // ::read(buffer, size): same as readBytes without timeout
    virtual int read(char *buffer, size_t size) = 0;
    virtual int read(uint8_t *buffer, size_t size) = 0;
    virtual size_t readBytes(char *buffer, size_t size) = 0;
    virtual size_t readBytes(uint8_t *buffer, size_t size) = 0;
    virtual int availableForWrite() = 0;
    virtual void flush() = 0; // wait for all outgoing characters to be sent, output buffer is empty after this call
    virtual size_t write(uint8_t c) = 0;
    virtual size_t write(const uint8_t *buffer, size_t size) = 0;

    operator bool() const;
    virtual void setDebugOutput(bool) = 0;
    virtual bool isTxEnabled() = 0;
    virtual bool isRxEnabled() = 0;
    virtual int baudRate() = 0;
    virtual bool hasOverrun() = 0;

    virtual bool hasRxError() = 0;

    virtual void startDetectBaudrate() = 0;

    virtual unsigned long testBaudrate() = 0;

    virtual unsigned long detectBaudrate(time_t timeoutMillis) = 0;
};

// extern virtual void serialEventRun() __attribute__((weak)) = 0;

#endif


#endif