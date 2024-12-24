#include "ESP8266WiFi.h"
#include "Client.h"

int ESP8266WiFiClass::connect(IPAddress ip, uint16_t port)
{
    return 0;
}

int ESP8266WiFiClass::connect(const char *host, uint16_t port)
{
    return 0;
}

size_t ESP8266WiFiClass::write(uint8_t)
{
    return 0;
}

size_t ESP8266WiFiClass::write(const uint8_t *buf, size_t size)
{
    return 0;
}

int ESP8266WiFiClass::available()
{
    return 0;
}

int ESP8266WiFiClass::read()
{
    return 0;
}

int ESP8266WiFiClass::read(uint8_t *buf, size_t size)
{
    return 0;
}

int ESP8266WiFiClass::peek()
{
    return 0;
}

void ESP8266WiFiClass::flush()
{
    // Empty implementation
}

void ESP8266WiFiClass::stop()
{
    // Empty implementation
}

uint8_t ESP8266WiFiClass::connected()
{
    return 0;
}

ESP8266WiFiClass::operator bool()
{
    return false;
}

ESP8266WiFiClass WiFi;