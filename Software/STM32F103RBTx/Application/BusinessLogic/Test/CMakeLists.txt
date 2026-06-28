cmake_minimum_required(VERSION 4.3.1)

project(BusinessLogicUnitTests LANGUAGES CXX)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include(GoogleTest)  # provides gtest_discover_tests()

add_executable(test_MeasurementCoordinator
  test_MeasurementCoordinator.cpp
)

target_link_libraries(test_MeasurementCoordinator PRIVATE
  BusinessLogic
  GTest::gtest_main
  GTest::gmock_main
  Threads::Threads
)

target_compile_options(test_MeasurementCoordinator PRIVATE
  -Wall -Wextra -Wpedantic
)

# Optional: sanitizers (Debug only)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(test_MeasurementCoordinator PRIVATE -fsanitize=address,undefined -O0 -g)
  target_link_options(test_MeasurementCoordinator PRIVATE -fsanitize=address,undefined)
endif()

gtest_discover_tests(test_MeasurementCoordinator
  PROPERTIES
    LABELS "BusinessLogic"
)