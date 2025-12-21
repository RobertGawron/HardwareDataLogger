## Prerequisites

[Install Docker and log into the container.](./SetupDockerContainers.md)

## Run Unit Tests

```
cd /workspace && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make test_biz && make test_dev && make test_drv
```

## Run C++ Static Analysis

```
cd /workspace/build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug .. && make static
```

## Run Pÿthon Static Analysis

```
cd /workspace && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make pystatic
```

## Run Code Coverage

```
cd /workspace && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make test_biz && make test_dev && make test_drv && make cov
```

## Run Docs Coverage

```
cd /workspace && mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make docs
```

## Run UML Generation

```
cd /workspace/build
cmake ..
make uml
```
