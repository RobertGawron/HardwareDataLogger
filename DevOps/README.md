## Prerequisites

* * Install Docker. For Linux, use your package manager. For Windows, you need to install WSL (Windows Subsystem for Linux) first, then install Docker Desktop.

## Build the Docker Image

In the main directory (HardwareDataLogger), run:

```
docker-compose build dev && docker-compose up -d --remove-orphans && docker-compose exec dev bash
```

It takes time to build the image the first time, but once it's done, you should be logged in with the entire environment set up.

## Run Unit Tests

```
cd /workspace/build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja test_biz && ninja test_dev && ninja test_drv
```

## Run C++ Static Analysis

```
cd /workspace/build && cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug .. && ninja CMakeFiles/cstatic
```

## Run Python Static Analysis

```
cd /workspace/build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja pstatic
```

## Run Code Coverage

```
cd /workspace/build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja test_biz && ninja test_dev && ninja test_drv && ninja cov
```

## Run Docs Coverage

```
cd /workspace/build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug .. && ninja docs
```

## Run UML Generation

```
cd /workspace/build
cmake ..
make uml
```
