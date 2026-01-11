cmake_minimum_required(VERSION 3.28)

# Use CubeMX toolchain by default
if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# This makes it apply to subdirectories too
set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard" FORCE)

# Enable experimental C++ module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

# Define default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

# Add subdirectories - CubeMX MUST come first
add_subdirectory(cmake/stm32cubemx)

# Add Application subdirectory
add_subdirectory(Application/Library/u8g2/)
add_subdirectory(Application/Driver/)
add_subdirectory(Application/Device/)
add_subdirectory(Application/BusinessLogic/)

option(BUILD_IS_FOR_HARDWARE "Build for STM32 hardware" ON)

target_sources(${PROJECT_NAME} PRIVATE
    Application/Library/stm32-st7735/st7735.c
    Application/Library/stm32-st7735/st7735_reg.c
)

# C++ module interface unit
target_sources(${PROJECT_NAME}
  PRIVATE
    FILE_SET app_modules
    TYPE CXX_MODULES
    FILES
      Core/Src/MyApplication.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Os
    -flto
    -ffunction-sections
    -fdata-sections
)

target_link_options(${PROJECT_NAME} PRIVATE
    -Wl,--gc-sections
    -flto
    # -s
)

target_link_libraries(${PROJECT_NAME}
    stm32cubemx
    u8g2
    DriverInterface
    Driver
    Device
    BusinessLogic
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE ${DEBUG_OPTIONS})
endif()

# Custom target for flashing
add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
            -c "program $<TARGET_FILE:${PROJECT_NAME}> verify reset exit"
    DEPENDS ${PROJECT_NAME}
    COMMENT "Flashing $<TARGET_FILE:${PROJECT_NAME}> to STM32"
    USES_TERMINAL
)