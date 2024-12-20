## Prerequisites

[Install Docker and log into the container.](./SetupDockerContainers.md)

## Run Unit Tests

```
cmake ..
make test
```

## Run Static Analysis

```
cd /workspace/build && \
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_STANDARD=17 .. && \
make static
```

## Run Code Coverage

```
cmake -DCMAKE_BUILD_TYPE=Debug .. && \
make -j23 && \
make test -j23 && \
make coverage
```

## Run Docs Coverage

```
cmake ..
make docs
```

## Run UML Generation

```
cmake ..
make uml
```

## Running "Include What You Use"

```
cd build

CC="clang-10" CXX="clang++-10" cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use ../Software
```

