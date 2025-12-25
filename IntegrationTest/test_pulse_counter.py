"""
Module for testing the pulse counter in the Firmware Simulator.

This module contains unit tests for validating the functionality of the
pulse counter and its integration with the simulation environment.
"""

import time
import logging
import pytest

logger = logging.getLogger(__name__)


def test_pulse_counter_start(stm32_dut):
    """
    Test to validate the functionality of the pulse counter.

    This test verifies the integration of the pulse counter with the display
    content in the simulation environment.
    """
    logger.info("Starting test: test_pulse_counter_start")

    # Callbacks already registered by fixture!
    stm32_dut.init()
    stm32_dut.tick()
    
    stm32_dut.update_pulse_counters([5, 5, 5, 5])
    stm32_dut.tick()

    # Verify transmission
    # Define all expected transmissions
    expected_transmissions = [
        # First transmission
        [0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0xDF, 0x7E],
        # Second transmission
        [0x0B, 0x01, 0x02, 0x03, 0x04],
    ]
    
    # Assert all at once
    uart_capture.assert_all_transmissions(expected_transmissions)

    logger.info("Firmware started for the simulation.")

    time.sleep(0.1)  # Allow the firmware to run briefly for testing