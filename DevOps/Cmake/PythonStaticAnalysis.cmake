# ------------------------------------------------------------------------------
# Python static analysis: Prospector reports
# ------------------------------------------------------------------------------

# Where to write the final reports (default: repo DevOps BuildArtifacts)
set(PYTHON_REPORT_DIR_DEFAULT "${CMAKE_SOURCE_DIR}/DevOps/BuildArtifacts/PythonStaticAnalysis")
set(PYTHON_REPORT_DIR "${PYTHON_REPORT_DIR_DEFAULT}" CACHE PATH "Output directory for Python static analysis reports")

# Optional: workspace/temp dir used by the analysis (default: in build tree)
set(PYTHON_ANALYZE_DIR_DEFAULT "${CMAKE_BINARY_DIR}/BuildArtifacts/PythonStaticAnalysisWork")
set(PYTHON_ANALYZE_DIR "${PYTHON_ANALYZE_DIR_DEFAULT}" CACHE PATH "Working directory for Python static analysis (temporary)")

file(MAKE_DIRECTORY "${PYTHON_ANALYZE_DIR}")
file(MAKE_DIRECTORY "${PYTHON_REPORT_DIR}")

set(PYTHON_STATIC_ANALYSIS_SCRIPT "${CMAKE_SOURCE_DIR}/DevOps/Scripts/PythonStaticAnalysis.sh")

add_custom_target(pstatic
    COMMAND bash -lc
      "set -euo pipefail;
       dos2unix '${PYTHON_STATIC_ANALYSIS_SCRIPT}';
       export PYTHON_ANALYZE_DIR='${PYTHON_ANALYZE_DIR}';
       export PYTHON_REPORT_DIR='${PYTHON_REPORT_DIR}';
       source '${PYTHON_STATIC_ANALYSIS_SCRIPT}'"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Running Python static analysis with Prospector and generating reports..."
    VERBATIM
)