"""
Simulation module for managing interactions between STM32 and ESP8266 devices.

This module defines the `Simulation` class, which provides methods for managing
and interacting with device-under-test (DUT) simulations for STM32 and ESP8266.
It includes utilities for periodic ticks, UART communication, GPIO interactions,
and display management. The module also defines enumerations for simulation keys
and GPIO identifiers.
"""

import threading
import time
import logging
from typing import Tuple, List
from enum import Enum

from stm32f103_simulator import STM32F103


logger = logging.getLogger(__name__)


class SimulationKey(Enum):

    """Enumeration for simulation key events."""

    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3


class GPIOID(Enum):

    """Enumeration for GPIO identifiers."""

    GPIO1 = 13
    GPIO2 = 2
    GPIO3 = 3


class UartLogger:  # pylint: disable=too-few-public-methods

    """Helper class to log UART transmissions."""

    def __init__(self):
        """Initialize UART logger."""
        self.transmissions = []

    def callback(self, uart_id: int, data: list, size: int, timeout: int) -> int:
        """
        Capture and log UART TX data.

        :param uart_id: UART port identifier.
        :param data: List of integers representing the transmitted bytes.
        :param size: Number of bytes transmitted.
        :param timeout: Timeout in milliseconds.
        :return: Always returns 0 (HAL_OK) for success.
        """
        hex_string = ' '.join(f'{byte:02X}' for byte in data)
        logger.info(
            "UART %d TX: [%s], Size: %d, Timeout: %d",
            uart_id, hex_string, size, timeout
        )

        self.transmissions.append({
            'uart_id': uart_id,
            'data': data.copy(),
            'size': size,
            'timeout': timeout
        })
        return 0


class SdCardLogger:

    """Helper class to log SD card operations."""

    def __init__(self):
        """Initialize SD card logger."""
        self.operations = []

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
        logger.info("SD Card: Open file '%s', mode=%d", filename, mode)
        self.operations.append({
            'operation': 'open',
            'filename': filename,
            'mode': mode
        })
        return 0  # SdCardStatus::OK

    def write_callback(self, data: List[int], size: int) -> int:
        """Capture SD card write."""
        data_str = ''.join(
            chr(b) if 32 <= b < 127 else f'\\x{b:02x}' for b in data
        )
        logger.info("SD Card: Write %d bytes: '%s'", size, data_str)
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
        return 0  # SdCardStatus::OK


class Simulation:  # pylint: disable=too-many-instance-attributes

    """Simulation class manages the interaction between STM32 and ESP8266 simulations."""

    def __init__(self):
        """
        Initialize the Simulation class with tick interval, threading event
        for stopping, and the device under test (DUT).
        """
        self.tick_interval: float = 0.02
        self._tick_thread: threading.Thread | None = None
        self._stop_event: threading.Event = threading.Event()

        self.stm32: STM32F103 = STM32F103()
        # self.esp8266: Esp8266 = Esp8266()

        # Initialize loggers
        self.uart_logger = UartLogger()
        self.sd_logger = SdCardLogger()

        # Register callbacks
        self._register_callbacks()

        self.stm32.init()

        # Initialize callback attributes
        self.esp8266_uart0_tx_callback = None
        self.my_gpio_state_callback = None

    def _register_callbacks(self):
        """Register all callbacks with the STM32 simulator."""
        # Register UART callback
        self.stm32.register_serial_tx_callback(self.uart_logger.callback)

        # Register SD card callbacks
        self.stm32.register_sdcard_initialize_callback(
            self.sd_logger.initialize_callback
        )
        self.stm32.register_sdcard_start_callback(
            self.sd_logger.start_callback
        )
        self.stm32.register_sdcard_stop_callback(
            self.sd_logger.stop_callback
        )
        self.stm32.register_sdcard_reset_callback(
            self.sd_logger.reset_callback
        )
        self.stm32.register_sdcard_open_callback(
            self.sd_logger.open_callback
        )
        self.stm32.register_sdcard_write_callback(
            self.sd_logger.write_callback
        )
        self.stm32.register_sdcard_close_callback(
            self.sd_logger.close_callback
        )

    def set_esp8266_uart0_tx_callback(self, callback):
        """
        Set the callback for ESP8266 UART0 transmission.

        :param callback: Function to handle UART0 transmission.
        """
        self.esp8266_uart0_tx_callback = callback

    def set_esp8266_gpio_callback(self, callback):
        """
        Set the callback for ESP8266 GPIO state changes.

        :param callback: Function to handle GPIO state changes.
        """
        self.my_gpio_state_callback = callback

    def start_firmware(self) -> None:
        """
        Start periodic calls to the `tick` method of the DUT in a separate
        thread.
        """
        if self._tick_thread is None or not self._tick_thread.is_alive():
            # self.esp8266.register_uart0_tx_callback(self.esp8266_uart0_tx_callback)
            # self.esp8266.register_gpio_state_callback(self.my_gpio_state_callback)

            self.stm32.init()
            # self.esp8266.init()

            self._stop_event.clear()
            self._tick_thread = threading.Thread(
                target=self._run_periodic_tick, daemon=True
            )
            self._tick_thread.start()

    def stop_firmware(self) -> None:
        """Stop the periodic calls to the `tick` method of the DUT."""
        if self._tick_thread and self._tick_thread.is_alive():
            self._stop_event.set()
            self._tick_thread.join()

    def reload_firmware(self) -> None:
        """Stop and restart the periodic calls to the `tick` method."""
        self.stop_firmware()
        self.start_firmware()

    def update_pulse_counters(self, values) -> None:
        """Update the pulse counters in the STM32 simulation."""
        self.stm32.update_pulse_counters(values)

    def get_display_width(self) -> int:
        """Get the display width from the STM32 DUT."""
        return self.stm32.get_display_width()

    def get_display_height(self) -> int:
        """Get the display height from the STM32 DUT."""
        return self.stm32.get_display_height()

    def get_display_pixel(self, x: int, y: int) -> Tuple[int, int, int]:
        """
        Get the color of a pixel in RGB format from the STM32 DUT.

        :param x: X-coordinate of the pixel.
        :param y: Y-coordinate of the pixel.
        :return: RGB color tuple.
        """
        pixel_rgb565: int = self.stm32.get_display_pixel(x, y)
        return self._convert_rgb565_to_rgb8(pixel_rgb565)

    def _run_periodic_tick(self) -> None:
        """
        Run periodic `tick` calls to the DUT.

        This internal method handles periodic updates to simulate device behavior.
        """
        while not self._stop_event.is_set():
            self.stm32.tick()
            # self.esp8266.tick()
            time.sleep(self.tick_interval)

    def _convert_rgb565_to_rgb8(self, rgb565: int) -> Tuple[int, int, int]:
        """Convert a 16-bit RGB565 color to an 8-bit RGB color."""
        red = (rgb565 >> 11) & 0x1F
        green = (rgb565 >> 5) & 0x3F
        blue = rgb565 & 0x1F

        return (
            (red * 255) // 31,
            (green * 255) // 63,
            (blue * 255) // 31,
        )

    def key_pressed(self, key: SimulationKey):
        """Notify the STM32 simulation of a key press event."""
        self.stm32.key_pressed(key)

    def key_released(self, key: SimulationKey):
        """Notify the STM32 simulation of a key release event."""
        self.stm32.key_released(key)
