import time
import logging
import sys
from pathlib import Path

# Add the path to Simulation/FirmwarePCSimulator to sys.path
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

# pylint: disable=import-error, wrong-import-position
from simulation import Simulation, SimulationKey


logger = logging.getLogger(__name__)

def push_key(dut, key):
    dut.key_pressed(key)
    time.sleep(0.1)
    dut.key_released(key)


def test_iterate_list(assert_display_content):
    """Test to validate iteration through a list using display content."""
    logger.info("Starting test: test_iterate_list")

    dut: Simulation = Simulation()
    dut.start_firmware()
    logger.info("Firmware started for the simulation.")

    logger.info("Capturing initial display state.")
    assert_display_content(dut, "List Iteration Test 1", "test_iterate_list_1.png")

    logger.info("Simulating DOWN key press and release.")
    push_key(dut, SimulationKey.DOWN)
    time.sleep(0.1)

    logger.info("Capturing updated display state.")
    assert_display_content(dut, "List Iteration Test 2", "test_iterate_list_2.png")

    logger.info("Simulating DOWN key press and release.")
    push_key(dut, SimulationKey.DOWN)
    time.sleep(0.1)

    logger.info("Capturing updated display state.")
    assert_display_content(dut, "List Iteration Test 3", "test_iterate_list_3.png")

    logger.info("Simulating DOWN key press and release.")
    push_key(dut, SimulationKey.DOWN)
    time.sleep(0.1)

    logger.info("Capturing updated display state.")
    assert_display_content(dut, "List Iteration Test 4", "test_iterate_list_4.png")

    dut.stop_firmware()
    logger.info("Firmware stopped for the simulation.")
