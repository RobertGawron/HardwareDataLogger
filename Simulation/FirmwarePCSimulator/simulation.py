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
from typing import Tuple
from enum import Enum

from STM32F103RBTx.device_under_test import DeviceUnderTest as STM32F103RBTx
from ESP8266.device_under_test import DeviceUnderTest as Esp8266


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


class Simulation:

    """Simulation class manages the interaction between STM32 and ESP8266 simulations."""

    def __init__(self):
        """
        Initialize the Simulation class with tick interval, threading event
        for stopping, and the device under test (DUT).
        """
        self.tick_interval: float = 0.02
        self._tick_thread: threading.Thread | None = None
        self._stop_event: threading.Event = threading.Event()

        self.stm32: STM32F103RBTx = STM32F103RBTx()
        self.esp8266: Esp8266 = Esp8266()

        self.esp8266_uart0_tx_callback = None
        self.my_gpio_state_callback = None

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
            self.esp8266.register_uart0_tx_callback(self.esp8266_uart0_tx_callback)
            self.esp8266.register_gpio_state_callback(self.my_gpio_state_callback)

            self.stm32.register_serial_tx_callback(self.stm32_uart_tx_callback)

            self.stm32.init()
            self.esp8266.init()

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
            self.esp8266.tick()
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

    def stm32_uart_tx_callback(self, data: list, size: int, timeout: int) -> int:
        """
        Print the data transmitted from STM32F103RBTx UART and send it to ESP8266.

        :param data: List of integers representing the transmitted bytes.
        :param size: Number of bytes transmitted.
        :param timeout: Timeout in milliseconds.
        :return: Always returns 0 (HAL_OK) for success.
        """
        data_string = ''.join(map(chr, data))  # Convert byte list to string
        print(f"UART TX Callback: Transmitting data: '{data_string}', Size: {size}, Timeout: {timeout}")

        self.esp8266.uart0_tx(data, size, timeout)
        return 0  # HAL_OK equivalent
