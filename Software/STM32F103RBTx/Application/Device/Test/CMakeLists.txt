cmake_minimum_required(VERSION 3.28)
project(DeviceUnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS cppm)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest) 

add_custom_target(test_dev
    COMMAND ${CMAKE_CTEST_COMMAND} -L "Device" --output-on-failure
    COMMENT "Running Device Layer Unit Tests..."
    USES_TERMINAL
)

# --- Helper Functions ---

function(add_common_flags target)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

    # Sanitizers (Debug Builds Only)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -g -O0 -fprofile-arcs -ftest-coverage)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        target_link_libraries(${target} PRIVATE gcov)
    endif()
endfunction()

# --- Main Function: create_module_test ---

function(create_module_test TARGET_NAME TEST_FILE)

    add_executable(${TARGET_NAME} ${TEST_FILE})

    if(DEFINED EXPORT_SINGLE_JSON AND EXPORT_SINGLE_JSON STREQUAL "${TARGET_NAME}")
        message(STATUS "Enabling compile_commands.json export for: ${TARGET_NAME}")
        set_target_properties(${TARGET_NAME} PROPERTIES EXPORT_COMPILE_COMMANDS ON)
    endif()

    # --- Do NOT quote ARGN here. We want a list, not a single string. ---
    set(MODULE_FILES ${ARGN}) 

    if(MODULE_FILES)
        set(LIB_NAME "SUT_${TARGET_NAME}")
        
        set(ABS_FILES_LIST "")
        set(BASE_DIRS_LIST "")

        foreach(MOD ${MODULE_FILES})
            # 1. Convert to Absolute Path (Safe against ../../ logic)
            get_filename_component(MOD_ABS "${MOD}" ABSOLUTE)
            
            # 2. Extract the directory
            get_filename_component(MOD_DIR "${MOD_ABS}" DIRECTORY)

            # 3. Add to our lists
            list(APPEND ABS_FILES_LIST "${MOD_ABS}")
            list(APPEND BASE_DIRS_LIST "${MOD_DIR}")
        endforeach()

        # 4. Remove duplicate directories to keep the File Set clean
        list(REMOVE_DUPLICATES BASE_DIRS_LIST)

        # 5. Create Library
        add_library(${LIB_NAME} STATIC "${ABS_FILES_LIST}")
        
        # 6. Define File Set
        target_sources(${LIB_NAME} PUBLIC
            FILE_SET CXX_MODULES 
            BASE_DIRS ${BASE_DIRS_LIST}
            FILES ${ABS_FILES_LIST}
        )

         target_include_directories(${LIB_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/../../Driver/Hardware/Test/Stubs"
        )

        target_link_libraries(${TARGET_NAME} PRIVATE ${LIB_NAME})
    endif()

    target_link_libraries(${TARGET_NAME} PRIVATE
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
    )

    add_common_flags(${TARGET_NAME})
    
    # --- Removed the duplicate call to gtest_discover_tests ---
    gtest_discover_tests(${TARGET_NAME} PROPERTIES LABELS "Device")
    
    add_dependencies(test_dev ${TARGET_NAME})
endfunction()

# --- Test Definitions ---

create_module_test(test_Crc32 
    test_Crc32.cpp 
    ../Modules/Crc32.cppm
)

create_module_test(test_CobsEncoder 
    test_CobsEncoder.cpp 
    ../Modules/CobsEncoder.cppm
)

#create_module_test(test_Keyboard 
#    test_Keyboard.cpp 
#    ../Modules/Keyboard.cppm
#    ../Modules/DeviceComponent.cppm
#    ../Modules/KeyAction.cppm
#    ../../Driver/Hardware/Modules/KeyboardDriver.cppm
#    ../../Driver/Interface/KeyId.cppm
#    ../../Driver/Interface/KeyState.cppm
#    ../../Driver/Interface/DriverComponent.cppm
#    ../../Driver/Interface/KeyboardDriverConcept.cppm
#)




