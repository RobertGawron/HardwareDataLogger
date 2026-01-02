# Multi-stage Dockerfile with Latest GCC & LLVM for ARM and Native Linux
FROM ubuntu:24.04 AS base

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Set the working directory
WORKDIR /workspace

# ---------------------------------------------------------------------
# STAGE 1: System dependencies & Latest Toolchains
# ---------------------------------------------------------------------
FROM base AS system-deps

# Install base dependencies
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
    && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# Install Latest Native GCC (v14.2) for x86_64 Linux
# ---------------------------------------------------------------------
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    gcc-14 \
    g++-14 \
    gcc-14-multilib \
    g++-14-multilib \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-14 \
    --slave /usr/bin/gcov gcov /usr/bin/gcov-14 \
    --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-14 \
    --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-14 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# Install Latest LLVM/Clang (v19) for x86_64 Linux
# ---------------------------------------------------------------------
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    add-apt-repository -y "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-19 main" && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    clang-19 \
    clang++-19 \
    clang-tools-19 \
    clang-format-19 \
    clang-tidy-19 \
    lld-19 \
    lldb-19 \
    libc++-19-dev \
    libc++abi-19-dev \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 100 \
    --slave /usr/bin/clang++ clang++ /usr/bin/clang++-19 \
    --slave /usr/bin/clang-format clang-format /usr/bin/clang-format-19 \
    --slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-19 \
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
    valgrind \
    strace \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set Environment Variables
ENV PATH="/opt/arm-toolchain/bin:${PATH}"
# Default to GCC for native builds (can override with CC/CXX)
ENV CC=gcc
ENV CXX=g++

# ---------------------------------------------------------------------
# STAGE 2: Python environment
# ---------------------------------------------------------------------
FROM system-deps AS python-env

RUN python3 -m venv /workspace/venv
ENV PATH="/workspace/venv/bin:$PATH"

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
# STAGE 3: Rust & ESP Toolchains
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

# ---------------------------------------------------------------------
# FINAL STAGE: Runtime environment with build helpers
# ---------------------------------------------------------------------
FROM esp-toolchain AS final

RUN mkdir -p /workspace/build
WORKDIR /workspace/build

CMD ["bash", "-c", "show-compilers && exec bash"]