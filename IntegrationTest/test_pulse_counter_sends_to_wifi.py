"""
Integration test for pulse counter WiFi transmission.

This module validates that pulse counter measurements are correctly serialized,
COBS-encoded, and transmitted via UART to the WiFi module.
"""

import logging
from conftest import cobs_encode

logger = logging.getLogger(__name__)


def test_pulse_counter_sends_initial_values_to_wifi(stm32_dut):
    """
    Verify pulse counters send their initial values via WiFi on startup.

    Tests that when the system initializes, all pulse counters transmit
    their initial state (zeros) through the WiFi communication channel.
    """
    logger.info("Testing initial pulse counter transmission to WiFi")

    stm32_dut.init()
    stm32_dut.tick()

    # Expected initial state: all counters at zero
    initial_transmissions = [
        cobs_encode([0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x8B, 0x6B, 0x9F]),  # Counter 0: 0
        cobs_encode([0x0B, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x34, 0xA2, 0x0B, 0xA2]),  # Counter 1: 0
        cobs_encode([0x0B, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xE4, 0xD8, 0xAB, 0xE5]),  # Counter 2: 0
        cobs_encode([0x0B, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x54, 0xF1, 0xCB, 0xD8]),  # Counter 3: 0
        cobs_encode([0x09, 0x00, 0x04, 0x05, 0x00, 0xF5, 0xC9, 0x4C, 0xB1]),              # Counter 4: 5
    ]

    stm32_dut.uart.assert_all_transmissions(initial_transmissions)
    logger.info("Initial values transmitted correctly")


def test_pulse_counter_sends_updated_values_to_wifi(stm32_dut):
    """
    Verify pulse counters send updated values via WiFi after changes.

    Tests that when pulse counter values are updated, the new values are
    correctly transmitted through the WiFi communication channel using the
    proper protocol format (Little Endian with COBS encoding).
    """
    logger.info("Testing updated pulse counter transmission to WiFi")

    # Setup: Initialize system and clear initial transmissions
    stm32_dut.init()
    stm32_dut.tick()
    stm32_dut.uart.reset()

    # Action: Update pulse counters with test values
    test_values = [0x12552277, 5, 55555, 75]
    logger.info("Setting pulse counters to: %s", test_values)
    stm32_dut.uart.reset()
    stm32_dut.update_pulse_counters(test_values)
    stm32_dut.tick()

    # Verification: Check transmitted values match expected protocol format
    # Protocol: [Length(2,LE)][Source(1)][Value(N,LE)][CRC(4,LE)]
    # All values transmitted as Little Endian, COBS-encoded with 0x00 delimiter
    expected_transmissions = [
        # Counter 0: 307,569,271 (0x12552277) as uint32_t
        cobs_encode([0x0B, 0x00, 0x00, 0x77, 0x22, 0x55, 0x12, 0x76, 0x59, 0x3F, 0x66]),
        # Counter 1: 5 as uint32_t
        cobs_encode([0x0B, 0x00, 0x01, 0x05, 0x00, 0x00, 0x00, 0x06, 0x52, 0xD5, 0x95]),
        # Counter 2: 55,555 (0xD903) as uint32_t
        cobs_encode([0x0B, 0x00, 0x02, 0x03, 0xD9, 0x00, 0x00, 0xB5, 0x79, 0x46, 0x75]),
        # Counter 3: 75 (0x4B) as uint32_t
        cobs_encode([0x0B, 0x00, 0x03, 0x4B, 0x00, 0x00, 0x00, 0x68, 0x2E, 0xDE, 0x94]),
        # Counter 4: 5 as uint16_t
        cobs_encode([0x09, 0x00, 0x04, 0x05, 0x00, 0xF5, 0xC9, 0x4C, 0xB1]),
    ]

    stm32_dut.uart.assert_all_transmissions(expected_transmissions)
    logger.info("Updated values transmitted correctly")
