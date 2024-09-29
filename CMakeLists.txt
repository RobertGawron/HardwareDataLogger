cmake_minimum_required(VERSION 3.15)
project(HardwareDataLogger)

# Global compiler settings (use sparingly)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the flag to choose between X86 and ARM headers
set(USE_X86_HEADERS TRUE)  # Set this to TRUE for X86, FALSE for ARM

add_subdirectory(Software/NUCLEO-F103RB/Application)
add_subdirectory(Simulation/FirmwarePCSimulator)
add_subdirectory(Test/UT)

include(Software/StaticAnalysis.cmake)
include(Software/ClassDiagram.cmake)
include(Software/DocsCoverage.cmake)
