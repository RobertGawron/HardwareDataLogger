cmake_minimum_required(VERSION 3.10)
project(BusinessLogic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Find and configure pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# List of test executables
set(TEST_EXECUTABLES
    test_HmiBuilder
    test_SaferArray
    test_DriverState
    test_KeyboardFourPushButtonsDriver
    test_AmbientLightSensorDriver
    test_St7735DisplayBrightnessDriver
    test_St7735DisplayDriver
    test_UartDriver
)

function(apply_coverage_flags target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()


# Include directories for all modules
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Interfaces)

include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Interfaces)

include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Interfaces)

include_directories(${CMAKE_SOURCE_DIR}/Test/UT/Device)
include_directories(${CMAKE_SOURCE_DIR}/Test/UT/System)

# Enable testing
enable_testing()

# Google Test setup
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add Google Mock include directory if it's not already in GTest include directories
find_path(GMOCK_INCLUDE_DIR gmock/gmock.h)
if(GMOCK_INCLUDE_DIR)
    include_directories(${GMOCK_INCLUDE_DIR})
endif()


# Add test executable for BusinessLogic

add_executable(test_HmiBuilder
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/BusinessLogic/test_HmiBuilder.cpp
)
target_link_libraries(test_HmiBuilder PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)

add_executable(test_SaferArray ${CMAKE_SOURCE_DIR}/Test/UT/BusinessLogic/test_SaferArray.cpp)
target_link_libraries(test_SaferArray PRIVATE
    Threads::Threads
    gtest
    gtest_main
)

# Add test executable for Device

# Add test executable for Driver
add_executable(test_DriverState
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_DriverState.cpp
)
target_link_libraries(test_DriverState PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)

add_executable(test_KeyboardFourPushButtonsDriver
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/KeyboardFourPushButtonsDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_KeyboardFourPushButtonsDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)
target_link_libraries(test_KeyboardFourPushButtonsDriver PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)

add_executable(test_AmbientLightSensorDriver
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/AmbientLightSensorDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_AmbientLightSensorDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)
target_link_libraries(test_AmbientLightSensorDriver PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)


# Add test executable for DisplayPixelColor
add_executable(test_DisplayPixelColor 
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DisplayPixelColor.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_DisplayPixelColor.cpp
)
target_link_libraries(test_DisplayPixelColor PRIVATE
    Threads::Threads
    gtest
    gtest_main
)

# Add test executable for St7735DisplayDriver
add_executable(test_St7735DisplayDriver 
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/St7735DisplayDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/fonts.c
    ${CMAKE_SOURCE_DIR}/Test/UT/System/st7735.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_St7735DisplayDriver.cpp
)
target_link_libraries(test_St7735DisplayDriver PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)

add_executable(test_St7735DisplayBrightnessDriver
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/St7735DisplayBrightnessDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_St7735DisplayBrightnessDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)
target_link_libraries(test_St7735DisplayBrightnessDriver PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)

add_executable(test_UartDriver
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/UartDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/Driver/test_UartDriver.cpp
    ${CMAKE_SOURCE_DIR}/Test/UT/System/main.cpp
)
target_link_libraries(test_UartDriver PRIVATE
    Threads::Threads
    gtest
    gtest_main
    gmock
    gmock_main
)




foreach(test_exec ${TEST_EXECUTABLES})
    apply_coverage_flags(${test_exec})
endforeach()

foreach(test_exec ${TEST_EXECUTABLES})
    add_test(NAME ${test_exec} COMMAND ${test_exec})
endforeach()

add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -V
    DEPENDS ${TEST_EXECUTABLES}
    COMMENT "Executing all unit tests."
)

# Include the code coverage configuration
include(${CMAKE_SOURCE_DIR}/Test/UT/CodeCoverageConfig.cmake)

# Include the static analyse configuration
include(${CMAKE_SOURCE_DIR}/Test/UT/StaticAnalysisConfig.cmake)

# Include the dynamic analyse configuration
include(${CMAKE_SOURCE_DIR}/Test/UT/DynamicAnalysisConfig.cmake)
