# Use an official Ubuntu base image
FROM ubuntu:20.04

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
    llvm-10-dev \
    libclang-10-dev \
    clang-10 \
    libgtest-dev \
    libgmock-dev \
    vim \
    googletest \
    cppcheck \
    xsltproc \
    plantuml \
    libnewlib-arm-none-eabi \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install Python-based tools in one step
RUN pip3 install \
    cpplint \
    gprof2dot \
    coverxygen \
    hpp2plantuml

# Install CMake manually (version 3.22.0)
RUN apt-get update && \
    wget https://github.com/Kitware/CMake/releases/download/v3.22.0/cmake-3.22.0-linux-x86_64.sh && \
    mkdir /opt/cmake && \
    sh cmake-3.22.0-linux-x86_64.sh --skip-license --prefix=/opt/cmake && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
    rm cmake-3.22.0-linux-x86_64.sh  # Clean up

# Install include-what-you-use from source
RUN git clone https://github.com/include-what-you-use/include-what-you-use.git /usr/local/src/iwyu && \
    cd /usr/local/src/iwyu && \
    git checkout clang_10 && \
    git pull && \
    mkdir build && cd build && \
    cmake -G "Unix Makefiles" .. && \
    make -j $(nproc) && \
    make install

# workaround for cppcheck html generator that needs older version 
RUN pip uninstall -y pygments && pip install pygments==2.7.4

RUN pip uninstall -y pygments && \
    pip install pygments==2.7.4
    
RUN mkdir -p /workspace/build
WORKDIR /workspace/build

# Default to bash
CMD ["bash"]
