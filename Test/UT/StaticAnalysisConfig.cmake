# Find the cppcheck executable
find_program(CPPCHECK_EXECUTABLE cppcheck)
find_program(CPPCHECK_HTMLREPORT_EXECUTABLE cppcheck-htmlreport)

if(CPPCHECK_EXECUTABLE)
    # Define the source directories to check
    set(CPPCHECK_SOURCE_DIRS ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/)

    # Define the output directory for HTML report
    set(CPPCHECK_REPORT_DIR ${CMAKE_BINARY_DIR}/static_analyse)

    # Define options for cppcheck
    set(CPPCHECK_OPTIONS
        --enable=all          # Enable all checks
        --inconclusive        # Include inconclusive checks
        --std=c++11           # Specify C++ standard
        --language=c++        # Specify language
        --quiet               # Suppress verbose output
        --force               # Force checking of all files
        --suppress=missingIncludeSystem # Suppress missing include errors (common with system includes)
        --xml                   # Output results in XML format
    )

    # Add a custom target for running cppcheck
    add_custom_target(static_analyse
        COMMAND ${CPPCHECK_EXECUTABLE} ${CPPCHECK_OPTIONS} ${CPPCHECK_SOURCE_DIRS} 2> cppcheck_results.xml
        COMMENT "Running cppcheck on Application/ folder..."
        VERBATIM
    )

    if(CPPCHECK_HTMLREPORT_EXECUTABLE)
        add_custom_command(TARGET static_analyse
            POST_BUILD
            COMMAND ${CPPCHECK_HTMLREPORT_EXECUTABLE} --file=cppcheck_results.xml --report-dir=${CPPCHECK_REPORT_DIR} --source-dir=${CMAKE_SOURCE_DIR}
            COMMENT "Generating HTML report from cppcheck results..."
            VERBATIM
        )
    else()
        message(WARNING "cppcheck-htmlreport not found. Skipping HTML report generation.")
    endif()
else()
    message(WARNING "cppcheck not found. Skipping static analysis.")
endif()