cmake_minimum_required(VERSION 3.15)
project(HardwareDataLogger)

# Global compiler settings (use sparingly)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the flag to choose between X86 and ARM headers
set(USE_X86_HEADERS TRUE)  # Set this to TRUE for X86, FALSE for ARM

add_subdirectory(Software/STM32F103RBTx/Application)
add_subdirectory(Simulation/FirmwarePCSimulator/STM32F103RBTx)
add_subdirectory(Simulation/FirmwarePCSimulator/ESP8266)
add_subdirectory(Test/Unit)

# Include the DevOps scripts (static code analysis, etc.)
include(DevOps/Cmake/CStaticAnalysis.cmake)
include(DevOps/Cmake/PythonStaticAnalysis.cmake)
include(DevOps/Cmake/DocsCoverage.cmake)
include(DevOps/Cmake/ClassDiagram.cmake)


