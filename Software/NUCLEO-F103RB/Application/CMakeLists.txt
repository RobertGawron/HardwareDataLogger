# BusinessLogic/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(BusinessLogic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

# Include directories for all modules
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Inc)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Inc)

include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Interfaces)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Interfaces)
include_directories(${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Interfaces)

# Some files in Driver/ use platform related headers, those are mocks for it.
# In generall I dont want any stm32 relted headers in unit tests.
include_directories(${CMAKE_SOURCE_DIR}/Test/UT/System/)

include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Middlewares/Third_Party/stm32-st7735/st7735/
    
) 


# Source files for each module
set(BUSINESS_LOGIC_SRC
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/ApplicationBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiDataModel.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiInputController.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiViewHistogram.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiViewMain.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/HmiViewManager.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/MeasurementCoordinator.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/MeasurementDataStore.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/MeasurementSourcesBuilder.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Src/MeasurementStoresBuilder.cpp
)

set(DEVICE_SRC
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/DisplayBrightnessRegulator.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/Keyboard.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/PulseCounterMeasurementSource.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/SdCardMeasurementRecorder.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/UartMeasurementRecorder.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/UartMeasurementSource.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Src/WiFiMeasurementRecorder.cpp
)

set(DRIVER_SRC
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/AmbientLightSensorDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/KeyboardFourPushButtonsDriver.cpp
#    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/SdCardDriver.cpp
   ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/St7735DisplayBrightnessDriver.cpp
#    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/St7735DisplayDriver.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/UartDriver.cpp
)

# Add library target for each module
add_library(BusinessLogic ${BUSINESS_LOGIC_SRC})
add_library(Device ${DEVICE_SRC})
add_library(Driver ${DRIVER_SRC})

# If libraries use threading, link them with pthread
find_package(Threads REQUIRED)  # Find the threads package
target_link_libraries(BusinessLogic Threads::Threads)
target_link_libraries(Device Threads::Threads)
target_link_libraries(Driver Threads::Threads)

# Enable testing
enable_testing()



