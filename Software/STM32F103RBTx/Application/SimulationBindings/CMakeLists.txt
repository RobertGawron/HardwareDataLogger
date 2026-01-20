add_library(SimulationBindings SHARED)

target_sources(SimulationBindings PRIVATE
 # EventHandlers.cppm
  LibWrapper.cppm
)

target_include_directories(SimulationBindings PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SimulationBindings PRIVATE
  BusinessLogic
  Device
  Driver
  u8g2
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