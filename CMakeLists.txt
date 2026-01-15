cmake_minimum_required(VERSION 3.28)
project(HardwareDataLogger)

# Global compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define ARM target for static analysis (STM32F103 = Cortex-M3)
set(ARM_STATIC_ANALYSIS_TARGET "thumbv7m-none-eabi" CACHE STRING "ARM target for static analysis")

option(BUILD_IS_FOR_HARDWARE "Build for STM32 hardware" OFF)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg")
    


    
endif()

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_subdirectory(Software/STM32F103RBTx/Application/Library/u8g2/)
    add_subdirectory(Software/STM32F103RBTx/Application/Driver/)
    add_subdirectory(Software/STM32F103RBTx/Application/Device/)
    add_subdirectory(Software/STM32F103RBTx/Application/BusinessLogic/)
    add_subdirectory(Software/STM32F103RBTx/Application/SimulationBindings/)

    


    include(Software/STM32F103RBTx/Application/CodeCoverage.cmake)
    include(DevOps/Cmake/CStaticAnalysis.cmake)
    include(DevOps/Cmake/PythonStaticAnalysis.cmake)
    include(DevOps/Cmake/DocsCoverage.cmake)

add_custom_target(firmware
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/firmware-build
    COMMAND ${CMAKE_COMMAND} 
        -S ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx
        -B ${CMAKE_BINARY_DIR}/firmware-build
        -G Ninja
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/cmake/gcc-arm-none-eabi.cmake
        -DCMAKE_BUILD_TYPE=Release
        -DBUILD_IS_FOR_HARDWARE=ON
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/firmware-build --parallel
    COMMENT "Building STM32 firmware with Ninja..."
    USES_TERMINAL
)



add_custom_target(cstatic_stm
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/firmware-build
    
    # Configure and build firmware with ARM toolchain using Ninja
    COMMAND ${CMAKE_COMMAND} 
        -S ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx
        -B ${CMAKE_BINARY_DIR}/firmware-build
        -G Ninja
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/cmake/gcc-arm-none-eabi.cmake
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/firmware-build --parallel
    
    # Ensure output directories exist
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysisIntermediary
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysis
    
    # Run CodeChecker directly with ARM target (Clang only to avoid GCC compatibility issues)
    COMMAND ${CMAKE_COMMAND} -E echo "Running static analysis on firmware with target ${ARM_STATIC_ANALYSIS_TARGET}..."
    COMMAND CodeChecker analyze 
        ${CMAKE_BINARY_DIR}/firmware-build/compile_commands.json
        --output ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysisIntermediary
        --analyzers clangsa
        --file ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic
        --file ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device
        --file ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver
        --skip ${CMAKE_SOURCE_DIR}/DevOps/Scripts/CodeCheckerSkipList
        --jobs 1
        --enable-all
        --ctu
    
    # Generate HTML report
    COMMAND ${CMAKE_COMMAND} -E echo "Generating HTML report..."
    COMMAND CodeChecker parse 
        ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysisIntermediary
        --skip ${CMAKE_SOURCE_DIR}/DevOps/Scripts/CodeCheckerSkipList
        --export html
        --output ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysis
    
    # Check for errors and fail if found
    COMMAND ${CMAKE_COMMAND} -E echo "Checking for critical errors..."
    COMMAND bash -c "if [ -n \"\$(CodeChecker parse ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysisIntermediary --print-issues | grep -i 'error')\" ]; then echo 'CodeChecker found errors!'; exit 1; fi"
    
    COMMENT "Building firmware with Ninja and running static analysis (target: ${ARM_STATIC_ANALYSIS_TARGET})..."
    USES_TERMINAL
    VERBATIM
)