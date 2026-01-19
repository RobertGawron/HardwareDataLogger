# Setup

The toolchain for flashing and debugging the ESP chip is housed in a Docker container. This avoids manual host machine configuration, prevents pollution, and eliminates software version conflicts when working across multiple projects.

# Prerequisites

    * Windows 10/11 with WSL2 enabled.
    * Docker Desktop.
    * usbipd-win installed (via PowerShell: winget install usbipd).

# Instalation

Download and install drivers from https://www.wch-ic.com/downloads/ch341ser_zip.html

# Configuration on WSL (on the Host side)

THis need sto be done each time the programmer is connected via USB to the host machine.

* Open PowerShell as Administrator. Identify your device Bus ID and attach it to the WSL VM.

```usbipd list```

Example output:

PS C:\WINDOWS\system32> usbipd list
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
2-5    27c6:639c  Goodix MOC Fingerprint                                        Not shared
4-1    0020:0b21  USB Audio, USB Input Device                                   Not shared
4-2    9986:7523  USB-SERIAL CH340 (COM3)                                       Not shared

Note that in above example CH340 has BUSID 4-2.

# Attach the device (Replace 4-2 with your actual ID)

usbipd attach --wsl --busid 4-2

Load Driver in Shared Kernel, type wsl in PowerShell and run:

modprobe ch341

# Configuration inside Docker image


Force the ch341 driver to recognize ID 9986:7523

echo 9986 7523 > /sys/bus/usb-serial/drivers/ch341-uart/new_id

2. Verify detection:
Check kernel logs to ensure the driver attached:


dmesg | tail -n 10

# Look for: "ch341-uart converter now attached to ttyUSB0"

3. Manually create the file node:
Since the file /dev/ttyUSB0 won't appear automatically:

cat /sys/class/tty/ttyUSB0/dev
# Output example: 188:0

# Create the device node manually
mknod /dev/ttyUSB0 c 188 0


Run this script, the LED on the board near the CH340 should blink:


import serial
import time

# Initialize connection
ser = serial.Serial('/dev/ttyUSB0', 9600)
print("Connected to /dev/ttyUSB0")

# Toggle RTS (Request to Send)
print("RTS ON")
ser.rts = True
time.sleep(1)
print("RTS OFF")
ser.rts = False

# Toggle DTR (Data Terminal Ready)
print("DTR ON")
ser.dtr = True
time.sleep(1)
print("DTR OFF")
ser.dtr = False

ser.close()