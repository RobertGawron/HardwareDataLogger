
#include <Arduino.h>
#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

constexpr int USER_LED_GPIO = 13;
constexpr int BAUD_RATE = 115200;
constexpr size_t BUFFER_SIZE = 100;
constexpr size_t OUTBUFFER_SIZE = 256;
constexpr int PROCESSING_DELAY = 500;

void setup()
{
  pinMode(USER_LED_GPIO, OUTPUT);

  Serial.begin(BAUD_RATE);
  Serial.print("Hello from ESP");
}

void loop()
{
  if (Serial.available() > 0)
  {
    // Light up the LED during the processing just for test
    digitalWrite(USER_LED_GPIO, HIGH);

    int incomingData = Serial.read();                          // Read the incoming data
    uint8_t packetLength = static_cast<uint8_t>(incomingData); // Ensure proper conversion

    // Read package
    char buffer[BUFFER_SIZE];
    Serial.readBytes(buffer, packetLength);

    char outbuffer[OUTBUFFER_SIZE];
    int pos = 0; // Current position in the buffer

    pos += snprintf(outbuffer + pos, sizeof(outbuffer) - pos, "I got from STM32: ");

    for (uint8_t i = 0; i < packetLength; i++)
    {
      pos += snprintf(outbuffer + pos, sizeof(outbuffer) - pos, "%c", buffer[i]);
    }

    Serial.println(outbuffer);

    delay(PROCESSING_DELAY); // Simulate processing

    digitalWrite(USER_LED_GPIO, LOW);

    delay(PROCESSING_DELAY);
  }
}

/*
#include <Arduino.h>
#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wi-Fi and MQTT Broker Settings
const char *ssid = "Your_SSID";
const char *password = "Your_PASSWORD";
const char *mqtt_server = "broker.hivemq.com"; // Example public MQTT broker
const int mqtt_port = 1883;
const char *mqtt_topic = "esp8266/test";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      Serial.println("connected");
      // Subscribe or resubscribe to topics
      client.subscribe(mqtt_topic);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Handle incoming messages here
  if (String(topic) == mqtt_topic)
  {
    Serial.println("Processing MQTT message...");
  }
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  // Publish a message periodically
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 2000)
  {
    lastMsg = now;
    String msg = "Hello from ESP8266 at ";
    msg += String(now);
    client.publish(mqtt_topic, msg.c_str());
    Serial.println("Message published: " + msg);
  }
}
*/
