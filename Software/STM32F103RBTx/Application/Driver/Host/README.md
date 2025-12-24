# Purpouse

This is a mock library that replaces real drivers that uses low level libraries (HAL etc.). It's used to build PC based variant of the firmware used for sstel tests ans simulation. 

# Content

This folder contains:

* C++ mocks for drivers in Driver/ folder
* C++ mock for PlatformFactoryStm32.cpp
* CMake to build the C++ code into a library
* low level C library wrapper: device_under_test.py
* high level wrapper that provides easy to use API to interact with the firmware's drivers:  simulation.py

# Assumptions

* No high abstractiosn libs are included here, no GUI, test framewroks etc
* Mock only and all cpp files from Driver/ folder