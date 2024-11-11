# Use an official Ubuntu base image
FROM ubuntu:24.04

# Set the working directory
WORKDIR /workspace

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install build essentials and other dependencies in one step
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gcovr \
    clang \
    clang-tidy \
    clang-tools \
    python3 \
    python3-pip \
    graphviz \
    doxygen \
    wget \
    lld \
    software-properties-common \
    llvm-15-dev \
    libclang-15-dev \
    clang-15 \
    libgtest-dev \
    libgmock-dev \
    vim \
    googletest \
    cppcheck \
    xsltproc \
    plantuml \
    libnewlib-arm-none-eabi \
    qt6-base-dev \
    python3-pyqt6 \
    python3-venv \
    llvm-15 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install Python-based tools in one step
# Create a virtual environment in /workspace/venv
RUN python3 -m venv /workspace/venv

# Activate the virtual environment and install the packages
RUN /workspace/venv/bin/pip install \
    cpplint \
    gprof2dot \
    coverxygen \
    hpp2plantuml

# Add virtual environment binaries to the PATH
ENV PATH="/workspace/venv/bin:$PATH"

# Install CMake manually (version 3.22.0)
#RUN apt-get update && \
#    wget https://github.com/Kitware/CMake/releases/download/v3.22.0/cmake-3.22.0-linux-x86_64.sh && \
#    mkdir /opt/cmake && \
#    sh cmake-3.22.0-linux-x86_64.sh --skip-license --prefix=/opt/cmake && \
#    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
#    rm cmake-3.22.0-linux-x86_64.sh  # Clean up

# Install include-what-you-use from source
#RUN git clone https://github.com/include-what-you-use/include-what-you-use.git /usr/local/src/iwyu && \
#    cd /usr/local/src/iwyu && \
#    git checkout clang_15 && \
#    git pull && \
#    mkdir build && cd build && \
#    cmake -G "Unix Makefiles" .. && \
#    make -j $(nproc) && \
#    make install

# workaround for cppcheck html generator that needs older version 
RUN pip uninstall -y pygments && pip install pygments==2.7.4

RUN pip uninstall -y pygments && \
    pip install pygments==2.7.4
    
RUN mkdir -p /workspace/build
WORKDIR /workspace/build

# Default to bash
CMD ["bash"]
