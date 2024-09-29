# Use an official Python runtime as a parent image
FROM ubuntu:24.04

# Set environment variable for non-interactive install
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    python3-pip \
    python3-pyqt6 \
    && apt-get clean



# Install PyQt6 and OpenCV
#RUN pip3 install PyQt6

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Make port 80 available to the world outside this container
EXPOSE 80

# Run the application
CMD ["bash"]