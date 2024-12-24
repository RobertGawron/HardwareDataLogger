
#include <Arduino.h>
#include <HardwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int USR_LED_GPIO = 13;

void setup()
{
  pinMode(USR_LED_GPIO, OUTPUT);

  Serial.begin(115200);
  Serial.print("Hello from ESP");
}

void loop()
{
  if (Serial.available() > 0)
  {
    // we light up the led during the processing just for test
    digitalWrite(USR_LED_GPIO, HIGH);

    uint8_t packetLength = Serial.read(); // Read the incoming data

    // read package
    char buffer[100];
    Serial.readBytes(buffer, packetLength);

    char outbuffer[256];
    int pos = 0; // Current position in the buffer

    pos += snprintf(outbuffer + pos, sizeof(outbuffer) - pos, "I got from STM32: ");

    for (int i = 0; i < packetLength; i++)
    {
      pos += snprintf(outbuffer + pos, sizeof(outbuffer) - pos, "%c", buffer[i]);
    }

    Serial.println(outbuffer);

    delay(500); // Delay to simulate processing

    digitalWrite(USR_LED_GPIO, LOW);

    delay(500); // TODO
  }
}