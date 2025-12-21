FROM ubuntu:24.04 AS base

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Set the working directory
WORKDIR /workspace

# ---------------------------------------------------------------------
# STAGE 1: System dependencies (changes rarely)
# ---------------------------------------------------------------------
FROM base AS system-deps

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    gcovr \
    python3 \
    python3-pip \
    python3-dbg \
    python3-venv \
    python3-pyqt6 \
    wget \
    llvm \
    clang \
    clang-tidy \
    clang-tools \
    libclang-dev \
    lsb-release \
    unzip \
    openjdk-11-jdk-headless \
    graphviz \
    doxygen \
    lld \
    software-properties-common \
    libgtest-dev \
    libgmock-dev \
    vim \
    googletest \
    cppcheck \
    xsltproc \
    plantuml \
    libnewlib-arm-none-eabi \
    qt6-base-dev \
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
    lcov \
    dos2unix \
    pkg-config \
    libssl-dev \
    libudev-dev \
    ca-certificates \
    cpulimit \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# STAGE 2: Python environment (changes occasionally)
# ---------------------------------------------------------------------
FROM system-deps AS python-env

# Create a virtual environment
RUN python3 -m venv /workspace/venv

# Set environment variables for Python
ENV PATH="/workspace/venv/bin:$PATH"
ENV QT_PLUGIN_PATH="/workspace/venv/lib/python3.12/site-packages/PyQt6/Qt6/plugins"

# Upgrade pip and install Python packages
RUN /workspace/venv/bin/pip install --no-cache-dir --upgrade pip && \
    /workspace/venv/bin/pip install --no-cache-dir \
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
# STAGE 3: Rust toolchain (slowest, changes rarely)
# ---------------------------------------------------------------------
FROM python-env AS rust-toolchain

# Install rustup for root user
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- \
    --default-toolchain stable -y --profile minimal

# Set PATH for Rust
ENV PATH="/root/.cargo/bin:${PATH}"

# Install Rust tools in a single layer
ARG ARCH
RUN if [ -z "$ARCH" ]; then ARCH=$(uname -m)-unknown-linux-gnu; fi && \
    curl -L "https://github.com/esp-rs/espup/releases/latest/download/espup-${ARCH}" -o "/root/.cargo/bin/espup" && \
    chmod u+x "/root/.cargo/bin/espup" && \
    curl -L "https://github.com/esp-rs/espflash/releases/latest/download/cargo-espflash-${ARCH}.zip" -o "/tmp/cargo-espflash.zip" && \
    unzip "/tmp/cargo-espflash.zip" -d "/root/.cargo/bin/" && \
    curl -L "https://github.com/esp-rs/embuild/releases/latest/download/ldproxy-${ARCH}.zip" -o "/tmp/ldproxy.zip" && \
    unzip "/tmp/ldproxy.zip" -d "/root/.cargo/bin/" && \
    rm /tmp/*.zip && \
    chmod u+x /root/.cargo/bin/cargo-espflash /root/.cargo/bin/ldproxy

# ---------------------------------------------------------------------
# STAGE 4: ESP32 toolchain (slowest part)
# ---------------------------------------------------------------------
FROM rust-toolchain AS esp-toolchain

ARG ESP_BOARD=all
ARG GITHUB_TOKEN

# Install Xtensa Rust
RUN if [ -n "${GITHUB_TOKEN}" ]; then export GITHUB_TOKEN=${GITHUB_TOKEN}; fi && \
    espup install \
    --targets "${ESP_BOARD}" \
    --log-level info \
    --export-file /root/export-esp.sh && \
    rustup default esp

# Set up bash environment
RUN echo "source /root/export-esp.sh" >> /root/.bashrc

# ---------------------------------------------------------------------
# FINAL STAGE: Runtime environment
# ---------------------------------------------------------------------
FROM esp-toolchain AS final

# Create build directory
RUN mkdir -p /workspace/build

WORKDIR /workspace/build

CMD ["bash"]