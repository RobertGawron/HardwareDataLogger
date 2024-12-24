/*
  WiFiClient.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino.  All right reserved.

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

  Modified by Ivan Grokhotkov, December 2014 - esp8266 support
*/
#if 0
#ifndef wificlient_h
#define wificlient_h

#include <memory>
#include "Arduino.h"
#include "Print.h"
#include "Client.h"
//  #include "IPAddress.h"
//  #include "include/slist.h"

#ifndef TCP_MSS
#define TCP_MSS 1460 // lwip1.4
#endif

#define WIFICLIENT_MAX_PACKET_SIZE TCP_MSS
#define WIFICLIENT_MAX_FLUSH_WAIT_MS 300

#define TCP_DEFAULT_KEEPALIVE_IDLE_SEC 7200   // 2 hours
#define TCP_DEFAULT_KEEPALIVE_INTERVAL_SEC 75 // 75 sec
#define TCP_DEFAULT_KEEPALIVE_COUNT 9         // fault after 9 failures

class ClientContext;
class WiFiServer;

// ROBERT: my hacks ===============================================================================
typedef int IPAddress;
// typedef std::string String;
typedef int Stream;

// typedef int PGM_P;
#include <string>

// for main:
/*
// GPIO FUNCTIONS
#define INPUT 0x00
#define INPUT_PULLUP 0x02
#define INPUT_PULLDOWN_16 0x04 // PULLDOWN only possible for pin16
#define OUTPUT 0x01
#define OUTPUT_OPEN_DRAIN 0x03
#define WAKEUP_PULLUP 0x05
#define WAKEUP_PULLDOWN 0x07
#define SPECIAL 0xF8 // defaults to the usable BUSes uart0rx/tx uart1tx and hspi
*/
typedef enum
{
  WL_NO_SHIELD = 255, // for compatibility with WiFi Shield library
  WL_IDLE_STATUS = 0,
  WL_NO_SSID_AVAIL = 1,
  WL_SCAN_COMPLETED = 2,
  WL_CONNECTED = 3,
  WL_CONNECT_FAILED = 4,
  WL_CONNECTION_LOST = 5,
  WL_WRONG_PASSWORD = 6,
  WL_DISCONNECTED = 7
} wl_status_t;
/*
#define HIGH 0x1
#define LOW 0x0
*/
// #include "mils.h"

#include "Client.h"
// ROBERT: my hacks ===============================================================================

class WiFiClient : public Client
{
public:
  WiFiClient();

  virtual ~WiFiClient();

  WiFiClient(const WiFiClient &);

  WiFiClient &operator=(const WiFiClient &);

  virtual std::unique_ptr<WiFiClient> clone() const;

  virtual uint8_t status();

  virtual int connect(IPAddress ip, uint16_t port);

  virtual int connect(const char *host, uint16_t port);

  virtual int connect(const String &host, uint16_t port);

  virtual size_t write(uint8_t);

  virtual size_t write(const uint8_t *buf, size_t size);

  virtual size_t write_P(PGM_P buf, size_t size);

  [[deprecated("use stream.sendHow(client...)")]]
  size_t write(Stream &stream);

  virtual int available();

  virtual int read();

  virtual int read(uint8_t *buf, size_t size);

  int read(char *buf, size_t size);

  virtual int peek();

  virtual size_t peekBytes(uint8_t *buffer, size_t length);

  size_t peekBytes(char *buffer, size_t length);

  virtual void flush();

  virtual void stop();

  bool flush(unsigned int maxWaitMs);

  bool stop(unsigned int maxWaitMs);

  virtual uint8_t connected();

  virtual operator bool();

  virtual IPAddress remoteIP();

  virtual uint16_t remotePort();

  virtual IPAddress localIP();

  virtual uint16_t localPort();

  static void setLocalPortStart(uint16_t port);

  int availableForWrite();

  friend class WiFiServer;

  static void stopAll();

  static void stopAllExcept(WiFiClient *c);

  void keepAlive(
      uint16_t idle_sec = TCP_DEFAULT_KEEPALIVE_IDLE_SEC,
      uint16_t intv_sec = TCP_DEFAULT_KEEPALIVE_INTERVAL_SEC,
      uint8_t count = TCP_DEFAULT_KEEPALIVE_COUNT);

  bool isKeepAliveEnabled() const;

  uint16_t getKeepAliveIdle() const;

  uint16_t getKeepAliveInterval() const;

  uint8_t getKeepAliveCount() const;

  void disableKeepAlive();

  static void setDefaultNoDelay(bool noDelay);

  static bool getDefaultNoDelay();

  bool getNoDelay() const;

  void setNoDelay(bool nodelay);

  static void setDefaultSync(bool sync);

  static bool getDefaultSync();

  bool getSync() const;

  void setSync(bool sync);

  virtual bool hasPeekBufferAPI() const;

  virtual size_t peekAvailable();

  virtual const char *peekBuffer();

  virtual void peekConsume(size_t consume);

  virtual bool outputCanTimeout();

  virtual bool inputCanTimeout();

  void abort();
};

#endif
#endif