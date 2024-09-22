# Docker

## Why?
For me, using Docker in embedded systems has a key advantage: it eliminates the need for a README filled with outdated commands for setting up the development environment. In reality, such lists are rarely kept up to date (I often forget to update them myself too!). Docker solves this problem by providing a structured list of everything you need to install to get your environment up and running. But it's more than just a list - it's code, meaning it can be verified, maintained, and reused easily.

## Prerequisites
* Install Docker. For Linux it should be simple, for Windows you need WSL installed first and some Linux image for it.

## Build Docker image
  
 ```root@robert:/mnt/c/Users/rober/Documents/HardwareDataLogger# docker build -f Docker/Dockerfile.ci  -t hardwaredatalogger .```

# Run the Docker image

```root@robert:/mnt/c/Users/rober/Documents/HardwareDataLogger# docker run -it --rm hardwaredatalogger```

You will be logged in into docker image where you can do test etc.

# How to upload Docker image to GitHub

```echo PERSONAL-TOKEN | docker login ghcr.io -u RobertGawron --password-stdin
docker tag hardwaredatalogger:latest ghcr.io/robertgawron/hardwaredatalogger:v1.1
docker push ghcr.io/robertgawron/hardwaredatalogger:v1.1```
