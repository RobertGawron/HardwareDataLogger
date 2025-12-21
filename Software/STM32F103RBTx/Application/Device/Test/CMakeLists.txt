cmake_minimum_required(VERSION 3.10)
project(BusinessLogicUnitTests)

# 1. Setup Environment
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find pthreads and GTest
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
enable_testing()
find_package(GTest REQUIRED)
find_path(GMOCK_INCLUDE_DIR gmock/gmock.h)

# --- Helper Functions ---

function(add_sanitizers target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -g)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endfunction()

function(apply_coverage_flags target)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()

# Custom target to run just these device tests
add_custom_target(test_dev
    COMMAND ${CMAKE_CTEST_COMMAND} -V
    COMMENT "Executing Device unit tests."
)

function(create_test_exec TARGET_NAME)
    # Using ARGN to allow multiple source files
    add_executable(${TARGET_NAME} ${ARGN})
    
    target_link_libraries(${TARGET_NAME} PRIVATE
        Threads::Threads
        gtest
        gtest_main
        gmock
        gmock_main
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIR}
    )

    apply_coverage_flags(${TARGET_NAME})
    add_sanitizers(${TARGET_NAME})
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

    add_dependencies(test_dev ${TARGET_NAME})
endfunction()


create_test_exec(test_Keyboard 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/Keyboard.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    test_Keyboard.cpp
)

create_test_exec(test_PulseCounterSource 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/PulseCounterMeasurementSource.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    test_PulseCounterMeasurementSource.cpp
)

create_test_exec(test_WiFiRecorder 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/WiFiMeasurementRecorder.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/WiFiMeasurementSerializer.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/CobsEncoder.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/Crc32.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp 
    test_WiFiMeasurementRecorder.cpp
)

create_test_exec(test_WiFiSerializer 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/WiFiMeasurementSerializer.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/Crc32.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp 
    test_WiFiMeasurementSerializer.cpp
)

create_test_exec(test_Crc32 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/Crc32.cpp 
    test_Crc32.cpp
)

create_test_exec(test_CobsEncoder 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/CobsEncoder.cpp 
    test_CobsEncoder.cpp
)