cmake_minimum_required(VERSION 4.3.1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(SimulationBindings SHARED)

target_sources(SimulationBindings PUBLIC 
  FILE_SET CXX_MODULES 
    FILES
      LibWrapper.cppm
)

target_link_libraries(SimulationBindings PRIVATE
  BusinessLogic
  Device
  Driver
)

set_target_properties(SimulationBindings PROPERTIES
  OUTPUT_NAME "simulator_stm32f103"
  VERSION 1.0.0
  SOVERSION 1
)

install(TARGETS SimulationBindings
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)