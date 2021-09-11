int USR_LED_GPIO = 13;

void setup() 
{
  pinMode (USR_LED_GPIO, OUTPUT);
}
void loop()
{
  digitalWrite(USR_LED_GPIO, HIGH);
  delay(1000);
  digitalWrite(USR_LED_GPIO, LOW);
  delay(1000);
}
