FROM ubuntu:24.04

# Set the working directory
WORKDIR /workspace

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install all required dependencies
RUN apt-get update && apt-get install -y \
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
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# ---------------------------------------------------------------------
# PYTHON SETUP
# ---------------------------------------------------------------------

# Create a virtual environment in /workspace/venv
RUN python3 -m venv /workspace/venv

# Activate the virtual environment and install the packages
RUN /workspace/venv/bin/pip install --upgrade pip && \
    /workspace/venv/bin/pip install \
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

# Add virtual environment binaries to the PATH
ENV PATH="/workspace/venv/bin:$PATH"

# Set the QT_PLUGIN_PATH environment variable
ENV QT_PLUGIN_PATH="/workspace/venv/lib/python3.12/site-packages/PyQt6/Qt6/plugins"


# ---------------------------------------------------------------------
# RUST & ESP32 TOOLCHAIN SETUP
# ---------------------------------------------------------------------

# 1. Install rustup specifically for the Root user
# We set the default toolchain to 'stable' because espup needs a base to work from
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- \
    --default-toolchain stable -y --profile minimal

# 2. CRITICAL: Manually set the PATH so the rest of the RUN commands see 'rustup' and 'cargo'
ENV PATH="/root/.cargo/bin:${PATH}"

# 3. Install extra crates
RUN ARCH=$(rustc -Vv | grep host | cut -d ' ' -f 2) && \
    curl -L "https://github.com/esp-rs/espup/releases/latest/download/espup-${ARCH}" -o "/root/.cargo/bin/espup" && \
    chmod u+x "/root/.cargo/bin/espup" && \
    curl -L "https://github.com/esp-rs/espflash/releases/latest/download/cargo-espflash-${ARCH}.zip" -o "/root/.cargo/bin/cargo-espflash.zip" && \
    unzip "/root/.cargo/bin/cargo-espflash.zip" -d "/root/.cargo/bin/" && \
    curl -L "https://github.com/esp-rs/embuild/releases/latest/download/ldproxy-${ARCH}.zip" -o "/root/.cargo/bin/ldproxy.zip" && \
    unzip "/root/.cargo/bin/ldproxy.zip" -d "/root/.cargo/bin/" && \
    rm /root/.cargo/bin/*.zip && \
    chmod u+x /root/.cargo/bin/cargo-espflash /root/.cargo/bin/ldproxy

# 4. Install Xtensa Rust
# Note: Since we are root, we export to /root/export-esp.sh
ARG ESP_BOARD=all

RUN if [ -n "${GITHUB_TOKEN}" ]; then export GITHUB_TOKEN=${GITHUB_TOKEN}; fi \
    && espup install \
    --targets "${ESP_BOARD}" \
    --log-level debug \
    --export-file /root/export-esp.sh

# 5. Set default toolchain to the one espup just created
RUN rustup default esp

# 6. Make sure the ESP environment is loaded for future shells
RUN echo "source /root/export-esp.sh" >> /root/.bashrc


# Activate ESP environment
RUN echo "source /home/${CONTAINER_USER}/export-esp.sh" >> ~/.bashrc


# ---------------------------------------------------------------------
# FINAL CONFIGURATION
# ---------------------------------------------------------------------

RUN mkdir -p /workspace/build
WORKDIR /workspace/build


CMD ["bash"]