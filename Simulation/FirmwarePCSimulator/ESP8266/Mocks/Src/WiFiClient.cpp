#include "WiFiClient.h"
/*
WiFiClient::WiFiClient()
{
}

WiFiClient::~WiFiClient()
{
}

WiFiClient::WiFiClient(const WiFiClient &)
{
}

WiFiClient &WiFiClient::operator=(const WiFiClient &)
{
}

std::unique_ptr<WiFiClient> WiFiClient::clone() const
{
    return std::make_unique<WiFiClient>(*this);
}

uint8_t WiFiClient::status()
{
}

int WiFiClient::connect(IPAddress ip, uint16_t port)
{
}

int WiFiClient::connect(const char *host, uint16_t port)
{
}

int WiFiClient::connect(const String &host, uint16_t port)
{
}

size_t WiFiClient::write(uint8_t)
{
}

size_t WiFiClient::write(const uint8_t *buf, size_t size)
{
}

size_t WiFiClient::write_P(PGM_P buf, size_t size)
{
}

[[deprecated("use stream.sendHow(client...)")]]
size_t WiFiClient::write(Stream &stream)
{
}

int WiFiClient::available()
{
}

int WiFiClient::read()
{
}

int WiFiClient::read(uint8_t *buf, size_t size)
{
}

int WiFiClient::read(char *buf, size_t size)
{
}

int WiFiClient::peek()
{
}

size_t WiFiClient::peekBytes(uint8_t *buffer, size_t length)
{
}

size_t WiFiClient::peekBytes(char *buffer, size_t length)
{
}

void WiFiClient::flush()
{
}

void WiFiClient::stop()
{
}

bool WiFiClient::flush(unsigned int maxWaitMs)
{
}

bool WiFiClient::stop(unsigned int maxWaitMs)
{
}

uint8_t WiFiClient::connected()
{
}

WiFiClient::operator bool()
{
}

IPAddress WiFiClient::remoteIP()
{
}

uint16_t WiFiClient::remotePort()
{
}

IPAddress WiFiClient::localIP()
{
}

uint16_t WiFiClient::localPort()
{
}

void WiFiClient::setLocalPortStart(uint16_t port)
{
}

int WiFiClient::availableForWrite()
{
}

void WiFiClient::stopAll()
{
}

void WiFiClient::stopAllExcept(WiFiClient *c)
{
}

void WiFiClient::keepAlive(uint16_t idle_sec, uint16_t intv_sec, uint8_t count)
{
}

bool WiFiClient::isKeepAliveEnabled() const
{
}

uint16_t WiFiClient::getKeepAliveIdle() const
{
}

uint16_t WiFiClient::getKeepAliveInterval() const
{
}

uint8_t WiFiClient::getKeepAliveCount() const
{
}

void WiFiClient::disableKeepAlive()
{
}

void WiFiClient::setDefaultNoDelay(bool noDelay)
{
}

bool WiFiClient::getDefaultNoDelay()
{
}

bool WiFiClient::getNoDelay() const
{
}

void WiFiClient::setNoDelay(bool nodelay)
{
}

void WiFiClient::setDefaultSync(bool sync)
{
}

bool WiFiClient::getDefaultSync()
{
}

bool WiFiClient::getSync() const
{
}

void WiFiClient::setSync(bool sync)
{
}

bool WiFiClient::hasPeekBufferAPI() const
{
}

size_t WiFiClient::peekAvailable()
{
}

const char *WiFiClient::peekBuffer()
{
}

void WiFiClient::peekConsume(size_t consume)
{
}

bool WiFiClient::outputCanTimeout()
{
}

bool WiFiClient::inputCanTimeout()
{
}

void WiFiClient::abort()
{
}*/