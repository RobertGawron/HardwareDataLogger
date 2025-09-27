cmake_minimum_required(VERSION 3.22)

# Setup compiler before project()
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Include toolchain before project()
include("cmake/gcc-arm-none-eabi.cmake")

# Core project definition
project(HardwareDataLogger_STM32F103RBTx LANGUAGES C CXX ASM)

# Define STM32 device globally BEFORE CubeMX subdirectory
add_compile_definitions(STM32F103xB)

# Debug symbol handling
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_OPTIONS 
        "$<$<COMPILE_LANGUAGE:C>:-g3>"
        "$<$<COMPILE_LANGUAGE:CXX>:-g3>"
        "$<$<COMPILE_LANGUAGE:ASM>:-g3>"
    )
endif()

# Enable compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create executable
add_executable(${PROJECT_NAME})

# Add subdirectories - CubeMX MUST come first
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(Application)

# Target sources
target_sources(${PROJECT_NAME} PRIVATE
    Core/Src/MyApplication.cpp
    Core/Src/PlatformFactoryStm32.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    Application
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
    ../Common
)

# Link libraries - plain signature to match CubeMX
target_link_libraries(${PROJECT_NAME}
    stm32cubemx
    BusinessLogic
    Device
    Driver
    u8g2
)

# Apply debug options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE ${DEBUG_OPTIONS})
endif()