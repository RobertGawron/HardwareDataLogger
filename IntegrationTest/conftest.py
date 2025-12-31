"""
Module for managing pytest fixtures and hooks for validating simulation display content.

This module includes setup for assertions on the display output of the simulation,
along with integration for pytest HTML reports to include visual validation.
"""

import logging
from typing import Generator, List
import pytest
import pytest_html

from stm32f103_simulator import STM32F103  # pylint: disable=import-error


logger = logging.getLogger(__name__)


def cobs_encode(data: List[int]) -> List[int]:
    """
    Encode data using Consistent Overhead Byte Stuffing (COBS).

    :param data: Raw data to encode
    :return: COBS-encoded data with trailing 0x00 delimiter
    """
    if not data:
        return [0x01, 0x00]  # Empty frame

    encoded = []
    code_index = 0
    code = 0x01

    encoded.append(0x00)  # Placeholder for first code byte

    for byte in data:
        if byte == 0x00:
            # Write code byte and start new block
            encoded[code_index] = code
            code_index = len(encoded)
            encoded.append(0x00)  # Placeholder for next code byte
            code = 0x01
        else:
            # Copy non-zero byte
            encoded.append(byte)
            code += 1

            # If we've written 254 bytes, start new block
            if code == 0xFF:
                encoded[code_index] = code
                code_index = len(encoded)
                encoded.append(0x00)  # Placeholder for next code byte
                code = 0x01

    # Write final code byte
    encoded[code_index] = code

    # Add trailing delimiter
    encoded.append(0x00)

    return encoded


def cobs_decode(cobs_data: List[int]) -> List[int]:
    """
    Decode COBS-encoded data.

    :param cobs_data: COBS-encoded data with trailing 0x00 delimiter
    :return: Decoded raw data
    """
    if not cobs_data or cobs_data[-1] != 0x00:
        raise ValueError("Invalid COBS frame: missing trailing 0x00 delimiter")

    # Remove trailing delimiter
    data = cobs_data[:-1]
    decoded = []
    pos = 0

    while pos < len(data):
        code = data[pos]

        if code == 0x00:
            break  # Invalid

        # Insert zero if this isn't the first code byte
        if pos > 0:
            decoded.append(0x00)

        # Copy (code - 1) bytes
        for i in range(1, code):
            if pos + i < len(data):
                decoded.append(data[pos + i])

        pos += code

    return decoded


class UartCapture:

    """Helper class to capture and verify UART transmissions."""

    def __init__(self):
        """Initialize UART capture with empty transmission list."""
        self.transmissions = []
        self.verbose = True  # Add this flag (Default to True)

    def callback(self, uart_id: int, data: list, size: int, timeout: int) -> int:
        """Capture UART TX data."""
        # Only log if verbose is True
        if self.verbose:
            hex_string = ' '.join(f'{byte:02X}' for byte in data)
            logger.info(
                "UART %d: [%s], Size: %d, Timeout: %d",
                uart_id, hex_string, size, timeout
            )

        self.transmissions.append({
            'uart_id': uart_id,
            'data': data.copy(),
            'size': size,
            'timeout': timeout
        })
        return 0

    def register_all(self, dut):
        """Register UART callback with the STM32 simulator."""
        dut.register_serial_tx_callback(self.callback)

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
            raise IndexError(
                f"No transmission at index {index}, "
                f"only {len(self.transmissions)} captured"
            )
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

    def assert_uart_id(self, expected_uart_id: int, index: int = 0):
        """Assert that transmission came from expected UART."""
        transmission = self.get_transmission(index)
        actual = transmission['uart_id']

        assert actual == expected_uart_id, \
            f"Transmission {index} UART ID mismatch! " \
            f"Expected: {expected_uart_id}, Actual: {actual}"

    def assert_all_transmissions(self, expected_list: list):
        """
        Assert all transmissions match expected data.

        :param expected_list: List of expected data lists
        """
        self.assert_transmission_count(len(expected_list))

        for i, expected_data in enumerate(expected_list):
            self.assert_data(expected_data, index=i)

        logger.info(
            "All %d transmissions verified",
            len(expected_list)
        )

    def assert_contains_transmission(self, expected_data: list):
        """Assert that at least one transmission matches the expected data."""
        for i, transmission in enumerate(self.transmissions):
            if transmission['data'] == expected_data:
                logger.info(
                    "Found matching transmission at index %d", i
                )
                return

        # Format all transmissions for error message
        all_transmissions = '\n'.join(
            f"  [{i}] UART {t['uart_id']}: "
            f"[{' '.join(f'{b:02X}' for b in t['data'])}]"
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

        logger.info("Captured %d transmissions:", len(self.transmissions))
        for i, transmission in enumerate(self.transmissions):
            hex_string = ' '.join(
                f'{byte:02X}' for byte in transmission['data']
            )
            logger.info(
                "  [%d] UART %d: [%s], Size: %d, Timeout: %d",
                i, transmission['uart_id'], hex_string,
                transmission['size'], transmission['timeout']
            )


class SdCardCapture:

    """Helper class to capture and verify SD card operations."""

    def __init__(self):
        """Initialize SD card capture with empty operations list."""
        self.operations = []
        self.current_file = None
        self.file_opened = False

    def initialize_callback(self) -> bool:
        """Capture SD card initialize."""
        logger.info("SD Card: Initialize called")
        self.operations.append({'operation': 'initialize'})
        return True

    def start_callback(self) -> bool:
        """Capture SD card start."""
        logger.info("SD Card: Start called")
        self.operations.append({'operation': 'start'})
        return True

    def stop_callback(self) -> bool:
        """Capture SD card stop."""
        logger.info("SD Card: Stop called")
        self.operations.append({'operation': 'stop'})
        return True

    def reset_callback(self) -> bool:
        """Capture SD card reset."""
        logger.info("SD Card: Reset called")
        self.operations.append({'operation': 'reset'})
        return True

    def open_callback(self, filename: str, mode: int) -> int:
        """Capture SD card open file."""
        logger.info(
            "SD Card: Open file '%s', mode=%d", filename, mode
        )
        self.operations.append({
            'operation': 'open',
            'filename': filename,
            'mode': mode
        })
        self.current_file = filename
        self.file_opened = True
        return 0  # SdCardStatus::OK

    def write_callback(self, data: List[int], size: int) -> int:
        """Capture SD card write."""
        data_str = ''.join(
            chr(b) if 32 <= b < 127 else f'\\x{b:02x}' for b in data
        )
        logger.info(
            "SD Card: Write %d bytes: '%s'", size, data_str
        )
        self.operations.append({
            'operation': 'write',
            'data': data.copy(),
            'size': size
        })
        return 0  # SdCardStatus::OK

    def close_callback(self) -> int:
        """Capture SD card close file."""
        logger.info("SD Card: Close file")
        self.operations.append({'operation': 'close'})
        self.file_opened = False
        return 0  # SdCardStatus::OK

    def register_all(self, dut):
        """Register all SD card callbacks with the STM32 simulator."""
        dut.register_sdcard_initialize_callback(self.initialize_callback)
        dut.register_sdcard_start_callback(self.start_callback)
        dut.register_sdcard_stop_callback(self.stop_callback)
        dut.register_sdcard_reset_callback(self.reset_callback)
        dut.register_sdcard_open_callback(self.open_callback)
        dut.register_sdcard_write_callback(self.write_callback)
        dut.register_sdcard_close_callback(self.close_callback)

    def reset(self):
        """Clear all captured operations."""
        self.operations.clear()
        self.current_file = None
        self.file_opened = False
        logger.debug("SD card capture cleared")

    def count(self) -> int:
        """Get number of operations captured."""
        return len(self.operations)

    def get_operation(self, index: int = 0):
        """Get a specific operation by index."""
        if index >= len(self.operations):
            raise IndexError(
                f"No operation at index {index}, "
                f"only {len(self.operations)} captured"
            )
        return self.operations[index]

    def assert_operation_count(self, expected: int):
        """Assert the number of operations."""
        actual = len(self.operations)
        assert actual == expected, \
            f"Expected {expected} operations, got {actual}"

    def assert_operation_type(self, expected_type: str, index: int = 0):
        """Assert the operation type at given index."""
        operation = self.get_operation(index)
        actual = operation['operation']

        assert actual == expected_type, \
            f"Operation {index} type mismatch! " \
            f"Expected: {expected_type}, Actual: {actual}"

    def assert_write_data(self, expected_data: str, index: int = 0):
        """Assert that specific data was written (as string)."""
        operation = self.get_operation(index)
        assert operation['operation'] == 'write', \
            f"Operation {index} is not a write operation"

        actual_str = ''.join(chr(b) for b in operation['data'])

        assert actual_str == expected_data, \
            f"Write data mismatch at operation {index}!\n" \
            f"Expected: '{expected_data}'\n" \
            f"Actual:   '{actual_str}'"

    def get_all_writes(self) -> List[str]:
        """Get all write operations as strings."""
        writes = []
        for op in self.operations:
            if op['operation'] == 'write':
                data_str = ''.join(chr(b) for b in op['data'])
                writes.append(data_str)
        return writes

    def print_all(self):
        """Print all captured operations for debugging."""
        if not self.operations:
            logger.info("No SD card operations captured")
            return

        logger.info(
            "Captured %d SD card operations:", len(self.operations)
        )
        for i, op in enumerate(self.operations):
            if op['operation'] == 'write':
                data_str = ''.join(
                    chr(b) if 32 <= b < 127 else f'\\x{b:02x}'
                    for b in op['data']
                )
                logger.info(
                    "  [%d] WRITE: '%s' (%d bytes)",
                    i, data_str, op['size']
                )
            elif op['operation'] == 'open':
                logger.info(
                    "  [%d] OPEN: '%s', mode=%d",
                    i, op['filename'], op['mode']
                )
            else:
                logger.info(
                    "  [%d] %s", i, op['operation'].upper()
                )


@pytest.fixture(scope="function")
def stm32_dut():
    """
    Fixture providing STM32 simulator with attached capture helpers.
    Access helpers via: stm32_dut.uart and stm32_dut.sd
    """
    dut = STM32F103()

    # Instantiate helpers
    dut.uart = UartCapture()
    dut.sd = SdCardCapture()

    # Register callbacks immediately
    dut.uart.register_all(dut)
    dut.sd.register_all(dut)

    yield dut
    
    # Teardown: Reset pulse counters to zeros after each test
    try:
        dut.update_pulse_counters([0, 0, 0, 0])
    except Exception:
        pass  # Ignore if reset fails


@pytest.hookimpl(hookwrapper=True)
def pytest_runtest_makereport(
    item: pytest.Item, call: pytest.CallInfo
) -> Generator[None, None, None]:
    """
    Customize the test report generation.

    The `call` argument is part of the pytest hook API and is required even if
    it is not used in this implementation.

    :param item: The pytest test item being executed.
    :param call: Information about the test execution call (unused here).
    :return: Generator for pytest hook implementation.
    """
    # pylint: disable=unused-argument
    outcome = yield
    report = outcome.get_result()

    if report.when == "call":
        extras = getattr(report, "extras", [])
        images = getattr(item, "assert_display_contents", [])
        for image_base64, assert_name in images:
            # Append each image to the extras list
            extras.append(
                pytest_html.extras.image(
                    image_base64, mime_type="image/png", name=assert_name
                )
            )

        report.extras = extras
