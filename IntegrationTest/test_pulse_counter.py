"""
Module for testing the pulse counter in the Firmware Simulator.

This module contains unit tests for validating the functionality of the
pulse counter and its integration with the simulation environment.
"""

import time
import logging
import pytest

from stm32f103_simulator import STM32F103

logger = logging.getLogger(__name__)

class UartCapture:
    """Helper class to capture and verify UART transmissions."""
    
    def __init__(self):
        self.transmissions = []
    
    def callback(self, data: list, size: int, timeout: int) -> int:
        """Capture UART TX data."""
        hex_string = ' '.join(f'{byte:02X}' for byte in data)
        logger.info(f"UART TX: [{hex_string}], Size: {size}, Timeout: {timeout}")
        
        self.transmissions.append({
            'data': data.copy(),
            'size': size,
            'timeout': timeout
        })
        return 0
    
    def reset(self):
        """Clear all captured transmissions."""
        self.transmissions.clear()
        logger.debug("UART capture cleared")
    
    def count(self) -> int:
        """Get number of transmissions captured."""
        return len(self.transmissions)
    
    def get_transmission(self, index: int = 0):
        """Get a specific transmission by index."""
        if index >= len(self.transmissions):
            raise IndexError(f"No transmission at index {index}, only {len(self.transmissions)} captured")
        return self.transmissions[index]
    
    def assert_transmission_count(self, expected: int):
        """Assert the number of transmissions."""
        actual = len(self.transmissions)
        assert actual == expected, \
            f"Expected {expected} transmissions, got {actual}"
    
    def assert_data(self, expected_data: list, index: int = 0):
        """Assert that specific data was transmitted at given index."""
        transmission = self.get_transmission(index)
        actual = transmission['data']
        
        assert actual == expected_data, \
            f"Transmission {index} mismatch!\n" \
            f"Expected: [{' '.join(f'{b:02X}' for b in expected_data)}]\n" \
            f"Actual:   [{' '.join(f'{b:02X}' for b in actual)}]"
    
    def assert_all_transmissions(self, expected_list: list):
        """
        Assert all transmissions match expected data.
        
        :param expected_list: List of expected data lists
        """
        self.assert_transmission_count(len(expected_list))
        
        for i, expected_data in enumerate(expected_list):
            self.assert_data(expected_data, index=i)
        
        logger.info(f"✓ All {len(expected_list)} transmissions verified")
    
    def assert_contains_transmission(self, expected_data: list):
        """Assert that at least one transmission matches the expected data."""
        for i, transmission in enumerate(self.transmissions):
            if transmission['data'] == expected_data:
                logger.info(f"✓ Found matching transmission at index {i}")
                return
        
        # Format all transmissions for error message
        all_transmissions = '\n'.join(
            f"  [{i}]: [{' '.join(f'{b:02X}' for b in t['data'])}]"
            for i, t in enumerate(self.transmissions)
        )
        
        assert False, \
            f"Expected transmission not found!\n" \
            f"Looking for: [{' '.join(f'{b:02X}' for b in expected_data)}]\n" \
            f"Captured transmissions:\n{all_transmissions}"
    
    def get_all_data(self) -> list:
        """Get all transmitted data as a list of byte lists."""
        return [t['data'] for t in self.transmissions]
    
    def print_all(self):
        """Print all captured transmissions for debugging."""
        if not self.transmissions:
            logger.info("No transmissions captured")
            return
        
        logger.info(f"Captured {len(self.transmissions)} transmissions:")
        for i, t in enumerate(self.transmissions):
            hex_string = ' '.join(f'{byte:02X}' for byte in t['data'])
            logger.info(f"  [{i}] Data: [{hex_string}], Size: {t['size']}, Timeout: {t['timeout']}")


@pytest.fixture
def uart_capture():
    """Fixture providing UART capture capability."""
    return UartCapture()


def test_pulse_counter_start(uart_capture):
    """
    Test to validate the functionality of the pulse counter.

    This test verifies the integration of the pulse counter with the display
    content in the simulation environment.
    """
    logger.info("Starting test: test_pulse_counter_start")

    stm32_dut: STM32F103 = STM32F103()
    stm32_dut.register_serial_tx_callback(uart_capture.callback)
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
