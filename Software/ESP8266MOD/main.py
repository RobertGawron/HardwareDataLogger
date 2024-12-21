from machine import Pin
import time
import sys

# Define the GPIO pin for the user LED
USR_LED_GPIO = 13
led = Pin(USR_LED_GPIO, Pin.OUT)

# Set up serial communication
sys.stdin = open('/dev/tty', 'r')  # Redirect stdin for serial reading
sys.stdout = open('/dev/tty', 'w')  # Redirect stdout for serial writing

def blink_led():
    """Blink the LED."""
    led.on()
    time.sleep(0.5)  # Wait for 500 milliseconds
    led.off()
    time.sleep(0.5)  # Wait for 500 milliseconds

while True:
    try:
        # Check if data is available from the serial port
        if sys.stdin.readable():
            received_char = sys.stdin.read(1)  # Read a single character
            
            if received_char == '\n':
                # Blink LED when data is received
                blink_led()
                
                # Optionally, echo back the received data
                sys.stdout.write("receivedData\n")
                sys.stdout.flush()
    except Exception as e:
        print("Error:", e)
        time.sleep(1)
