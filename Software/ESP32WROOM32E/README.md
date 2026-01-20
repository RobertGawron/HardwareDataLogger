# Setup

The toolchain for flashing and debugging the ESP chip is housed in a Docker container. This avoids manual host machine configuration, prevents pollution, and eliminates software version conflicts when working across multiple projects.

While the DevOps approach is theoretically platform-agnostic, we are dealing with real hardware, which creates a dependency on the host OS. This manual assumes development is done on a Windows 11 machine with Docker running on it. On Linux, the process should be much easier, although this has not been tested.

# Prerequisites

   * [Setup of the docker image for this project](../../DevOps/README.md)
   * Install usbipd-win (run as root PowerShell and type: winget install usbipd).
   * Install CH340 drivers from https://www.wch-ic.com/downloads/ch341ser_zip.html

# Configuration on WSL (on the Host side)

***This needs to be done each time the programmer is connected via USB to the host machine.***

   * Open PowerShell as Administrator. Identify your device Bus ID:
     
      ```usbipd list```
      
      Example output:
      
      ```
      PS C:\WINDOWS\system32> usbipd list
      Connected:
      BUSID  VID:PID    DEVICE                                                        STATE
      2-5    27c6:639c  Goodix MOC Fingerprint                                        Not shared
      4-1    0020:0b21  USB Audio, USB Input Device                                   Not shared
      4-2    9986:7523  USB-SERIAL CH340 (COM3)                                       Not shared
      
      Note that in above example CH340 has BUSID 4-2.
      ```

   * Attach the device (Replace 4-2 with your actual ID)
   
      ```
      usbipd bind --busid 4-3
      usbipd attach --wsl --busid 4-2
      ```

   * Load Driver in Shared Kernel, type ```wsl``` in PowerShell and run:

      ```modprobe ch341```

# Configuration inside Docker image

***This needs to be done each time the docker contained is created/started.***

   * Force the ch341 driver to recognize ID 9986:7523

      ```echo 9986 7523 > /sys/bus/usb-serial/drivers/ch341-uart/new_id```

   * Check kernel logs to ensure the driver attached:

      ```dmesg | tail -n 25```

      Look for: "ch341-uart converter now attached to ttyUSB0"

   * Manually create the file node since the file /dev/ttyUSB0 won't appear automatically:

      ```cat /sys/class/tty/ttyUSB0/dev```
      
      Output example: 
      
      ```188:0```

      Create the device node manually

      ```mknod /dev/ttyUSB0 c 188 0```

# Troubleshooting

Run this script, the LED on the board near the CH340 should blink:

```python
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
```



/// building:


cargo install ldproxy