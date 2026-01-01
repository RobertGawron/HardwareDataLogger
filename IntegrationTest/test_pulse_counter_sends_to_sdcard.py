"""
Module for testing the SD card functionality in the Firmware Simulator.

This module contains unit tests for validating the SD card driver
and its integration with the simulation environment.
"""

import logging
from conftest import SdCardOperation

logger = logging.getLogger(__name__)


def test_sdcard_write_csv(stm32_dut):
    """Test SD card CSV writing functionality."""
    # Disable UART logging via the attached object
    stm32_dut.uart.verbose = False

    logger.info("Starting test: test_sdcard_write_csv")

    stm32_dut.init()

    # Verify initialization sequence
    assert stm32_dut.sd.count() == 3, "Expected 3 operations after init()"
    stm32_dut.sd.assert_operation_type(SdCardOperation.INITIALIZE, 0)
    stm32_dut.sd.assert_operation_type(SdCardOperation.START, 1)
    stm32_dut.sd.assert_operation_type(SdCardOperation.OPEN, 2)

    # Verify the file opened correctly
    open_op = stm32_dut.sd.get_operation(2)
    assert open_op['filename'] == 'measurements.txt', \
        f"Expected filename 'measurements.txt', got '{open_op['filename']}'"
    assert open_op['mode'] == 1, \
        f"Expected APPEND mode (1), got {open_op['mode']}"

    stm32_dut.sd.reset()

    # First tick - should write initial zeros for all 4 pulse counters + 1 extra
    stm32_dut.tick()

    # Verify first batch of writes (initial state with counters at 0)
    assert stm32_dut.sd.count() == 5, "Expected 5 write operations after first tick"

    for i in range(5):
        stm32_dut.sd.assert_operation_type(SdCardOperation.WRITE, i)

    # Check the initial zero values written
    writes = stm32_dut.sd.get_all_writes()
    assert writes[0] == '0,0\n', f"Expected '0,0\\n', got '{writes[0]}'"
    assert writes[1] == '1,0\n', f"Expected '1,0\\n', got '{writes[1]}'"
    assert writes[2] == '2,0\n', f"Expected '2,0\\n', got '{writes[2]}'"
    assert writes[3] == '3,0\n', f"Expected '3,0\\n', got '{writes[3]}'"
    assert writes[4] == '4,5\n', f"Expected '4,5\\n', got '{writes[4]}'"

    logger.info("Initial writes verified: 4 counters at 0, plus source 4 at 5")

    stm32_dut.sd.reset()

    # Update pulse counters to trigger new measurements
    stm32_dut.update_pulse_counters([10, 20, 30, 40])
    stm32_dut.tick()

    # Verify second batch of writes (updated counter values)
    assert stm32_dut.sd.count() == 5, "Expected 5 write operations after second tick"

    writes = stm32_dut.sd.get_all_writes()
    logger.info("Captured %d write operations", len(writes))

    # Verify the updated measurements
    assert writes[0] == '0,10\n', f"Expected '0,10\\n', got '{writes[0]}'"
    assert writes[1] == '1,20\n', f"Expected '1,20\\n', got '{writes[1]}'"
    assert writes[2] == '2,30\n', f"Expected '2,30\\n', got '{writes[2]}'"
    assert writes[3] == '3,40\n', f"Expected '3,40\\n', got '{writes[3]}'"
    assert writes[4] == '4,5\n', f"Expected '4,5\\n', got '{writes[4]}'"

    logger.info("Updated writes verified: counters at [10, 20, 30, 40], plus source 4 at 5")

    # Verify CSV format compliance
    for i, write_data in enumerate(writes):
        # Check format: "sourceId,value\n"
        assert ',' in write_data, f"Write {i} missing comma delimiter: '{write_data}'"
        assert write_data.endswith('\n'), f"Write {i} missing newline: '{write_data}'"

        parts = write_data.strip().split(',')
        assert len(parts) == 2, \
            f"Write {i} should have 2 CSV fields, got {len(parts)}: '{write_data}'"

        # Verify both parts are numeric
        try:
            source_id = int(parts[0])
            value = int(parts[1])
            logger.info("Write %d: source_id=%d, value=%d", i, source_id, value)
        except ValueError as e:
            assert False, f"Write {i} contains non-numeric data: '{write_data}' - {e}"

    logger.info("All CSV format checks passed")
    logger.info("SD card test completed successfully")
