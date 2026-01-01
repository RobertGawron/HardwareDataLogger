# Multi-stage Dockerfile with Latest GCC & LLVM for ARM and Native Linux
FROM ubuntu:24.04 AS base

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Set the working directory
WORKDIR /workspace

# ---------------------------------------------------------------------
# STAGE 1: System dependencies & Build Tools
# ---------------------------------------------------------------------
FROM base AS build-deps

# Install base dependencies and build requirements
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    xz-utils \
    software-properties-common \
    ca-certificates \
    unzip \
    gnupg \
    lsb-release \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    flex \
    bison \
    texinfo \
    && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# Build GCC 15 from source (experimental C++26 support)
# ---------------------------------------------------------------------
FROM build-deps AS gcc-builder

ARG GCC_SNAPSHOT_DATE=20260117

# Download GCC 15 snapshot
RUN mkdir -p /tmp/gcc-build && cd /tmp/gcc-build && \
    wget -q "https://gcc.gnu.org/pub/gcc/snapshots/LATEST-15/gcc-15-${GCC_SNAPSHOT_DATE}.tar.xz" && \
    tar -xf gcc-15-${GCC_SNAPSHOT_DATE}.tar.xz && \
    rm gcc-15-${GCC_SNAPSHOT_DATE}.tar.xz

# Configure and build GCC 15

RUN apt-get update && apt-get install -y --no-install-recommends \
    zlib1g-dev \
    libisl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y --no-install-recommends \
    file \
    && rm -rf /var/lib/apt/lists/*
    
# This will take 30-60 minutes depending on CPU
RUN cd /tmp/gcc-build/gcc-15-${GCC_SNAPSHOT_DATE} && \
    ./contrib/download_prerequisites && \
    cd /tmp/gcc-build && \
    mkdir build && cd build && \
    ../gcc-15-${GCC_SNAPSHOT_DATE}/configure \
        --prefix=/opt/gcc-15 \
        --enable-languages=c,c++ \
        --disable-multilib \
        --disable-bootstrap \
        --enable-checking=release \
        --with-system-zlib && \
    make -j$(nproc) && \
    make install && \
    cd / && rm -rf /tmp/gcc-build

# ---------------------------------------------------------------------
# STAGE 2: System dependencies with GCC 15
# ---------------------------------------------------------------------
FROM base AS system-deps

# Copy GCC 15 from builder stage
COPY --from=gcc-builder /opt/gcc-15 /opt/gcc-15

# Install runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    xz-utils \
    software-properties-common \
    ca-certificates \
    unzip \
    gnupg \
    lsb-release \
    libgmp10 \
    libmpfr6 \
    libmpc3 \
    && rm -rf /var/lib/apt/lists/*

# Set up alternatives for GCC 15
RUN update-alternatives --install /usr/bin/gcc gcc /opt/gcc-15/bin/gcc 100 \
    --slave /usr/bin/g++ g++ /opt/gcc-15/bin/g++ \
    --slave /usr/bin/gcov gcov /opt/gcc-15/bin/gcov \
    --slave /usr/bin/gcc-ar gcc-ar /opt/gcc-15/bin/gcc-ar \
    --slave /usr/bin/gcc-ranlib gcc-ranlib /opt/gcc-15/bin/gcc-ranlib

# Add GCC 15 to library path
ENV LD_LIBRARY_PATH="/opt/gcc-15/lib64:${LD_LIBRARY_PATH}"

# ---------------------------------------------------------------------
# Install Latest LLVM/Clang (v20) for x86_64 Linux - C++26 Support
# ---------------------------------------------------------------------
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    add-apt-repository -y "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-20 main" && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    clang-20 \
    clang++-20 \
    clang-tools-20 \
    clang-format-20 \
    clang-tidy-20 \
    lld-20 \
    lldb-20 \
    libc++-20-dev \
    libc++abi-20-dev \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-20 100 \
    --slave /usr/bin/clang++ clang++ /usr/bin/clang++-20 \
    --slave /usr/bin/clang-format clang-format /usr/bin/clang-format-20 \
    --slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-20 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# Install Latest ARM GNU Toolchain (15.2.Rel1) for arm-none-eabi
# ---------------------------------------------------------------------
ARG ARM_TOOLCHAIN_VERSION=15.2.rel1
ARG ARM_TOOLCHAIN_URL=https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_TOOLCHAIN_VERSION}/binrel/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz

RUN wget -q ${ARM_TOOLCHAIN_URL} && \
    tar -xJf arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz -C /opt/ && \
    rm arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz && \
    ln -s /opt/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi /opt/arm-toolchain

# ---------------------------------------------------------------------
# Install Development Tools
# ---------------------------------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    gcovr \
    python3 \
    python3-pip \
    python3-venv \
    graphviz \
    doxygen \
    libgtest-dev \
    libgmock-dev \
    cppcheck \
    ninja-build \
    gdb \
    gdb-multiarch \
    openocd \
    usbutils \
    stlink-tools \
    tree \
    vim \
    lcov \
    dos2unix \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set Environment Variables
ENV PATH="/opt/arm-toolchain/bin:/opt/gcc-15/bin:${PATH}"
ENV CC=gcc
ENV CXX=g++

# ---------------------------------------------------------------------
# STAGE 3: Python environment
# ---------------------------------------------------------------------
FROM system-deps AS python-env

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

RUN pip install --no-cache-dir --upgrade pip && \
    pip install --no-cache-dir \
    cpplint \
    gprof2dot \
    coverxygen \
    hpp2plantuml \
    pytest \
    pytest-html \
    PyQt6 \
    codechecker \
    prospector \
    vjunit

# ---------------------------------------------------------------------
# STAGE 4: Rust & ESP Toolchains
# ---------------------------------------------------------------------
FROM python-env AS esp-toolchain

# Install rustup
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | \
    sh -s -- --default-toolchain stable -y --profile minimal
ENV PATH="/root/.cargo/bin:${PATH}"

# Install ESP toolchains
ARG ESP_BOARD=all
RUN curl -L "https://github.com/esp-rs/espup/releases/latest/download/espup-x86_64-unknown-linux-gnu" \
    -o "/root/.cargo/bin/espup" && \
    chmod u+x "/root/.cargo/bin/espup" && \
    espup install --targets "${ESP_BOARD}" --log-level info --export-file /root/export-esp.sh && \
    rustup default esp

RUN cargo install espflash

# ---------------------------------------------------------------------
# FINAL STAGE: Runtime environment with build helpers
# ---------------------------------------------------------------------
FROM esp-toolchain AS final

RUN mkdir -p /workspace/build

COPY Software/STM32F103RBTx/Application/SimulationBindings/Python/ /tmp/PythonDriver/

RUN /opt/venv/bin/pip install -e /tmp/PythonDriver/ && \
    rm -rf /tmp/PythonDriver/

# In your Dockerfile, install newer CMake
RUN wget -q https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-linux-x86_64.sh && \
    chmod +x cmake-3.31.5-linux-x86_64.sh && \
    ./cmake-3.31.5-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.31.5-linux-x86_64.sh

WORKDIR /workspace/build

CMD ["bash", "-c", "exec bash"]