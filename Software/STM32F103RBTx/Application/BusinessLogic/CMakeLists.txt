cmake_minimum_required(VERSION 3.28)
project(BusinessLogic LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BusinessLogic library
add_library(BusinessLogic STATIC)

target_sources(BusinessLogic PRIVATE
    Src/ApplicationBuilder.cpp
    Src/HmiFactory.cpp
    Src/HmiMeasurementModel.cpp
    Src/HmiMui.cpp
    Src/HmiMuiHandlers.cpp
    Src/MeasurementCoordinator.cpp
    Src/MeasurementDataStore.cpp
    Src/MeasurementSourcesFactory.cpp
    Src/MeasurementStoresFactory.cpp
)

target_include_directories(BusinessLogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)
