# PC Simulator for firmware

## Why using a simulator?

The reasons for using a simulator are explained in the main [README](../../README.md).

## Architecture

Simulation consists of:
- Firmware (.so file)
  - High-level logic is used as-is, without modification for simulation mode. This code is located in the [Application/BusinessLogic/](../../Software/STM32F103RBTx/Application/BusinessLogic) and [Application/Device/](../../Software/STM32F103RBTx/Application/Device) folders within the firmware directory.
  - The [Stub folder](./Stub) replaces low-level classes (Driver folder within the firmware directory).
- device_under_test.py: Loads the firmware .so file and provides a Python API interface.
- hmi.py: Provides the graphical interface.

# Remarks

* Do Not Inherit from [Firmware Driver Headers](../Software/STM32F103RBTx/Application/Driver), as they include many HAL dependencies that are difficult to stub and not needed in simulation mode. Instead, use driver interface headers and create stub drivers based on inheritance from those interfaces. The only exception to this rule is the Display driver.

* No Stubs for [Business Logic](../../Software/STM32F103RBTx/Application/BusinessLogic) or [Device](../../Software/STM32F103RBTx/Application/Device) Layers. A stub in these layers suggests the classes are too tightly coupled with low-level code, indicating a need to refactor the firmware for better separation of concerns.

## How to use it

* Build the Firmware in simulation mode:

  ```TODO```
* Build and run the Docker Container:

  ```TODO```
* Once inside the Docker container, navigate to the simulation directory:

  ```TODO```
* Execute the simulation script:

  ```python3 hmi.py```


## Remarks

TODO: synthesis into the above chapter.

- Doker
- MobaXterm (when running on Windows) https://mobaxterm.mobatek.net/download-home-edition.html

If you're using Windows, you need MobaXterm, if you are using Linux you (probably, I didn't test it) can just use a terminal.

Simulation is a graphic app, configure the console so that it is able to launch them:

```export DISPLAY=:0```

Build the image:

```docker build -t hmi .```

Start the image:

```docker run -it --rm  -e DISPLAY=$DISPLAY  -v /tmp/.X11-unix:/tmp/.X11-unix hmi```

Note that console has changed it's prompt.

Now launch the simulation:

```python3 hmi.py```

Alternatively if you don't like Docker, you can look on the Docker file, it contains the lists of packages that need to be installed in order to launch the simulation.
