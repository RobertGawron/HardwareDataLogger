
# Define the output directories for Python static analysis and reports
set(PYTHON_ANALYZE_DIR ${CMAKE_BINARY_DIR}/BuildArtifacts/PythonStaticAnalysis)
set(PYTHON_REPORT_DIR ${CMAKE_BINARY_DIR}/BuildArtifacts)

# Echo the variables for debugging
message(STATUS "PYTHON_ANALYZE_DIR: ${PYTHON_ANALYZE_DIR}")
message(STATUS "PYTHON_REPORT_DIR: ${PYTHON_REPORT_DIR}")

# Ensure the output directories exist
file(MAKE_DIRECTORY ${PYTHON_ANALYZE_DIR})
file(MAKE_DIRECTORY ${PYTHON_REPORT_DIR})

# Add a custom target for Python static analysis
add_custom_target(pystatic
    COMMAND bash -c " \
        /workspace/Simulation/FirmwarePCSimulator/PythonStaticAnalysis.sh"
    COMMENT "Running Python static analysis with Prospector and generating reports..."
    VERBATIM
)
