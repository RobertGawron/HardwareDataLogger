"""
Module for testing display interactions in the Firmware Simulator.

This module contains tests for validating display content changes
based on simulation interactions, such as key presses and callbacks.
"""

import time
import logging
import sys
from pathlib import Path

# Add the path to Simulation/FirmwarePCSimulator to sys.path
# This allows importing modules from the simulation directory.
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

# pylint: disable=import-error, wrong-import-position
# flake8: noqa: E402
from simulation import Simulation, SimulationKey

# Configure logger for the test module
logger = logging.getLogger(__name__)


def push_key(dut, key):
    """
    Simulate a key press and release on the Device Under Test (DUT).

    :param dut: The simulation instance being tested.
    :param key: The simulation key to press and release.
    """
    dut.key_pressed(key)
    time.sleep(0.1)
    dut.key_released(key)


def uart_tx_callback(message: str):
    """
    Handle UART0 TX events.

    Log the transmitted message.

    :param message: The transmitted message string.
    """
    logger.info("UART0 TX Callback: %s", message)


def gpio_state_callback(gpio_id: int, state: bool):
    """
    Handle GPIO state changes.

    Log GPIO state changes.

    :param gpio_id: ID of the GPIO pin.
    :param state: Boolean representing the state of the GPIO pin.
    """
    logger.info("GPIO Callback: GPIO %d, State %s", gpio_id, state)


def test_iterate_list(assert_display_content):
    """
    Test to validate iteration through a list using display content.

    Simulates interactions with the simulation and verifies the display
    content updates as expected.

    :param assert_display_content: A function to validate the display content.
    """
    logger.info("Starting test: test_iterate_list")

    # Initialize the simulation instance
    dut: Simulation = Simulation()

    # Set up callbacks for UART and GPIO
    dut.set_esp8266_uart0_tx_callback(uart_tx_callback)
    dut.set_esp8266_gpio_callback(gpio_state_callback)

    # Start the firmware simulation
    dut.start_firmware()
    logger.info("Firmware started for the simulation.")

    # Capture and validate initial display state
    logger.info("Capturing initial display state.")
    assert_display_content(dut, "List Iteration Test 1", "test_iterate_list_1.png")

    # Simulate DOWN key presses and capture updated display states
    for iteration in range(2, 5):
        logger.info("Simulating DOWN key press and release.")
        push_key(dut, SimulationKey.DOWN)
        time.sleep(0.1)

        logger.info("Capturing updated display state.")
        assert_display_content(
            dut, f"List Iteration Test {iteration}", f"test_iterate_list_{iteration}.png"
        )

    # Stop the firmware simulation
    dut.stop_firmware()
    logger.info("Firmware stopped for the simulation.")
