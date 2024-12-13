cmake_minimum_required(VERSION 3.10)
project(ApplicationLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# For Debug
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Helper function to print include directories for a target
function(print_include_dirs target_name)
    message(STATUS "Include directories for target ${target_name}:")
    get_target_property(include_dirs ${target_name} INCLUDE_DIRECTORIES)
    foreach(dir ${include_dirs})
        message(STATUS "  ${dir}")
    endforeach()
endfunction()

# Enable coverage flags if in Debug mode and ENABLE_COVERAGE is defined
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

# Compiler flags for ARM target and CPU (Cortex-M3) using the arm-none-eabi toolchain

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TARGET_FLAGS}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/STM32F1xx_HAL_Driver/Inc/")
# Check if USE_X86_HEADERS is defined
if(USE_X86_HEADERS)
    # If USE_X86_HEADERS is true, include X86 headers for unit testing
    include_directories("${CMAKE_SOURCE_DIR}/Test/UT/System")
else()
    # Else, include STM32-specific headers for the STM32F103RBTx
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/STM32F1xx_HAL_Driver/Inc/")
   
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include")
   
    
   # include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/FatFs/src/")
endif()
message(STATUS "VariableName: ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc/")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../FATFS/Target/")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../cubeide-sd-card/cubeide-sd-card/Drivers/CMSIS/Include/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Device/ST/STM32F1xx/Include/")

#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../FATFS/App/")


file(GLOB BUSINESS_LOGIC_SRC "${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/*.cpp")
file(GLOB DEVICE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/*.cpp")
file(GLOB DRIVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/*.cpp")


# Add u8g2 as a subdirectory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2 ${CMAKE_BINARY_DIR}/u8g2_build)

# Link the u8g2 library (produced by its own CMakeLists.txt) to ApplicationLib
#target_link_libraries(${PROJECT_NAME} PRIVATE u8g2)


# Add library target for each module
add_library(BusinessLogic STATIC ${BUSINESS_LOGIC_SRC})
add_library(Device STATIC ${DEVICE_SRC})
add_library(Driver STATIC ${DRIVER_SRC})

# Add include paths for Driver library
target_include_directories(Driver PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/stm32-st7735/"
)

target_include_directories(BusinessLogic PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc"
)
target_include_directories(Device PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/cppsrc"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/u8g2/csrc"
)

print_include_dirs(BusinessLogic)
print_include_dirs(Device)

# Add the main ApplicationLib shared library and link the individual module libraries
add_library(${PROJECT_NAME} STATIC ${BUSINESS_LOGIC_SRC} ${DEVICE_SRC} ${DRIVER_SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE u8g2)
# Link the individual libraries to the main library
#target_link_libraries(${PROJECT_NAME} PRIVATE BusinessLogic Device Driver)
