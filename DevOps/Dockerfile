# ==============================================================
# Base
# ==============================================================
FROM ubuntu:24.04 AS base
ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /workspace


# ==============================================================
# STAGE 1: Build dependencies for GCC
# ==============================================================
FROM base AS build-deps

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    xz-utils \
    ca-certificates \
    unzip \
    gnupg \
    lsb-release \
    software-properties-common \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    libisl-dev \
    zlib1g-dev \
    flex \
    bison \
    texinfo \
    file \
    && rm -rf /var/lib/apt/lists/*


# ==============================================================
# STAGE 2: Build GCC 16.1 (Release Candidate)
# ==============================================================
FROM build-deps AS gcc-builder

# Use the latest 16.1 RC tarball
RUN mkdir -p /tmp/gcc-build && cd /tmp/gcc-build && \
    wget -q "https://gcc.gnu.org/pub/gcc/snapshots/16.1.0-RC-20260424/gcc-16.1.0-RC-20260424.tar.xz" && \
    tar -xf gcc-16.1.0-RC-20260424.tar.xz && \
    rm gcc-16.1.0-RC-20260424.tar.xz

RUN cd /tmp/gcc-build/gcc-16.1.0-RC-20260424 && \
    ./contrib/download_prerequisites && \
    cd /tmp/gcc-build && \
    mkdir build && cd build && \
    ../gcc-16.1.0-RC-20260424/configure \
        --prefix=/opt/gcc-16 \
        --enable-languages=c,c++ \
        --disable-multilib \
        --disable-bootstrap \
        --enable-checking=release \
        --with-system-zlib && \
    make -j$(nproc) && \
    make install && \
    cd / && rm -rf /tmp/gcc-build

# ==============================================================
# STAGE 3: System dependencies
# ==============================================================
FROM base AS system-deps

# Copy GCC 16
COPY --from=gcc-builder /opt/gcc-16 /opt/gcc-16

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    xz-utils \
    ca-certificates \
    unzip \
    gnupg \
    lsb-release \
    software-properties-common \
    libgmp10 \
    libmpfr6 \
    libmpc3 \
    ninja-build \
    gdb \
    gdb-multiarch \
    openocd \
    stlink-tools \
    usbutils \
    python3 \
    python3-pip \
    python3-venv \
    graphviz \
    doxygen \
    libgtest-dev \
    libgmock-dev \
    cppcheck \
    gcovr \
    lcov \
    tree \
    vim \
    dos2unix \
    just \
    && rm -rf /var/lib/apt/lists/*


# --------------------------------------------------------------
# Set GCC 16 as default
# --------------------------------------------------------------
RUN update-alternatives --install /usr/bin/gcc gcc /opt/gcc-16/bin/gcc 100 \
    --slave /usr/bin/g++ g++ /opt/gcc-16/bin/g++ \
    --slave /usr/bin/gcov gcov /opt/gcc-16/bin/gcov \
    --slave /usr/bin/gcc-ar gcc-ar /opt/gcc-16/bin/gcc-ar \
    --slave /usr/bin/gcc-ranlib gcc-ranlib /opt/gcc-16/bin/gcc-ranlib

# --------------------------------------------------------------
# Install LLVM/Clang 22.1.0
# --------------------------------------------------------------
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key \
    | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    add-apt-repository -y "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-22 main" && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        clang-22 \
        clang++-22 \
        clang-tools-22 \
        clang-format-22 \
        clang-tidy-22 \
        lld-22 \
        lldb-22 \
        libc++-22-dev \
        libc++abi-22-dev \
    && rm -rf /var/lib/apt/lists/*

# ==============================================================
# Install ARM GNU Toolchain
# ==============================================================
ARG ARM_TOOLCHAIN_VERSION=15.3.rel1
ARG ARM_TOOLCHAIN_URL=https://gitlab.arm.com/api/v4/projects/tooling%2Fgnu-toolchains-for-arm/packages/generic/gnu-toolchain/${ARM_TOOLCHAIN_VERSION}/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz

RUN wget -q ${ARM_TOOLCHAIN_URL} && \
    tar -xJf arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz -C /opt/ && \
    rm arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi.tar.xz && \
    ln -s /opt/arm-gnu-toolchain-${ARM_TOOLCHAIN_VERSION}-x86_64-arm-none-eabi /opt/arm-toolchain

# ==============================================================
# Install Node.js 20 + TypeScript
# ==============================================================
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl ca-certificates gnupg && \
    curl -fsSL https://deb.nodesource.com/setup_20.x | bash - && \
    apt-get install -y --no-install-recommends nodejs && \
    npm install -g typescript && \
    rm -rf /var/lib/apt/lists/*


# ==============================================================
# STAGE 4: Python environment
# ==============================================================
FROM system-deps AS python-env

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

RUN pip install --no-cache-dir --upgrade pip && \
    pip install --no-cache-dir \
        cpplint \
        gprof2dot \
        coverxygen \
        #hpp2plantuml \
        pytest \
        pytest-html \
        codechecker \
        #prospector \
        #vjunit \
        fastapi==0.109.0 \
        uvicorn[standard]==0.27.0 \
        websockets==12.0 \
        pydantic==2.5.0 \
        python-multipart==0.0.6 \
        python-dotenv \
        aiofiles \
        # python linters
        black ruff mypy radon bandit pip-audit safety cyclonedx-bom


# ==============================================================
# STAGE 5: Rust & ESP
# ==============================================================
FROM python-env AS esp-toolchain

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs \
    | sh -s -- --default-toolchain stable -y --profile minimal

ENV PATH="/root/.cargo/bin:${PATH}"

ARG ESP_BOARD=all
RUN curl -L "https://github.com/esp-rs/espup/releases/latest/download/espup-x86_64-unknown-linux-gnu" \
    -o "/root/.cargo/bin/espup" && \
    chmod u+x "/root/.cargo/bin/espup" && \
    espup install --targets "${ESP_BOARD}" --export-file /root/export-esp.sh && \
    rustup default esp && \
    cargo install espflash


# ==============================================================
# FINAL STAGE
# ==============================================================
FROM esp-toolchain AS final

RUN mkdir -p /workspace/build

# Install latest CMake
ARG CMAKE_VERSION=4.4.0
RUN wget -q https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.sh && \
    chmod +x cmake-${CMAKE_VERSION}-linux-x86_64.sh && \
    ./cmake-${CMAKE_VERSION}-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-${CMAKE_VERSION}-linux-x86_64.sh

# todo move it somewhere earlier
ENV PATH="/opt/arm-toolchain/bin:${PATH}"


WORKDIR /workspace/build
CMD ["bash"]