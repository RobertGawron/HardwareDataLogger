## Prerequisites

[Install Docker and log into the container.](./SetupDockerContainers.md)

# Running tests

cd /workspace/build/ && cmake .. && make -j24 && cd /workspace/Test/System && pytest test_display.py -s  --html=report.html

