## Prerequisites

* [Install Docker and log into the container.](./SetupDockerContainers.md)
* Install CubeMX
* Install VisualStudioCode
* Generate the project in STM32CubeMX, which will create the CMake setup.
* Configure the STM32 VS Code Extension.

# Building and Running Firmware PC Simulation

### Build the Firmware (PC Variant)

```
cd /workspace/build/ && cmake .. && make -j24
```

### Start the Simulation

```
cd /workspace/Simulation/FirmwarePCSimulator/ && python3 main.py
```

### All-in-One Command

```
cd /workspace/build/ && cmake .. && make -j24 && cd /workspace/Simulation/FirmwarePCSimulator/ && python3 main.py
```

### Troubleshooting tunneling GUI to host environment

The simulation is a desktop application that runs in Docker. Docker needs to be configured to display the simulation window. To test this, you can temporarily install some X11 applications and run them:

```
apt-get update && apt-get install -y x11-apps
xclock
```

If a small window with a clock is visible, it means everything is set up correctly.

**Note:** If using Windows, [MobaXterm](https://mobaxterm.mobatek.net/download-home-edition.html) (or another tool capable of displaying X11 windows) is required. The Visual Studio terminal will not work.

## Troubleshooting core dumps

### Check if Core Dumps Are Enabled

Core dumps might be disabled by default on your system. Check the current core dump settings using:

```
ulimit -c
```

If it shows `0`, core dumps are disabled. Enable core dumps by running:

```
ulimit -c unlimited
```

On WSL (Docker runs in Windows), disable `wsl-capture-crash` for Core Dumps:

```
echo "/tmp/core.%e.%p" | tee /proc/sys/kernel/core_pattern
```

### Debug Core Dumps

```
gdb /workspace/venv/bin/python3 /tmp/core.python3.2430
```