"""
Module for managing the DeviceUnderTest class.

This module handles interactions with the shared library for simulating the
ESP8266 firmware, providing methods for initialization, tick simulation,
and registering callbacks.
"""

import ctypes
import os.path
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
        pass
        """dll_name: str = "libSimulatorESP8266.so"
        dll_abs_path: str = (
            os.path.dirname(os.path.abspath(__file__))
            + "/../../.."
            + os.path.sep + "build" + os.path.sep
            + "Simulation/FirmwarePCSimulator/ESP8266" + os.path.sep
            + dll_name
        )
        if not os.path.exists(dll_abs_path):
            raise FileNotFoundError(
                f"Shared library not found: {dll_abs_path}"
            )

        print("Loading shared library ESP8266: ", dll_abs_path)

        self.dut: ctypes.CDLL = ctypes.CDLL(dll_abs_path)
        self._my_callback_c = None
        self._gpio_state_callback_c = None
        """
    def init(self) -> None:
        """
        Initialize the embedded library.

        This method is required for the library to start functioning.
        """
        pass#self.dut.LibWrapper_Init()

    def tick(self) -> None:
        """
        Triggered by the `LibWrapper_Tick` function in the shared library.

        This simulates a single tick or step in the device's processing cycle.
        """
        pass#self.dut.LibWrapper_Tick()

    def register_uart0_tx_callback(self, callback):
        """
        Register a UART0 TX callback with the shared library.

        The callback should be a Python function that accepts a single
        string (`str`) argument.
        """
        pass#
        #on_serial_tx_callback_type = ctypes.CFUNCTYPE(None, ctypes.c_char_p)
        #self._my_callback_c = on_serial_tx_callback_type(callback)
        #self.dut.LibWrapper_RegisterOnSerialTx(self._my_callback_c)

    def register_gpio_state_callback(self, callback):
        """
        Register a GPIO state change callback with the shared library.

        The callback should be a Python function that accepts two
        arguments: `gpio_id` (int) and `state` (bool).
        """
        pass
        """on_gpio_change_callback_type = ctypes.CFUNCTYPE(
            None, ctypes.c_int, ctypes.c_bool
        )
        self._gpio_state_callback_c = on_gpio_change_callback_type(callback)
        self.dut.LibWrapper_RegisterOnGpioChange(self._gpio_state_callback_c)
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
        pass
        """self.dut.LibWrapper_OnSerialRx.argtypes = [
            ctypes.POINTER(ctypes.c_uint8),  # const uint8_t* pData
            ctypes.c_uint16,                # uint16_t Size
            ctypes.c_uint32                 # uint32_t Timeout
        ]
        self.dut.LibWrapper_OnSerialRx.restype = ctypes.c_int  # HAL_Status

        # Convert Python list to ctypes array
        data_array = (ctypes.c_uint8 * size)(*data)

        # Call the LibWrapper_OnSerialRx function
        result = self.dut.LibWrapper_OnSerialRx(
            data_array, ctypes.c_uint16(size), ctypes.c_uint32(timeout)
        )
        return result
        """  
