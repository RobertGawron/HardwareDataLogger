project(DriverHardwareUnitTests LANGUAGES CXX)

enable_testing()

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

# ------------------------------------------------------------
# Common flags
# ------------------------------------------------------------

function(add_common_flags target)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -g -O0
            -fprofile-arcs -ftest-coverage
        )
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()

# ------------------------------------------------------------
# Custom test target
# ------------------------------------------------------------

add_custom_target(test_drv
    COMMAND ${CMAKE_CTEST_COMMAND} -V
    COMMENT "Running Driver Layer Unit Tests..."
    USES_TERMINAL
)

# ------------------------------------------------------------
# Helper to create test
# ------------------------------------------------------------

function(create_driver_test TARGET_NAME TEST_FILE)

    add_executable(${TARGET_NAME} ${TEST_FILE})

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            Driver           
            GTest::gtest
            GTest::gtest_main
            Threads::Threads
    )

    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application
        ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Hardware/Test/Stubs
    )

    add_common_flags(${TARGET_NAME})

    gtest_discover_tests(${TARGET_NAME})
    add_dependencies(test_drv ${TARGET_NAME})

endfunction()

# ------------------------------------------------------------
# Tests
# ------------------------------------------------------------

create_driver_test(test_LightSensorDriver test_LightSensorDriver.cpp)
create_driver_test(test_KeyboardDriver test_KeyboardDriver.cpp)
create_driver_test(test_UartDriver test_UartDriver.cpp)
create_driver_test(test_PulseCounterDriver test_PulseCounterDriver.cpp)
create_driver_test(test_DriverState test_DriverState.cpp)
create_driver_test(test_St7735DisplayBrightnessDriver test_St7735DisplayBrightnessDriver.cpp)