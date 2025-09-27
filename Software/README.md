# Software

## Subprojects

* [Details about **STM32F103RBTx** project.](./STM32F103RBTx/README.md)
* [Details about **ESP8266MOD** project.](./ESP8266MOD/README.md)

## Architecture

![measurement flow diagram](../Documentation/Diagrams/RemoteHostMeasurementDataFlow.svg)



TODO:
https://github.com/RobertGawron/HardwareDataLogger/tree/main/Software/ESP8266

# Install the specific version with ESP8266 support
espup install --toolchain-version 1.80.0.0

# On Linux/macOS, source the environment variables
source ~/export-esp.sh



not this: cargo install cargo-espflash@2.1.0
this one: cargo install espflash --version 3.3.0


# 2. Download the toolchain (Linux 64-bit version)
wget https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz

# 3. Extract it to a common directory
mkdir -p /opt/esp
tar -xzf xtensa-lx106-elf-gcc8_4_0-esp-2020r3-linux-amd64.tar.gz -C /opt/esp

# 4. Add the toolchain to your PATH for the current session
export PATH="/opt/esp/xtensa-lx106-elf/bin:$PATH"

# 5. Verify it works
xtensa-lx106-elf-gcc --version


yanked versions
optional

cargo install cargo-generate
USER=root cargo generate --git https://github.com/thecodechemist99/esp8266-rust
rm -rf PROJECT_NAME/.git



--------------

try again:

USER=root cargo generate esp-rs/esp-idf-template cargo


it hates venv 

PATH=/usr/bin:/usr/local/bin:$PATH cargo build