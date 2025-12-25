cmake_minimum_required(VERSION 3.28)
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

# Custom target to run just these business logic tests
add_custom_target(test_biz
    COMMAND ${CMAKE_CTEST_COMMAND} -V
    COMMENT "Executing Business Logic unit tests."
)

function(create_test_exec TARGET_NAME)
    # Using ARGN to allow multiple source files
    add_executable(${TARGET_NAME} ${ARGN})
    
    if(EXPORT_BL_GROUP)
        # This sets the default for ALL targets defined in this file (and below)
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
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Library/u8g2/cppsrc/
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Library/u8g2/csrc/
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIR}
    )

    apply_coverage_flags(${TARGET_NAME})
    add_sanitizers(${TARGET_NAME})
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

    add_dependencies(test_biz ${TARGET_NAME})
endfunction()


create_test_exec(test_MeasurementDataStore
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/MeasurementDataStore.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_MeasurementDataStore.cpp
)

create_test_exec(test_MeasurementCoordinator
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/MeasurementCoordinator.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_MeasurementCoordinator.cpp
)


create_test_exec(test_MeasurementStoresFactory
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/MeasurementStoresFactory.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_MeasurementStoresFactory.cpp
)

create_test_exec(test_ApplicationBuilder
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/ApplicationBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_ApplicationBuilder.cpp
)

create_test_exec(test_MeasurementSourcesFactory
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic/Src/MeasurementSourcesFactory.cpp
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Src/DriverState.cpp
    test_MeasurementSourcesFactory.cpp
)
