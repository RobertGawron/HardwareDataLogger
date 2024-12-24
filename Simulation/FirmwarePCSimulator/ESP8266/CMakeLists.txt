# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(SimulatorESP8266 LANGUAGES C CXX)

# Enable position-independent code for compatibility with shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdinc")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc -nostdinc++")


# Include directories scoped to each target
set(INCLUDE_DIRS
BEFORE # The BEFORE keyword ensures that these directories are prioritized over the system's include paths.


    #${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/u8g2/csrc
    #${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Core/Inc
    #${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/STM32F103RBTx/Application/Driver/Inc
   # ${CMAKE_SOURCE_DIR}/Software/ESP8266/.pio/libdeps/huzzah/PubSubClient/src
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/

    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/Mocks/Inc/
    #${CMAKE_SOURCE_DIR}/Software/ESP8266/.pio/libdeps/huzzah/PubSubClient/src

   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/cores/esp8266/
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/tools/sdk/include/
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/variants/adafruit
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/tools/sdk/lwip2/include/
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/framework-arduinoespressif8266/libraries/ESP8266WiFi/src/
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/toolchain-xtensa/xtensa-lx106-elf/include/
    


    

    

    
)

file(GLOB SIMULATOR_MAIN_SRC
    "${CMAKE_SOURCE_DIR}/Software/ESP8266/src/*.cpp"
     "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/*.cpp"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/Mocks/Src/*.cpp"
#    "${CMAKE_SOURCE_DIR}/Software/ESP8266/.pio/libdeps/huzzah/PubSubClient/src/*.cpp"

)


# Define DriverForSimulation as a shared library
add_library(MainSource SHARED ${SIMULATOR_MAIN_SRC})
target_include_directories(MainSource PRIVATE ${INCLUDE_DIRS})


# C:\Users\rober\Documents\HardwareDataLogger\Software\ESP8266\.vscode\c_cpp_properties.json
target_compile_definitions(MainSource PRIVATE 
    PLATFORMIO=60116
    ESP8266
    ARDUINO_ARCH_ESP8266
    ARDUINO_ESP8266_ADAFRUIT_HUZZAH
    F_CPU=80000000L
    __ets__
    ICACHE_FLASH
    _GNU_SOURCE
    ARDUINO=10805
    ARDUINO_BOARD="PLATFORMIO_HUZZAH"
    ARDUINO_BOARD_ID="huzzah"
    FLASHMODE_QIO
    LWIP_OPEN_SRC
    NONOSDK22x_190703=1
    TCP_MSS=536
    LWIP_FEATURES=1
    LWIP_IPV6=0
    VTABLES_IN_FLASH
    MMU_IRAM_SIZE=0x8000
    MMU_ICACHE_SIZE=0x8000
)

# Define FirmwarePCSimulator as the main shared library
set(SIMULATOR_SRC ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/LibWrapper.cpp)
add_library(SimulatorESP8266 SHARED ${SIMULATOR_SRC})
target_include_directories(SimulatorESP8266 PRIVATE ${INCLUDE_DIRS})

target_link_libraries(SimulatorESP8266
MainSource 
)
