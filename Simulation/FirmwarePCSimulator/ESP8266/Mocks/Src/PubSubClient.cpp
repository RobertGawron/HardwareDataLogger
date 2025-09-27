#include "PubSubClient.h"

#include <stdint.h>
#include <inttypes.h>
#include "Client.h"
typedef int IPAddress;

PubSubClient::PubSubClient()
{
}

PubSubClient::PubSubClient(Client &client)
{
}

PubSubClient::PubSubClient(IPAddress ip, uint16_t port, Client &client)
{
}

PubSubClient::PubSubClient(IPAddress ip, uint16_t port, Client &client, Stream &)
{
}

PubSubClient::PubSubClient(IPAddress ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client &client)
{
}

PubSubClient::PubSubClient(IPAddress ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client &client, Stream &)
{
}

PubSubClient::PubSubClient(uint8_t *, uint16_t, Client &client)
{
}

PubSubClient::PubSubClient(uint8_t *, uint16_t, Client &client, Stream &)
{
}

PubSubClient::PubSubClient(uint8_t *, uint16_t, MQTT_CALLBACK_SIGNATURE, Client &client)
{
}

PubSubClient::PubSubClient(uint8_t *, uint16_t, MQTT_CALLBACK_SIGNATURE, Client &client, Stream &)
{
}

PubSubClient::PubSubClient(const char *, uint16_t, Client &client)
{
}

PubSubClient::PubSubClient(const char *, uint16_t, Client &client, Stream &)
{
}

PubSubClient::PubSubClient(const char *, uint16_t, MQTT_CALLBACK_SIGNATURE, Client &client)
{
}

PubSubClient::PubSubClient(const char *, uint16_t, MQTT_CALLBACK_SIGNATURE, Client &client, Stream &)
{
}

PubSubClient::~PubSubClient()
{
}

PubSubClient &PubSubClient::setServer(IPAddress ip, uint16_t port)
{
}

PubSubClient &PubSubClient::setServer(uint8_t *ip, uint16_t port)
{
}

PubSubClient &PubSubClient::setServer(const char *domain, uint16_t port)
{
}

PubSubClient &PubSubClient::setCallback(MQTT_CALLBACK_SIGNATURE)
{
}

PubSubClient &PubSubClient::setClient(Client &client)
{
}

PubSubClient &PubSubClient::setStream(Stream &stream)
{
}

PubSubClient &PubSubClient::setKeepAlive(uint16_t keepAlive)
{
}

PubSubClient &PubSubClient::setSocketTimeout(uint16_t timeout)
{
}

boolean PubSubClient::setBufferSize(uint16_t size)
{
}

uint16_t PubSubClient::getBufferSize()
{
}

boolean PubSubClient::connect(const char *id)
{
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass)
{
}

boolean PubSubClient::connect(const char *id, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage)
{
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage)
{
}

boolean PubSubClient::connect(const char *id, const char *user, const char *pass, const char *willTopic, uint8_t willQos, boolean willRetain, const char *willMessage, boolean cleanSession)
{
}

void PubSubClient::disconnect()
{
}

boolean PubSubClient::publish(const char *topic, const char *payload)
{
}

boolean PubSubClient::publish(const char *topic, const char *payload, boolean retained)
{
}

boolean PubSubClient::publish(const char *topic, const uint8_t *payload, unsigned int plength)
{
}

boolean PubSubClient::publish(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained)
{
}

boolean PubSubClient::publish_P(const char *topic, const char *payload, boolean retained)
{
}

boolean PubSubClient::publish_P(const char *topic, const uint8_t *payload, unsigned int plength, boolean retained)
{
}

boolean PubSubClient::beginPublish(const char *topic, unsigned int plength, boolean retained)
{
}

int PubSubClient::endPublish()
{
}

size_t PubSubClient::write(uint8_t)
{
}

size_t PubSubClient::write(const uint8_t *buffer, size_t size)
{
}

boolean PubSubClient::subscribe(const char *topic)
{
}

boolean PubSubClient::subscribe(const char *topic, uint8_t qos)
{
}

boolean PubSubClient::unsubscribe(const char *topic)
{
}

boolean PubSubClient::loop()
{
}

boolean PubSubClient::connected()
{
}

int PubSubClient::state()
{
}

int PubSubClient::status()
{
}
