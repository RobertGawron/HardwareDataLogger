# Setup Guide

## Flashing the Device
Flashing the device is performed from the host machine.

### Steps to Set Up
1. **Install Visual Studio Code:**
   - Download and install [Visual Studio Code](https://code.visualstudio.com/).

2. **Install PlatformIO Extension:**
   - Open Visual Studio Code.
   - Navigate to the Extensions Marketplace.
   - Search for and install the "PlatformIO IDE" extension.

3. **Configure PlatformIO:**
   - Open the `platformio.ini` file in your project.
   - Set the correct `upload_port` to match your device's COM port.


## Troubleshooting

### Common Issues During Flashing

1. **Cannot Connect to the COM Port:**
   - Ensure the correct COM port is set in the `platformio.ini` file.
   - Verify no other applications (e.g., serial monitors or terminal tools) are using the COM port.
   - Restart Visual Studio Code and try again.



Steps to Install PubSubClient in PlatformIO
Install the Library via CLI:

Open the PlatformIO terminal in VS Code.


pio lib install "PubSubClient"


/workspace/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/cores/esp8266/IPAddress.h: In member function 'const uint32_t& IPAddress::v4() const':

take the main class
fix all includes
provide mocks

mixed includes
C:\Users\rober\.platformio\packages\framework-arduinoespressif8266\cores\esp8266\Arduino.h

to many headers

mocking header means extra work for keep it sync


silgeton for wifi and serial


at least first level of .h files the same, inheritance

Arduino.h