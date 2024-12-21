# ESP8266MOD (WiFi interface)

### Usage

Docker
on host machine sudo apt install usbutils


/workspace/Software/STM32F103RBTx
TODO


prospector --output-format pylint /workspace/Software/ESP8266MOD/ > /workspace/build/BuildArtifacts/ESP8266MOD_report.pylint
prospector --output-format pylint /workspace/Test/System/ > /workspace/build/BuildArtifacts/System_report.pylint
prospector --output-format pylint /workspace/Simulation/FirmwarePCSimulator/ > /workspace/build/BuildArtifacts/FirmwarePCSimulator_report.pylint

junit2html -f  /workspace/build/BuildArtifacts/ESP8266MOD_report.pylint -o /workspace/build/BuildArtifacts/PythonStaticAnalysis/ESP8266MOD_report.html && junit2html -f  /workspace/build/BuildArtifacts/System_report.pylint -o /workspace/build/BuildArtifacts/PythonStaticAnalysis/System_report.html && junit2html -f  /workspace/build/BuildArtifacts/FirmwarePCSimulator_report.pylint -o /workspace/build/BuildArtifacts/PythonStaticAnalysis/FirmwarePCSimulator_report.html


mkdir /workspace/build/BuildArtifacts/PythonStaticAnalysis/








-------------------------------------------
                 rst          flash        |
                                          |

board                                                            


flash all time 
rst once





2. Verify USB Device Connection on Windows
Since WSL maps serial ports from Windows, verify the COM port on Windows:

Open Device Manager in Windows.
Expand Ports (COM & LPT) and look for your ESP device (e.g., USB Serial Device (COMX)).
Note the COM port (e.g., COM3).
3. Map Windows COM Port to WSL
WSL maps Windows COM ports as /dev/ttyS*. Use the following mapping:

COM1 → /dev/ttyS1
COM2 → /dev/ttyS2
COM3 → /dev/ttyS3


in shell of windows:

winget install usbipd


on host:

wsl --shutdown
wsl

open new shell wiwnods as root

C:\Users\rober>usbipd list
Connected:
BUSID  VID:PID    DEVICE                                                        STATE
2-1    10c4:ea60  Silicon Labs CP210x USB to UART Bridge (COM3)                 Not shared
2-3    046d:c52b  Logitech USB Input Device, USB Input Device                   Not shared
2-5    27c6:639c  Goodix MOC Fingerprint                                        Not shared
2-6    0c45:6739  Integrated Webcam                                             Not shared
2-10   8087:0033  Intel(R) Wireless Bluetooth(R)                                Not shared


usbipd bind --busid 2-1


root@robert:/mnt/c/Documents and Settings/rober/Documents# chmod 666 /dev/ttyS3

modify docker compose

docker-compose build dev && docker-compose up -d --remove-orphans && docker-compose exec dev bash

on host machine
root@robert:/mnt/c/Documents and Settings/rober/Documents# ls -l /dev/ttyS3


====
root@6c8650bd859e:/workspace/Software/ESP8266MOD# ll  /dev/ttyS3
crw-rw-rw- 1 root dialout 4, 67 Dec 21 15:43 /dev/ttyS3

on host 

root@robert:/mnt/c/Documents and Settings/rober/Documents#  ll  /dev/ttyS3
crw-rw-rw- 1 root dialout 4, 67 Dec 21 16:41 /dev/ttyS3
====

on host 

root@robert:/mnt/c/Documents and Settings/rober/Documents# lsof /dev/ttyS3
root@robert:/mnt/c/Documents and Settings/rober/Documents# 

on docker;

root@6c8650bd859e:/workspace/Software/ESP8266MOD# lsof /dev/ttyS3
root@6c8650bd859e:/workspace/Software/ESP8266MOD# 

====

cd /workspace/Software/ESP8266MOD/ && python3 -m venv /workspace/venv



esptool.py --port /dev/ttyS3 erase_flash



=====================

on host:

esptool.py --port /dev/ttyUSB0 erase_flash
