cmake_minimum_required(VERSION 3.28)
project(HardwareDataLogger)

# Global compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg")
    
    add_subdirectory(Software/STM32F103RBTx/Application/Device/Test)
    add_subdirectory(Software/STM32F103RBTx/Application/Driver/Hardware/Test)
    add_subdirectory(Software/STM32F103RBTx/Application/BusinessLogic/Test)

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_subdirectory(Software/STM32F103RBTx/Application/Library/u8g2/)
    add_subdirectory(Software/STM32F103RBTx/Application/BusinessLogic/)
    add_subdirectory(Software/STM32F103RBTx/Application/Device/)
    add_subdirectory(Software/STM32F103RBTx/Application/Driver/Host)
    

    # Run Business Logic tests
    add_custom_target(ut_biz
        
        COMMAND ${CMAKE_CTEST_COMMAND} -R "test_BusinessLogic" --output-on-failure
        COMMENT "Running Business Logic Unit Tests..."
    )

    # Run Device tests
    add_custom_target(ut_dev
        COMMAND ${CMAKE_CTEST_COMMAND} -R "test_Device" --output-on-failure
        COMMENT "Running Device Unit Tests..."
    )

    # Run Driver tests
    add_custom_target(ut_drv
        COMMAND ${CMAKE_CTEST_COMMAND} -R "test_Driver" --output-on-failure
        COMMENT "Running Driver Unit Tests..."
    )

    # Run all unit tests
    add_custom_target(ut_all
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMENT "Running All Unit Tests..."
    )

    # Code coverage for C++
    include(Software/STM32F103RBTx/Application/CodeCoverage.cmake)
    include(DevOps/Cmake/CStaticAnalysis.cmake)
    include(DevOps/Cmake/PythonStaticAnalysis.cmake)
    include(DevOps/Cmake/DocsCoverage.cmake)
    include(DevOps/Cmake/ClassDiagram.cmake)
    
endif()


add_custom_target(firmware
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/firmware-build
    COMMAND ${CMAKE_COMMAND} 
        -S ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx
        -B ${CMAKE_BINARY_DIR}/firmware-build
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/cmake/gcc-arm-none-eabi.cmake
        -DCMAKE_BUILD_TYPE=Release
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/firmware-build
    COMMENT "Building STM32 firmware..."
    USES_TERMINAL
)



add_custom_target(cstatic_stm
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/firmware-build
    COMMAND ${CMAKE_COMMAND} 
        -S ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx
        -B ${CMAKE_BINARY_DIR}/firmware-build
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/cmake/gcc-arm-none-eabi.cmake
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/firmware-build
    COMMAND ${CMAKE_COMMAND} -E echo "Copying compile_commands.json..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/firmware-build/compile_commands.json
        ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E echo "Successfully copied compile_commands.json to ${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target cstatic
    COMMENT "Building firmware and exporting compile commands..."
    USES_TERMINAL
    VERBATIM
)