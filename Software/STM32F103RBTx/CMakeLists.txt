cmake_minimum_required(VERSION 3.22)

# Set the project name
set(CMAKE_PROJECT_NAME NUCLEO-F103RB)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM, C, and C++ languages
enable_language(C CXX ASM)

# Project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: ${CMAKE_BUILD_TYPE}")

# Define STM32F103xB device (specific to the NUCLEO-F103RB board)
add_compile_definitions(STM32F103xB)

# Create the executable target
add_executable(${CMAKE_PROJECT_NAME})

# Add subdirectory for the application
add_subdirectory(Application)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)



# Add include paths
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Application/
    ${CMAKE_CURRENT_SOURCE_DIR}/Application/Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/stm32-st7735
    #${CMAKE_CURRENT_SOURCE_DIR}/cubeide-sd-card/cubeide-sd-card/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc  # Corrected STM32F1xx driver include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F1xx/Include  # Corrected CMSIS for STM32F1xx
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
)


# Gather C source files
file(GLOB C_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/stm32-st7735/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"  # Include C source files
)

# Gather C++ source files
file(GLOB CPP_SOURCES

    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.cpp"  # Include C++ source files
)

# Add sources to the executable target
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${C_SOURCES} ${CPP_SOURCES})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user-defined library search paths (if any)
)

# Link external libraries (such as STM32CubeMX)
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    ApplicationLib
    # Add user-defined libraries (if any)
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    STM32F103xB   # Correct STM32F1 device macro for NUCLEO-F103RB
)
 