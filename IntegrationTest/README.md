# Objectives

Software-in-the-loop (SIL) tests.

This is a set of automated integration tests that verify the behavior of STM and ESP32 firmware nodes working together.

These tests are not unit tests. The unit tests are located in the directories where the STM32 and ESP32 firmware reside.

# Prerequisites

[Install Docker and log into the container.](../Documentation/Manuals/SetupDockerContainer.md)

# Running tests

On first run of the Docker image, install the firmware wrapper package:

```
pip install -e /workspace/Software/STM32F103RBTx/Application/Driver/Host/Python/ 
```

Then use this one-liner:

```
cmake -G Ninja -B /workspace/build -DCMAKE_BUILD_TYPE=Debug /workspace && \
    ninja -C /workspace/build && \
    cd /workspace/IntegrationTest && \
    pytest test_*.py -s --html=/workspace/build/BuildArtifacts/IntegrationTest.html
```
# Troubleshooting

## Troubleshooting core dumps

### Check if Core Dumps Are Enabled

Core dumps might be disabled by default on your system. Check the current core dump settings using:

```
ulimit -c
```

If it shows `0`, core dumps are disabled. Enable core dumps by running:

```
ulimit -c unlimited
```

On WSL (Docker runs in Windows), disable `wsl-capture-crash` for Core Dumps:

```
echo "/tmp/core.%e.%p" | tee /proc/sys/kernel/core_pattern
```

### Debug Core Dumps

```
gdb /workspace/venv/bin/python3 /tmp/core.pytest.2430
```