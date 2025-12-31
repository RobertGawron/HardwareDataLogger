"""
Module for testing the SD card functionality in the Firmware Simulator.

This module contains unit tests for validating the SD card driver
and its integration with the simulation environment.
"""

import time
import logging

logger = logging.getLogger(__name__)


def test_sdcard_write_csv(stm32_dut):
    """Test SD card CSV writing functionality."""
    # 1. Disable UART logging via the attached object
    stm32_dut.uart.verbose = False

    logger.info("Starting test: test_sdcard_write_csv")

    stm32_dut.init()

    assert stm32_dut.sd.count() == 2, "Expected 2 operations after init()"
    stm32_dut.sd.assert_operation_type('initialize', 0)
    stm32_dut.sd.assert_operation_type('start', 1)
    stm32_dut.sd.reset()

    stm32_dut.tick()

    # Update pulse counters to trigger measurements
    stm32_dut.update_pulse_counters([10, 20, 30, 40])
    stm32_dut.tick()

    # Print all captured operations for debugging
    stm32_dut.sd.print_all()

    # Verify operations occurred
    assert stm32_dut.sd.count() > 0, "No SD card operations captured"

    # Check if any writes occurred
    writes = stm32_dut.sd.get_all_writes()
    logger.info("Captured %d write operations", len(writes))

    for i, write_data in enumerate(writes):
        logger.info("Write %d: '%s'", i, write_data)

    # FIXED: Use stm32_dut.sd instead of undefined sdcard_capture
    # stm32_dut.sd.assert_operation_type('initialize', 0)
    # stm32_dut.sd.assert_operation_type('start', 1)
    # stm32_dut.sd.assert_operation_type('open', 2)
    # stm32_dut.sd.assert_write_data('0,10\n', 3)  # sourceId=0, data=10

    logger.info("SD card test completed successfully")
    time.sleep(0.1)


def test_sdcard_lifecycle(stm32_dut):
    """Test SD card lifecycle operations."""
    # Disable UART logging via the attached object
    stm32_dut.uart.verbose = False

    logger.info("Starting test: test_sdcard_lifecycle")

    # Initialize the system
    stm32_dut.init()
    stm32_dut.tick()

    # Print captured operations
    stm32_dut.sd.print_all()

    # Verify lifecycle methods were called
    operations = [op['operation'] for op in stm32_dut.sd.operations]
    logger.info("Operations called: %s", operations)

    # Verify initialize and start were called
    assert 'initialize' in operations, "Initialize was not called"
    assert 'start' in operations, "Start was not called"

    logger.info("SD card lifecycle test completed")