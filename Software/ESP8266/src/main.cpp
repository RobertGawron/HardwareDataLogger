#include <Arduino.h>


int USR_LED_GPIO = 13;

void setup()
{
  pinMode(USR_LED_GPIO, OUTPUT);
}
void loop()
{
  // Blink LED when data is received
      digitalWrite(USR_LED_GPIO, HIGH); // Turn the LED on
      delay(500);                       // Wait for 500 milliseconds
      digitalWrite(USR_LED_GPIO, LOW);  // Turn the LED off
      delay(500);                       // Wait for 500 milliseconds
}