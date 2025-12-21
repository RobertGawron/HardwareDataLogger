cmake_minimum_required(VERSION 3.15)
project(HardwareDataLogger)

# Global compiler settings (use sparingly)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg")
    
    add_subdirectory(Software/STM32F103RBTx/Application/BusinessLogic/Test)
    add_subdirectory(Software/STM32F103RBTx/Application/Device/Test)
    add_subdirectory(Software/STM32F103RBTx/Application/Driver/Test)

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