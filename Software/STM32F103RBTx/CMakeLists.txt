cmake_minimum_required(VERSION 3.28)

if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)
endif()

project(HardwareDataLogger_STM32F103RBTx LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_IS_FOR_HARDWARE "Build for STM32 hardware" ON)
option(DISABLE_DYNAMIC_ALLOCATION "Disable dynamic memory allocation" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_compile_definitions(STM32F103xB)

if(DISABLE_DYNAMIC_ALLOCATION)
    add_compile_definitions(NDEBUG)  # added to disable assert(), by default it uses dynamic allocation for error messages
    add_compile_definitions(NO_DYNAMIC_ALLOCATION)

    add_link_options(
        -Wl,--wrap=malloc
        -Wl,--wrap=calloc
        -Wl,--wrap=realloc
        -Wl,--wrap=free
        -Wl,--wrap=_malloc_r
        -Wl,--wrap=_calloc_r
        -Wl,--wrap=_realloc_r
        -Wl,--wrap=_free_r
        -Wl,--undefined=__wrap_malloc
        -Wl,--undefined=__wrap_calloc
        -Wl,--undefined=__wrap_realloc
        -Wl,--undefined=__wrap_free
    )
endif()

add_executable(${PROJECT_NAME})

add_subdirectory(cmake/stm32cubemx)
add_subdirectory(Application/Driver/)
add_subdirectory(Application/Device/)
add_subdirectory(Application/BusinessLogic/)

target_sources(${PROJECT_NAME} PRIVATE
    Application/Library/stm32-st7735/st7735.c
    Application/Library/stm32-st7735/st7735_reg.c
)

target_sources(${PROJECT_NAME} PRIVATE
    FILE_SET app_modules
    TYPE CXX_MODULES
    FILES Core/Src/MyApplication.cpp
)

#if(DISABLE_DYNAMIC_ALLOCATION)
#    target_sources(${PROJECT_NAME} PRIVATE
#        Core/Src/no_dynamic_alloc.c
#    )
#endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc
    Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32F1xx/Include
    Drivers/CMSIS/Include
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Os
    -flto
    -ffunction-sections
    -fdata-sections

    # C++ only flags
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>

    $<$<CONFIG:Debug>:-g3>
)

target_link_options(${PROJECT_NAME} PRIVATE
    -Wl,--gc-sections
    -Wl,--cref
    -flto
    --specs=nosys.specs
)

target_link_libraries(${PROJECT_NAME}
    stm32cubemx
    DriverInterface
    Driver
    Device
    BusinessLogic
)

add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
            -c "program $<TARGET_FILE:${PROJECT_NAME}> verify reset exit"
    DEPENDS ${PROJECT_NAME}
    USES_TERMINAL
)