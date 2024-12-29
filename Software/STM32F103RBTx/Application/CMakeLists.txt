cmake_minimum_required(VERSION 3.22)
project(ApplicationLib)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



if(USE_X86_HEADERS)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    # Enable coverage flags if in Debug mode and ENABLE_COVERAGE is defined
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
    endif()

    # Enable debugging symbols (-g) and profiling (-pg)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

    set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

endif()

# ------------------------------------------------------------------------------
# Collect source files for each library separately
# ------------------------------------------------------------------------------
file(GLOB_RECURSE BUSINESS_LOGIC_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/*.cpp
)

file(GLOB_RECURSE DEVICE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/*.cpp
)

file(GLOB_RECURSE DRIVER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/*.cpp
)

# ------------------------------------------------------------------------------
# Add the u8g2 subdirectory (so we can link the u8g2 library below)
# ------------------------------------------------------------------------------
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2
    ${CMAKE_BINARY_DIR}/u8g2_build
)

# ------------------------------------------------------------------------------
# BusinessLogic library
# ------------------------------------------------------------------------------
add_library(BusinessLogic STATIC ${BUSINESS_LOGIC_SRCS})

target_include_directories(BusinessLogic
    PUBLIC
        # "Public" includes for anything that depends on BusinessLogic
        ${CMAKE_CURRENT_SOURCE_DIR}

        # Middlewares
        #${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc
)

target_link_libraries(BusinessLogic
    PRIVATE
        u8g2
)

# ------------------------------------------------------------------------------
# Device library
# ------------------------------------------------------------------------------
add_library(Device STATIC ${DEVICE_SRCS})

target_include_directories(Device
    PUBLIC
        # "Public" includes for anything that depends on Device
        ${CMAKE_CURRENT_SOURCE_DIR}
        # for hack
        #${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/STM32F1xx_HAL_Driver/Inc
        #${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Device/ST/STM32F1xx/Include
        #${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include
        #${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc

        # Middlewares
        #${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc
)




target_link_libraries(Device
    PRIVATE
        u8g2
)

# ------------------------------------------------------------------------------
# Driver library
# ------------------------------------------------------------------------------
add_library(Driver STATIC ${DRIVER_SRCS})

# Depends on if this is build for hardware or simulation we will set other headers.
# We cant use headers for hardware because they have macros and other things 
# that wont compile on x86
if(USE_X86_HEADERS)

    target_include_directories(Driver
    PUBLIC
        # "Public" includes for anything that depends on Driver
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Test/Unit/System

) 
else()

    target_include_directories(Driver
    PUBLIC
        # "Public" includes for anything that depends on Driver
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/STM32F1xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Device/ST/STM32F1xx/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc
 
        # Middlewares
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/
        # Driver doesn't need u8g2 because this lib is high level.
        # I will leave it commented if fast hack wold be needed. 
        #${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc
        #${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc        
) 
endif()

#target_link_libraries(Driver
#    PRIVATE
#        u8g2
#)
