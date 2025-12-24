## Objectives

Software-in-the-loop (SIL) tests.

This is a set of automated integration tests that verify the behavior of STM and ESP32 firmware nodes working together.

These tests are not unit tests. The unit tests are located in the directories where the STM32 and ESP32 firmware reside.

## Prerequisites

[Install Docker and log into the container.](../Documentation/Manuals/SetupDockerContainer.md)

# Running tests

On first run, install the firmware wrapper package:

```
pip install -e /workspace/Software/STM32F103RBTx/Application/Driver/Host/Python/ 
```

Then use this one-liner:

```
cd /workspace/build/ && \
    cmake -DCMAKE_BUILD_TYPE=Debug .. && \
    make -j24 && \
    cd /workspace/IntegrationTest && \
    pytest test_*.py -s  --html=/workspace/build/BuildArtifacts/IntegrationTest.html
```
