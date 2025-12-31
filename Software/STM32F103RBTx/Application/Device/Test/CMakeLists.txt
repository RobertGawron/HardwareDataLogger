cmake_minimum_required(VERSION 3.28)
project(BusinessLogicUnitTests)

# 1. Setup Environment
set(CMAKE_CXX_STANDARD 20)
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
    
    if(DEFINED EXPORT_SINGLE_JSON AND EXPORT_SINGLE_JSON STREQUAL "${TARGET_NAME}")
        message(STATUS "Enabling compile_commands.json export for: ${TARGET_NAME}")
        set_target_properties(${TARGET_NAME} PROPERTIES EXPORT_COMPILE_COMMANDS ON)
    endif()

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
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_Keyboard.cpp
)

create_test_exec(test_PulseCounterMeasurementSource 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/PulseCounterMeasurementSource.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_PulseCounterMeasurementSource.cpp
)

create_test_exec(test_WiFiMeasurementRecorder 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device/Src/WiFiMeasurementRecorder.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp 
    test_WiFiMeasurementRecorder.cpp
)

create_test_exec(test_WiFiMeasurementSerializer 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp 
    test_WiFiMeasurementSerializer.cpp
)

create_test_exec(test_Crc32 
    test_Crc32.cpp
)

create_test_exec(test_CobsEncoder 
    test_CobsEncoder.cpp
)