cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(BusinessLogic STATIC)

# Module interface files
target_sources(BusinessLogic PUBLIC FILE_SET CXX_MODULES FILES
    Modules/ApplicationComponent.cppm
    Modules/ApplicationFacade.cppm
    Modules/HmiFacade.cppm
    Modules/MeasurementCoordinator.cppm
)

target_sources(BusinessLogic PRIVATE
    Src/ApplicationFacade.cpp
    Src/HmiFacade.cpp
)

target_link_libraries(BusinessLogic PRIVATE
    Device
    Driver
    DriverInterface
    u8g2
)

target_include_directories(BusinessLogic PRIVATE
    ../Library/u8g2/cppsrc
)