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
cd /workspace/build
cmake -DCMAKE_BUILD_TYPE=Debug .. && \
make -j23 && \
make test -j23 && \
make coverage
```

## Run Docs Coverage

```
cd /workspace/build
cmake ..
make docs
```

## Run UML Generation

```
cd /workspace/build
cmake ..
make uml
```

## Running "Include What You Use"

```
cd /workspace/build

CC="clang-10" CXX="clang++-10" cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use ../Software
```

