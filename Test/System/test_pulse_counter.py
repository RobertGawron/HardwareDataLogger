import time
import logging
import sys
from pathlib import Path

# Add the path to Simulation/FirmwarePCSimulator to sys.path
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

from simulation import Simulation, SimulationKey


logger = logging.getLogger(__name__)

def test_pulse_counter_start(assert_display_content):
    """Test to validate iteration through a list using display content."""
    logger.info("Starting test: test_iterate_list")

    dut: Simulation = Simulation()
    dut.start_firmware()
    logger.info("Firmware started for the simulation.")

    time.sleep(0.1)

