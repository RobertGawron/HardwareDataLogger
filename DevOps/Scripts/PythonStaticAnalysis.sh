# Activate the virtual environment
source /workspace/venv/bin/activate

# Set up directories for artifacts
OUTPUT_DIR="/workspace/build/BuildArtifacts/PythonStaticAnalysis"
mkdir -p "$OUTPUT_DIR"

# Define input and output file paths
SYSTEM_JSON="$OUTPUT_DIR/IntegrationTest.json"
SYSTEM_HTML="$OUTPUT_DIR/IntegrationTest.html"
SIMULATOR_JSON="$OUTPUT_DIR/FirmwarePCSimulator.json"
SIMULATOR_HTML="$OUTPUT_DIR/FirmwarePCSimulator.html"
DRIVER_JSON="$OUTPUT_DIR/DriverHostPython.json"
DRIVER_HTML="$OUTPUT_DIR/DriverHostPython.html"

# Initialize exit code tracker
EXIT_CODE=0

# Run Prospector analysis
prospector --profile /workspace/DevOps/Scripts/.prospector.yaml --strictness veryhigh --doc-warnings --output-format xunit /workspace/IntegrationTest/ > "$SYSTEM_JSON" || EXIT_CODE=1
prospector --profile /workspace/DevOps/Scripts/.prospector.yaml --strictness veryhigh --doc-warnings --output-format xunit /workspace/FirmwarePCSimulator/ > "$SIMULATOR_JSON" || EXIT_CODE=1
prospector --profile /workspace/DevOps/Scripts/.prospector.yaml --strictness veryhigh --doc-warnings --output-format xunit /workspace/Software/STM32F103RBTx/Application/Driver/Host/Python/ > "$DRIVER_JSON" || EXIT_CODE=1

# vjunit is broken in original version, so we need to fix it
find /workspace/venv/ -type f -name "vjunit.py" -exec sed -i 's/children = testcase\.getchildren()/children = list(testcase)/g' {} +

# Convert JSON reports to HTML using prospector-html
vjunit -f "$SYSTEM_JSON" -o "$SYSTEM_HTML" || echo "Warning: HTML conversion failed for IntegrationTest"
vjunit -f "$SIMULATOR_JSON" -o "$SIMULATOR_HTML" || echo "Warning: HTML conversion failed for FirmwarePCSimulator"
vjunit -f "$DRIVER_JSON" -o "$DRIVER_HTML" || echo "Warning: HTML conversion failed for DriverHostPython"

# Expand all tabs in the HTML reports
sed -i "/\$('.ui.accordion').accordion();/c\\
\$('.ui.accordion').accordion();\\
\$('.ui.accordion .title').addClass('active');\\
\$('.ui.accordion .content').addClass('active');" "$SYSTEM_HTML" "$SIMULATOR_HTML" "$DRIVER_HTML"

# Exit with the appropriate code
exit $EXIT_CODE