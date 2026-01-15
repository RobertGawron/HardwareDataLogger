#!/usr/bin/env bash
set -euo pipefail

# ------------------------------------------------------------------------------
# Python static analysis runner (Prospector) + HTML report generation (vjunit)
# Uses venv tools explicitly (no "activate"), so it works in Docker/CI even when
# /workspace is a bind mount.
# ------------------------------------------------------------------------------

VENV_BIN="/opt/venv/bin"
PROSPECTOR="${VENV_BIN}/prospector"
VJUNIT="${VENV_BIN}/vjunit"

# Allow CMake (or caller) to override output locations via environment variables
# Final reports directory (requested):
OUTPUT_DIR="${PYTHON_REPORT_DIR:-/workspace/DevOps/BuildArtifacts/PythonStaticAnalysis}"
# Optional working dir (not strictly required by this script, but kept for symmetry)
WORK_DIR="${PYTHON_ANALYZE_DIR:-/tmp/PythonStaticAnalysisWork}"

mkdir -p "${OUTPUT_DIR}"
mkdir -p "${WORK_DIR}"

# Define output file paths
SYSTEM_XML="${OUTPUT_DIR}/IntegrationTest.xml"
SYSTEM_HTML="${OUTPUT_DIR}/IntegrationTest.html"

SIMULATOR_XML="${OUTPUT_DIR}/FirmwarePCSimulator.xml"
SIMULATOR_HTML="${OUTPUT_DIR}/FirmwarePCSimulator.html"

DRIVER_XML="${OUTPUT_DIR}/DriverHostPython.xml"
DRIVER_HTML="${OUTPUT_DIR}/DriverHostPython.html"

# Initialize exit code tracker
EXIT_CODE=0

# Sanity checks
if [[ ! -x "${PROSPECTOR}" ]]; then
  echo "ERROR: prospector not found/executable at: ${PROSPECTOR}" >&2
  echo "       Ensure the venv exists at /opt/venv and prospector is installed." >&2
  exit 2
fi

if [[ ! -x "${VJUNIT}" ]]; then
  echo "ERROR: vjunit not found/executable at: ${VJUNIT}" >&2
  echo "       Ensure vjunit is installed in the venv at /opt/venv." >&2
  exit 2
fi

# Run Prospector analysis (xUnit output)
# Note: prospector's xunit output is XML (even if you previously called it .json)
"${PROSPECTOR}" --profile /workspace/DevOps/Scripts/.prospector.yaml \
  --strictness veryhigh --doc-warnings --output-format xunit \
  /workspace/IntegrationTest/ > "${SYSTEM_XML}" || EXIT_CODE=1

"${PROSPECTOR}" --profile /workspace/DevOps/Scripts/.prospector.yaml \
  --strictness veryhigh --doc-warnings --output-format xunit \
  /workspace/FirmwarePCSimulator/ > "${SIMULATOR_XML}" || EXIT_CODE=1

"${PROSPECTOR}" --profile /workspace/DevOps/Scripts/.prospector.yaml \
  --strictness veryhigh --doc-warnings --output-format xunit \
  /workspace/Software/STM32F103RBTx/Application/Driver/Simulation/Python/ > "${DRIVER_XML}" || EXIT_CODE=1

# vjunit is broken in original version, so patch it in the venv
find /opt/venv/ -type f -name "vjunit.py" -exec sed -i \
  's/children = testcase\.getchildren()/children = list(testcase)/g' {} +

# Convert xUnit XML reports to HTML using vjunit
"${VJUNIT}" -f "${SYSTEM_XML}" -o "${SYSTEM_HTML}" || echo "Warning: HTML conversion failed for IntegrationTest"
"${VJUNIT}" -f "${SIMULATOR_XML}" -o "${SIMULATOR_HTML}" || echo "Warning: HTML conversion failed for FirmwarePCSimulator"
"${VJUNIT}" -f "${DRIVER_XML}" -o "${DRIVER_HTML}" || echo "Warning: HTML conversion failed for DriverHostPython"

# Expand all tabs in the HTML reports (best effort)
sed -i "/\$('.ui.accordion').accordion();/c\\
\$('.ui.accordion').accordion();\\
\$('.ui.accordion .title').addClass('active');\\
\$('.ui.accordion .content').addClass('active');" \
  "${SYSTEM_HTML}" "${SIMULATOR_HTML}" "${DRIVER_HTML}" || true

exit "${EXIT_CODE}"