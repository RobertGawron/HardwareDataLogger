cmake_minimum_required(VERSION 3.15)
project(HardwareDataLogger)

# Global compiler settings (use sparingly)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Software/NUCLEO-F103RB/Application)
add_subdirectory(Test/UT)
add_subdirectory(Simulation/FirmwarePCSimulator)

include(Software/NUCLEO-F103RB/Application/MissingDoxygen.cmake)
