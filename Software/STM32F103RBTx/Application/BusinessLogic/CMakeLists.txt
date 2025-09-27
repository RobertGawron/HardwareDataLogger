cmake_minimum_required(VERSION 3.28)
project(BusinessLogic LANGUAGES CXX)

# BusinessLogic library
add_library(BusinessLogic STATIC)

target_sources(BusinessLogic PRIVATE
    Src/ApplicationFacade.cpp
    Src/HmiFacade.cpp
)

target_include_directories(BusinessLogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)
