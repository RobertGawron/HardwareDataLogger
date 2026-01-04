# Define the source directories to analyze
set(CODECHECKER_SOURCE_DIRS
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/BusinessLogic
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Device
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver
   # ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator
)

# Define the output directories for CodeChecker analysis and reports
set(CODECHECKER_ANALYZE_DIR ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysisIntermediary)
set(CODECHECKER_REPORT_DIR ${CMAKE_BINARY_DIR}/BuildArtifacts/StaticAnalysis)
set(CODECHECKER_SKIP_FILE ${CMAKE_SOURCE_DIR}/DevOps/Scripts/CodeCheckerSkipList)

# Ensure the output directories exist
file(MAKE_DIRECTORY ${CODECHECKER_ANALYZE_DIR})
file(MAKE_DIRECTORY ${CODECHECKER_REPORT_DIR})

# Expected HTML output file
set(CODECHECKER_HTML_INDEX ${CODECHECKER_REPORT_DIR}/index.html)

# Add a custom command that produces the HTML output
add_custom_command(
    OUTPUT ${CODECHECKER_HTML_INDEX}
    
    # Step 1: Run analysis
    COMMAND CodeChecker analyze compile_commands.json
        --output ${CODECHECKER_ANALYZE_DIR}
        --file ${CODECHECKER_SOURCE_DIRS}
        --skip ${CODECHECKER_SKIP_FILE}
        --jobs 1
        --enable-all
        --disable clang-diagnostic-pre-c++20-compat-pedantic
        --disable checker:clang-diagnostic-c++98-compat
        --disable modernize-use-trailing-return-type
        --disable modernize-use-auto
        --disable altera-unroll-loops
        --disable cppcheck-missingIncludeSystem
        --disable cppcheck-toomanyconfigs
        --disable checker:clang-diagnostic-padded
        --disable altera-struct-pack-align
        --disable clang-diagnostic-weak-vtables
        --disable altera-id-dependent-backward-branch
        --disable bugprone-easily-swappable-parameters
        --disable clang-diagnostic-covered-switch-default
    
    # Step 2: Generate HTML report
    COMMAND CodeChecker parse ${CODECHECKER_ANALYZE_DIR}
        --skip ${CODECHECKER_SKIP_FILE}
        --export html
        --output ${CODECHECKER_REPORT_DIR}
    
    # Step 3: Check for errors and fail if found
    COMMAND bash -c "if CodeChecker parse ${CODECHECKER_ANALYZE_DIR} --print-issues | grep -qi 'error'; then echo 'CodeChecker found errors!'; exit 1; fi"
    
    DEPENDS compile_commands.json
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running CodeChecker analysis, generating HTML report, and checking for errors..."
    VERBATIM
)

# Add the custom target that depends on the HTML output
add_custom_target(cstatic
    DEPENDS ${CODECHECKER_HTML_INDEX}
)

# Message if CodeChecker is not found (optional)
find_program(CODECHECKER_EXECUTABLE CodeChecker)
if(NOT CODECHECKER_EXECUTABLE)
    message(WARNING "CodeChecker not found. Skipping static analysis.")
endif()