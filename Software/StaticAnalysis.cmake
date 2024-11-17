# Find the cppcheck executable
find_program(CPPCHECK_EXECUTABLE cppcheck)
find_program(CPPCHECK_HTMLREPORT_EXECUTABLE cppcheck-htmlreport)

if(CPPCHECK_EXECUTABLE)
    # Define the source directories to check
    set(CPPCHECK_SOURCE_DIRS ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/)

    # Define the output directory for the XML and HTML report
    set(CPPCHECK_REPORT_DIR ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalyse)
    file(MAKE_DIRECTORY ${CPPCHECK_REPORT_DIR})  # Ensure the directory exists

    # Define the XML report output path
    set(CPPCHECK_XML_OUTPUT ${CPPCHECK_REPORT_DIR}/CppCheckResults.xml)

    # Define options for cppcheck
    set(CPPCHECK_OPTIONS
        --enable=all              # Enable all checks
        --inconclusive            # Include inconclusive checks
        --std=c++11               # Specify C++ standard
        --language=c++            # Specify language
        --quiet                   # Suppress verbose output
        --force                   # Force checking of all files
        --suppress=missingIncludeSystem # Suppress missing include errors (common with system includes)
        --xml                     # Output results in XML format
        --output-file=${CPPCHECK_XML_OUTPUT}  # Output XML to the report directory
    )

    # Add a custom target for running cppcheck
    add_custom_target(static
        COMMAND ${CPPCHECK_EXECUTABLE} ${CPPCHECK_OPTIONS} ${CPPCHECK_SOURCE_DIRS}
        COMMENT "Running cppcheck on Application/ folder..."
        VERBATIM
    )

    # If cppcheck-htmlreport is found, generate an HTML report
    if(CPPCHECK_HTMLREPORT_EXECUTABLE)
        add_custom_command(TARGET static
            POST_BUILD
            COMMAND ${CPPCHECK_HTMLREPORT_EXECUTABLE}
                --file=${CPPCHECK_XML_OUTPUT}
                --report-dir=${CPPCHECK_REPORT_DIR}
                --source-dir=${CMAKE_SOURCE_DIR}
            COMMENT "Generating HTML report from cppcheck results..."
            VERBATIM
        )
    else()
        message(WARNING "cppcheck-htmlreport not found. Skipping HTML report generation.")
    endif()


    # Add a custom command to check for cppcheck errors
    add_custom_command(TARGET static POST_BUILD
        COMMAND bash -c "grep -v 'unmatchedSuppression|missingInclude' ${CPPCHECK_XML_OUTPUT} | grep error | wc -l > ${CPPCHECK_REPORT_DIR}/error_count.txt"
        COMMENT "Checking for cppcheck errors..."
        VERBATIM
    )

    # Fail the build if there are errors
    add_custom_command(TARGET static POST_BUILD
        COMMAND bash -c "if [ \$(cat ${CPPCHECK_REPORT_DIR}/error_count.txt) -ne 0 ]; then echo 'Cppcheck found errors!'; exit 1; fi"
        COMMENT "Failing the build if cppcheck finds errors..."
        VERBATIM
    )


else()
    message(WARNING "cppcheck not found. Skipping static analysis.")
endif()
