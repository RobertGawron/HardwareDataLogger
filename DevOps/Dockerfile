# Stage 1: Build Stage
# In this stage, we build include-what-you-use because it is not available as a Linux package. 
# We also avoid polluting the final image with temporary files.
FROM ubuntu:24.04 AS build-stage

# Set the working directory
WORKDIR /workspace

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and IWYU dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    llvm-15-dev \
    libclang-15-dev \
    clang-15 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Clone and build include-what-you-use
RUN git clone https://github.com/include-what-you-use/include-what-you-use.git /usr/local/src/iwyu && \
    cd /usr/local/src/iwyu && \
    git checkout clang_15 && \
    mkdir build && cd build && \
    cmake -G "Unix Makefiles" .. && \
    make -j $(nproc)

# Stage 2: Minimal Runtime Stage
FROM ubuntu:24.04 AS runtime-stage

# Set the working directory
WORKDIR /workspace

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install only the runtime dependencies for IWYU
#RUN apt-get update && apt-get install -y \
#    libclang-15-dev \
#    clang-15 \
#    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Copy the IWYU binary from the build stage
COPY --from=build-stage /usr/local/src/iwyu/build/bin/include-what-you-use /usr/local/bin/include-what-you-use


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

# workaround for cppcheck html generator that needs older version 
RUN pip uninstall -y pygments && pip install pygments==2.7.4


RUN mkdir -p /workspace/build
WORKDIR /workspace/build

#RUN git clone https://github.com/facebook/infer.git \
#&& cd infer \
#&& ./build-infer.sh \
#&& ln -s $(pwd)/infer/bin/infer /usr/local/bin/infer \
#&& cd .. && rm -rf infer

# Default command
CMD ["bash"]
