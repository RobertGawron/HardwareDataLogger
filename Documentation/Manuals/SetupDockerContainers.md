## Why?

For me, using Docker in embedded systems has a key advantage: it eliminates the need for a README filled with outdated commands for setting up the development environment. In reality, such lists are rarely kept up to date (I often forget to update them myself too!). Docker solves this problem by providing a structured list of everything you need to install to get your environment up and running. But it's more than just a list - it's code, meaning it can be verified, maintained, and reused easily.

## Prerequisites

* Install Docker. For Linux, this should be straightforward. For Windows, you need to install WSL first and set up a Linux image.

## Docker Image for Firmware Development

### Build the Image

In the main directory (HardwareDataLogger), run the following command to build the image:

```
docker-compose build dev
```

### Running the Docker Image

Start the Docker image:

```
docker-compose up -d --remove-orphans
```

Log into the Docker image:

```
docker-compose exec dev bash
```

When finished, shut down the Docker container:

```
docker-compose down --remove-orphans
```

## Docker Image for Raspberry Pi Development

### Build the Image

In the main directory (HardwareDataLogger), run the following command to build the image:

```
docker-compose build raspberry-logger
```

### Running the Docker Image

Start the Docker image:

```
docker-compose up raspberry-logger -d
```

Log into the Docker image:

```
docker-compose exec raspberry-logger bash
```

### Cross-Platform Usage

For cross-platform usage, use Buildx to produce a multi-arch image.
