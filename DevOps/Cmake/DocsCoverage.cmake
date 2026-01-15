# ------------------------------------------------------------------------------
# Docs coverage target: Doxygen XML + Coverxygen + genhtml (lcov)
# ------------------------------------------------------------------------------

# Find required executables
find_program(DOXYGEN_EXECUTABLE doxygen)
find_program(GENHTML_EXECUTABLE genhtml)

# Use CMake's Python finder so -DPython3_EXECUTABLE=... works
find_package(Python3 REQUIRED COMPONENTS Interpreter)

if(DOXYGEN_EXECUTABLE)
    # Set the source directory and output directory for the Doxygen analysis
    set(DOXYGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/")

    # Default output dir (can be overridden from CLI/VS Code task)
    set(DOXYGEN_OUTPUT_DIR_DEFAULT "${CMAKE_SOURCE_DIR}/BuildArtifacts/DocsCoverage")
    set(DOXYGEN_OUTPUT_DIR "${DOXYGEN_OUTPUT_DIR_DEFAULT}" CACHE PATH "Docs coverage output directory")

    # Ensure the output directory exists
    file(MAKE_DIRECTORY "${DOXYGEN_OUTPUT_DIR}")

    # Set the paths for the Doxyfile template and the final generated Doxyfile
    set(DOXYFILE_IN  "${CMAKE_SOURCE_DIR}/DevOps/Scripts/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_SOURCE_DIR}/DevOps/Scripts/Doxyfile")

    # Create a Doxyfile from template
    configure_file("${DOXYFILE_IN}" "${DOXYFILE_OUT}" @ONLY)

    # Custom target to run Doxygen and generate XML output (needed for Coverxygen)
    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYFILE_OUT}"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        COMMENT "Running Doxygen to detect missing comments and generate XML..."
        VERBATIM
    )

    # Run Coverxygen via Python + generate HTML report via genhtml
    if(Python3_Interpreter_FOUND)
        if(NOT GENHTML_EXECUTABLE)
            message(FATAL_ERROR "genhtml not found. Install it (e.g. apt-get install lcov).")
        endif()

        add_custom_command(TARGET docs
            POST_BUILD
            COMMAND "${Python3_EXECUTABLE}" -m coverxygen --format lcov
                --kind enum,enumvalue,friend,typedef,variable,function,class,struct,union,define
                --xml-dir "${DOXYGEN_OUTPUT_DIR}/xml"
                --src-dir "${DOXYGEN_INPUT_DIR}"
                --output "${DOXYGEN_OUTPUT_DIR}/doc-coverage.info"
            COMMAND "${GENHTML_EXECUTABLE}" --no-function-coverage
                --no-branch-coverage "${DOXYGEN_OUTPUT_DIR}/doc-coverage.info"
                -o "${DOXYGEN_OUTPUT_DIR}"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            COMMENT "Generating Coverxygen documentation coverage report..."
            VERBATIM
        )
    else()
        message(WARNING "Python3 interpreter not found. Skipping Coverxygen coverage report generation.")
    endif()
else()
    message(WARNING "Doxygen not found. Skipping missing documentation check.")
endif()