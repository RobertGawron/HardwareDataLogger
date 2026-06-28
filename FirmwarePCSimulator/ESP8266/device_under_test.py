"""
Module for managing the DeviceUnderTest class.

This module handles interactions with the shared library for simulating the
ESP8266 firmware, providing methods for initialization, tick simulation,
and registering callbacks.
"""

from typing import List


class DeviceUnderTest:

    """
    Manage the DeviceUnderTest simulation.

    This class loads the shared library and provides methods to interact
    with the simulation, including initializing the library, triggering
    ticks, and registering callbacks.
    """

    def __init__(self) -> None:
        """
        Initialize the shared library for the simulation.

        Constructs the library path dynamically based on the script's
        location and loads the shared library.
        """

    def init(self) -> None:
        """
        Initialize the embedded library.

        This method is required for the library to start functioning.
        """

    def tick(self) -> None:
        """
        Triggered by the `LibWrapper_Tick` function in the shared library.

        This simulates a single tick or step in the device's processing cycle.
        """

    def register_uart0_tx_callback(self, callback):
        """
        Register a UART0 TX callback with the shared library.

        The callback should be a Python function that accepts a single
        string (`str`) argument.
        """

    def register_gpio_state_callback(self, callback):
        """
        Register a GPIO state change callback with the shared library.

        The callback should be a Python function that accepts two
        arguments: `gpio_id` (int) and `state` (bool).
        """

    def uart0_tx(self, data: List[int], size: int, timeout: int) -> int:
        """
        Transmit data via UART0.

        Calls the `LibWrapper_OnSerialRx` method in the shared library.

        :param data: List of integers (uint8_t) to transmit.
        :param size: Number of bytes to transmit.
        :param timeout: Timeout value in milliseconds.
        :return: HAL_StatusTypeDef (0 = HAL_OK, 1 = HAL_ERROR, etc.)
        """
        # pylint: disable=unused-argument
        return 0
