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

# Custom target to run just these business logic tests
add_custom_target(test_drv
    COMMAND ${CMAKE_CTEST_COMMAND} -V
    COMMENT "Executing Business Logic unit tests."
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
         ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Test/Stubs
        ${GTEST_INCLUDE_DIRS}
        ${GMOCK_INCLUDE_DIR}
    )

    apply_coverage_flags(${TARGET_NAME})
    add_sanitizers(${TARGET_NAME})
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

    add_dependencies(test_drv ${TARGET_NAME})
endfunction()


#create_test_exec(test_AmbientLightSensorDriver 
#    ../Src/AmbientLightSensorDriver.cpp 
#    test_AmbientLightSensorDriver.cpp
#)

create_test_exec(test_DisplayPixelColor 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DisplayPixelColor.cpp 
    test_DisplayPixelColor.cpp
)

create_test_exec(test_DriverState 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp
    test_DriverState.cpp
)

create_test_exec(test_KeyboardDriver 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/KeyboardFourPushButtonsDriver.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Test/Stubs/main.cpp
    test_KeyboardFourPushButtonsDriver.cpp
)

create_test_exec(test_AmbientLight 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/AmbientLightSensorDriver.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp 
    test_AmbientLightSensorDriver.cpp
)

create_test_exec(test_UartDriver 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/UartDriver.cpp 
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp 
    test_UartDriver.cpp
)

create_test_exec(test_PulseCounterDriver 
    ../Src/PulseCounterDriver.cpp 
    ../Src/DriverState.cpp 
    test_PulseCounterDriver.cpp
)
