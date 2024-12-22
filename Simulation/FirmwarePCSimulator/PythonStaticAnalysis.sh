# Activate the virtual environment
source /workspace/venv/bin/activate

# Set up directories for artifacts
OUTPUT_DIR="/workspace/build/BuildArtifacts/PythonStaticAnalysis"
mkdir -p "$OUTPUT_DIR"

# Define input and output file paths
SYSTEM_JSON="$OUTPUT_DIR/SystemTests.json"
SYSTEM_HTML="$OUTPUT_DIR/SystemTests.html"
SIMULATOR_JSON="$OUTPUT_DIR/FirmwarePCSimulator.json"
SIMULATOR_HTML="$OUTPUT_DIR/FirmwarePCSimulator.html"

# Initialize exit code tracker
EXIT_CODE=0

# Run Prospector analysis
prospector --output-format json /workspace/Test/System/ > "$SYSTEM_JSON" || EXIT_CODE=1
prospector --output-format json /workspace/Simulation/FirmwarePCSimulator/ > "$SIMULATOR_JSON" || EXIT_CODE=1

# Convert JSON reports to HTML using prospector-html
prospector-html -i "$SYSTEM_JSON" -o "$SYSTEM_HTML" || echo "Warning: HTML conversion failed for SystemTests"
prospector-html -i "$SIMULATOR_JSON" -o "$SIMULATOR_HTML" || echo "Warning: HTML conversion failed for FirmwarePCSimulator"

# Exit with the appropriate code
exit $EXIT_CODE
