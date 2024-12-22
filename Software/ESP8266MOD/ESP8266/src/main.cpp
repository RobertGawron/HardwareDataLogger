#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library (not strictly necessary for serial communication, but typically included for ESP8266 projects)

unsigned long previousMillis = 0; // Stores the last time the message was sent
const long interval = 2000;       // Interval at which to send the message (in milliseconds)

int USR_LED_GPIO = 13;

void setup()
{
  pinMode(USR_LED_GPIO, OUTPUT);
  Serial.begin(115200); // Start the serial communication at 115200 baud rate
}
void loop()
{
  if (Serial.available() > 0)
  {                                    // Check if data is available to read from the serial port
    char receivedChar = Serial.read(); // Read the incoming data
    if (receivedChar == '\n')
    {

      // Blink LED when data is received
      digitalWrite(USR_LED_GPIO, HIGH); // Turn the LED on
      delay(500);                       // Wait for 500 milliseconds
      digitalWrite(USR_LED_GPIO, LOW);  // Turn the LED off
      delay(500);                       // Wait for 500 milliseconds

      // Optionally, echo back the received data to the STM32
      Serial.print("receivedData");
    }
  }
}
