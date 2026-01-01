cmake_minimum_required(VERSION 3.31)
project(BusinessLogicUnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS cppm)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

# --- Helper Functions ---

function(add_common_flags target)

    # Compiler Warnings
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

    # Sanitizers & Coverage (Debug Only)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()

# --- Main Function: create_module_test ---

function(create_module_test TARGET_NAME TEST_FILE)

    add_executable(${TARGET_NAME} ${TEST_FILE})

    # JSON Export Logic
    if(DEFINED EXPORT_SINGLE_JSON AND EXPORT_SINGLE_JSON STREQUAL "${TARGET_NAME}")
        message(STATUS "Enabling compile_commands.json export for: ${TARGET_NAME}")
        set_target_properties(${TARGET_NAME} PROPERTIES EXPORT_COMPILE_COMMANDS ON)
    endif()

    set(MODULE_FILE "${ARGV2}")
    if(MODULE_FILE)
        get_filename_component(MOD_ABS "${MODULE_FILE}" ABSOLUTE)
        get_filename_component(MOD_DIR "${MOD_ABS}" DIRECTORY)

        set(LIB_NAME "SUT_${TARGET_NAME}")
        add_library(${LIB_NAME} STATIC "${MOD_ABS}")
        
        target_sources(${LIB_NAME} PUBLIC
            FILE_SET CXX_MODULES 
            BASE_DIRS "${MOD_DIR}"
            FILES "${MOD_ABS}"
        )

        target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})
    endif()

    target_link_libraries(${TARGET_NAME} PRIVATE
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
        Threads::Threads
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Library/u8g2/cppsrc/
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Library/u8g2/csrc/
    )

    add_common_flags(${TARGET_NAME})

    # Register Test with Label "BusinessLogic"
    # This allows: ctest -L BusinessLogic
    gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "BusinessLogic")
    
endfunction()

# --- Test Definitions ---

create_module_test(test_MeasurementCoordinator 
    test_MeasurementCoordinator.cpp
    ../Modules/MeasurementCoordinator.cppm 
)


# --- Custom Target ---
add_custom_target(test_biz
    COMMAND ${CMAKE_CTEST_COMMAND} -L "BusinessLogic" --output-on-failure
    COMMENT "Running Business Logic Unit Tests..."
    USES_TERMINAL
)
