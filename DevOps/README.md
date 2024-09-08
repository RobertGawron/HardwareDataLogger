# Docker

## Why?
For me, using Docker in embedded systems has a key advantage: it eliminates the need for a README filled with outdated commands for setting up the development environment. In reality, such lists are rarely kept up to date (I often forget to update them myself too!). Docker solves this problem by providing a structured list of everything you need to install to get your environment up and running. But it's more than just a list - it's code, meaning it can be verified, maintained, and reused easily.



## Prerequisites

* Install Docker. For Linux it should be simple, for Windows you need WSL installed first and some Linux image for it.

## Build Docker image

The idea is that we we will build image once and mount the project files, so that if there is no need to rebuild contain,er unless you add other tools.

### Run the Docker image

In the main directory (HardwareDataLogger) run the command to build the image.


docker-compose build dev
docker-compose up -d

docker-compose exec dev bash

docker-compose down --remove-orphans


cd build

for INCLUDE_WHAT_YOU_USE:

CC="clang-10" CXX="clang++-10" cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use ../Software

for all the rest:

cmake ..