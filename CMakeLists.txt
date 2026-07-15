cmake_minimum_required(VERSION 4.3.1)

project(HardwareDataLogger LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Language / modules policy ----
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ---- Testing ----
include(CTest)
enable_testing()

# ---- Options to control what is built (used by presets) ----
option(BUILD_IS_FOR_HARDWARE "Build for STM32 hardware" OFF)

option(HDL_BUILD_DRIVER   "Build Driver layer" ON)
option(HDL_BUILD_DEVICE   "Build Device layer" ON)
option(HDL_BUILD_BUSINESS "Build BusinessLogic layer" ON)
option(HDL_BUILD_SIMBIND  "Build SimulationBindings" OFF)

option(HDL_BUILD_TESTS_DRIVER   "Build Driver unit tests" OFF)
option(HDL_BUILD_TESTS_DEVICE   "Build Device unit tests" OFF)
option(HDL_BUILD_TESTS_BUSINESS "Build BusinessLogic unit tests" OFF)

option(ENABLE_COVERAGE "Enable GCC coverage instrumentation" OFF)

# ---- Debug flags: avoid forcing -pg globally ----
option(HDL_ENABLE_GPROF "Enable -pg profiling instrumentation (host only)" OFF)
if(HDL_ENABLE_GPROF)
  add_compile_options(-pg)
  add_link_options(-pg)
endif()



if(ENABLE_COVERAGE AND NOT BUILD_IS_FOR_HARDWARE)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Coverage instrumentation enabled")

    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
  endif()
endif()

# ---- Source tree root ----
set(HARDWARE_APP_DIR "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application")

# ---- Dependencies / layers ----
if(HDL_BUILD_DRIVER)
  add_subdirectory("${HARDWARE_APP_DIR}/Driver")
endif()

if(HDL_BUILD_DEVICE)
  add_subdirectory("${HARDWARE_APP_DIR}/Device")
endif()

if(HDL_BUILD_BUSINESS)
  add_subdirectory("${HARDWARE_APP_DIR}/BusinessLogic")
endif()

if(HDL_BUILD_SIMBIND)
  add_subdirectory("${HARDWARE_APP_DIR}/SimulationBindings")
endif()

# ---- Unit tests ----
if(BUILD_TESTING)
  if(HDL_BUILD_TESTS_BUSINESS)
    add_subdirectory("${HARDWARE_APP_DIR}/BusinessLogic/Test")
  endif()

  if(HDL_BUILD_TESTS_DEVICE)
    add_subdirectory("${HARDWARE_APP_DIR}/Device/Test")
  endif()

endif()


# ---- Tooling targets (optional; should be guarded so unit builds stay small) ----
option(HDL_ENABLE_TOOLING_TARGETS "Enable tooling targets like integration/docs/static analysis" ON)
if(HDL_ENABLE_TOOLING_TARGETS)

  include("${HARDWARE_APP_DIR}/CodeCoverage.cmake" OPTIONAL)
#  include("${CMAKE_SOURCE_DIR}/DevOps/Cmake/CStaticAnalysis.cmake" OPTIONAL)
  include("${CMAKE_SOURCE_DIR}/DevOps/Cmake/PythonStaticAnalysis.cmake" OPTIONAL)
#  include("${CMAKE_SOURCE_DIR}/DevOps/Cmake/DocsCoverage.cmake" OPTIONAL)

  find_package(Python3 QUIET COMPONENTS Interpreter)
  if(Python3_Interpreter_FOUND)
    add_custom_target(integration
      COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/BuildArtifacts
      COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/IntegrationTest
              ${Python3_EXECUTABLE} -m pytest -s
              --html=${CMAKE_BINARY_DIR}/BuildArtifacts/IntegrationTest.html
      USES_TERMINAL
    )
  endif()

  # install-sim should only exist if SimulationBindings is built
  add_custom_target(install-local
    COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR}
            --prefix ${CMAKE_SOURCE_DIR}
    COMMENT "Installing SimulationBindings into project root"
    USES_TERMINAL
  )
endif()