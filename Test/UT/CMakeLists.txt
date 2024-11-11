cmake_minimum_required(VERSION 3.10)
project(UnitTests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find and configure pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Enable testing
enable_testing()

# Google Test setup
find_package(GTest REQUIRED)

# Add Google Mock include directory if available
find_path(GMOCK_INCLUDE_DIR gmock/gmock.h)

# Function to apply sanitizers (AddressSanitizer, UndefinedBehaviorSanitizer) to targets
function(add_sanitizers target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -g)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endfunction()

# Function to apply coverage flags
function(apply_coverage_flags target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()

# Function to create test executables, link libraries, register tests, and apply sanitizers
function(create_test_exec TARGET_NAME SRC_FILES)
    add_executable(${TARGET_NAME} ${SRC_FILES})
    
    target_link_libraries(${TARGET_NAME} PRIVATE
        Threads::Threads
        gtest
        gtest_main
        gmock
        gmock_main
    )

    # Add include directories for each test target
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application
        ${CMAKE_SOURCE_DIR}/Test/UT/Device
        ${CMAKE_SOURCE_DIR}/Test/UT/System
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIR}
    )

    apply_coverage_flags(${TARGET_NAME})
    add_sanitizers(${TARGET_NAME})
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

# Define source files for each test
set(TEST_HMIBUILDER_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/HmiBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/BusinessLogic/test_HmiBuilder.cpp
)

set(TEST_SAFERARRAY_SRC
    ${CMAKE_SOURCE_DIR}/Test/UT/BusinessLogic/test_SaferArray.cpp
)

set(TEST_DRIVERSTATE_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_DriverState.cpp
)

set(TEST_KEYBOARD_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/KeyboardFourPushButtonsDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_KeyboardFourPushButtonsDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)

set(TEST_AMBIENTLIGHT_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/AmbientLightSensorDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_AmbientLightSensorDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)

set(TEST_DISPLAYPIXELCOLOR_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DisplayPixelColor.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_DisplayPixelColor.cpp
)

set(TEST_ST7735DISPLAY_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/St7735DisplayDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/fonts.c
    ${CMAKE_SOURCE_DIR}/Test/UT/System/st7735.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_St7735DisplayDriver.cpp
)

set(TEST_ST7735BRIGHTNESS_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/St7735DisplayBrightnessDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_St7735DisplayBrightnessDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)

set(TEST_UART_SRC
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/UartDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_UartDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)

# Add test executables using the create_test_exec function with source lists
create_test_exec(test_HmiBuilder "${TEST_HMIBUILDER_SRC}")
create_test_exec(test_SaferArray "${TEST_SAFERARRAY_SRC}")
create_test_exec(test_DriverState "${TEST_DRIVERSTATE_SRC}")
create_test_exec(test_KeyboardFourPushButtonsDriver "${TEST_KEYBOARD_SRC}")
create_test_exec(test_AmbientLightSensorDriver "${TEST_AMBIENTLIGHT_SRC}")
create_test_exec(test_DisplayPixelColor "${TEST_DISPLAYPIXELCOLOR_SRC}")
create_test_exec(test_St7735DisplayDriver "${TEST_ST7735DISPLAY_SRC}")
create_test_exec(test_St7735DisplayBrightnessDriver "${TEST_ST7735BRIGHTNESS_SRC}")
create_test_exec(test_UartDriver "${TEST_UART_SRC}")

# Custom target to run all tests
add_custom_target(test
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -V
    COMMENT "Executing all unit tests."
)

# Include the code coverage configuration
include(${CMAKE_SOURCE_DIR}/Test/UT/CodeCoverage.cmake)
