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
    python3-dbg \
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
    gdb \
    strace \
    elfutils \
    file \
    libxcb-cursor0 \
    libxcb-cursor-dev \
    libx11-xcb1 \
    libxcb-render0 \
    libxcb-shm0 \
    libxcb-xfixes0 \
    libxcb1 \
    libxrender1 \
    libxkbcommon-x11-0 \
    libxcb-icccm4 \
    libxcb-keysyms1 \
    libxcb-image0 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-sync1 \
    libxcb-xinerama0 \
    libfontconfig1 \
    libfreetype6 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Python-based tools in one step
# Create a virtual environment in /workspace/venv
RUN python3 -m venv /workspace/venv

# Activate the virtual environment and install the packages
RUN /workspace/venv/bin/pip install --upgrade pip && \
    /workspace/venv/bin/pip install \
    cpplint \
    gprof2dot \
    coverxygen \
    hpp2plantuml \
    PyQt6

# Add virtual environment binaries to the PATH
ENV PATH="/workspace/venv/bin:$PATH"

# Set the QT_PLUGIN_PATH environment variable
ENV QT_PLUGIN_PATH="/workspace/venv/lib/python3.12/site-packages/PyQt6/Qt6/plugins"

# Install CMake manually (version 3.22.0)
# RUN apt-get update && \
#    wget https://github.com/Kitware/CMake/releases/download/v3.22.0/cmake-3.22.0-linux-x86_64.sh && \
#    mkdir /opt/cmake && \
#    sh cmake-3.22.0-linux-x86_64.sh --skip-license --prefix=/opt/cmake && \
#    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
#    rm cmake-3.22.0-linux-x86_64.sh  # Clean up

# Install include-what-you-use from source
# RUN git clone https://github.com/include-what-you-use/include-what-you-use.git /usr/local/src/iwyu && \
#    cd /usr/local/src/iwyu && \
#    git checkout clang_15 && \
#    git pull && \
#    mkdir build && cd build && \
#    cmake -G "Unix Makefiles" .. && \
#    make -j $(nproc) && \
#    make install

# workaround for cppcheck html generator that needs older version 
RUN pip uninstall -y pygments && pip install pygments==2.7.4

RUN mkdir -p /workspace/build
WORKDIR /workspace/build

# Default to bash
CMD ["bash"]
