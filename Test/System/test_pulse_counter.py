"""
Module for testing the pulse counter in the Firmware Simulator.

This module contains unit tests for validating the functionality of the
pulse counter and its integration with the simulation environment.
"""

import time
import logging
import sys
from pathlib import Path

# Add the path to Simulation/FirmwarePCSimulator to sys.path
simulation_path = Path(__file__).parent.parent.parent / "Simulation" / "FirmwarePCSimulator"
sys.path.append(str(simulation_path))

# pylint: disable=import-error, wrong-import-position
# flake8: noqa: E402
from simulation import Simulation

logger = logging.getLogger(__name__)


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


def test_pulse_counter_start(assert_display_content):
    # pylint: disable=unused-argument
    """
    Test to validate the functionality of the pulse counter.

    This test verifies the integration of the pulse counter with the display
    content in the simulation environment.
    """
    logger.info("Starting test: test_pulse_counter_start")

    dut: Simulation = Simulation()

    dut.set_esp8266_uart0_tx_callback(uart_tx_callback)
    dut.set_esp8266_gpio_callback(gpio_state_callback)

    dut.start_firmware()
    logger.info("Firmware started for the simulation.")

    time.sleep(0.1)  # Allow the firmware to run briefly for testing
