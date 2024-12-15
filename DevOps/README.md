# Docker

## Why?
For me, using Docker in embedded systems has a key advantage: it eliminates the need for a README filled with outdated commands for setting up the development environment. In reality, such lists are rarely kept up to date (I often forget to update them myself too!). Docker solves this problem by providing a structured list of everything you need to install to get your environment up and running. But it's more than just a list - it's code, meaning it can be verified, maintained, and reused easily.

## Prerequisites

* Install Docker. For Linux it should be simple, for Windows you need WSL installed first and some Linux image for it.

## Build Docker image

The idea is that we we will build image once and mount the project files, so that if there is no need to rebuild contain,er unless you add other tools.

### Run the Docker image

In the main directory (HardwareDataLogger) run the command to build the image.

Build the docker image:

docker-compose build dev

Start the Docker image:

docker-compose up -d --remove-orphans

Log into the Docker image:

docker-compose exec dev bash

Additionally at the end of work:

docker-compose down --remove-orphans

## Runing stuff

## Builds the firmware

make code

## Run tests

make test

## Run static analysis

make static

# Run code coverage

cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j23 && make test -j23 && make coverage

# Run docs coverage

make docs

# Run UML generation

make uml

## Running Include what you use 

cd build

for INCLUDE_WHAT_YOU_USE:

CC="clang-10" CXX="clang++-10" cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use ../Software

for all the rest:

cmake ..


# Building and running Firmware PC Simulation

* Launch Docker as explained in the previous steps.
* Build the firmware in the PC variant:

cd /workspace/build/ && cmake .. && make -j24

* Start the simulation:

cd /workspace/Simulation/FirmwarePCSimulator/ && python3 main.py

* all at once:

cd /workspace/build/ && cmake .. && make -j24 && cd /workspace/Simulation/FirmwarePCSimulator/ && python3 main.py


### Troubleshooting:
The simulation is a desktop application that runs in Docker. Docker needs to be configured to display the simulation window. To test this, you can temporarily install some X11 applications and run them:

apt-get update && apt-get install -y x11-apps
xclock

If a small window with a clock is visible, it means everything is set up correctly.

Note: If using Windows, [MobaXterm](https://mobaxterm.mobatek.net/download-home-edition.html) (or another tool capable of displaying X11 windows) is required. The Visual Studio terminal will not work.

# Pytest

cd /workspace/build/ && cmake .. && make -j24

cd /workspace/Test/SystemTests
python3 -m venv /workspace/venv
pytest test_display.py -s  --html=report.html


after:
cd /workspace/build/ && cmake .. && make -j24 && cd /workspace/Test/SystemTests && pytest test_display.py -s  --html=report.html




