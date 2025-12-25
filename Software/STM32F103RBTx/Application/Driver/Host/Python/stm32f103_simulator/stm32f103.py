"""
Module for interacting with the simulated STM32 firmware.

This module provides a Python interface for managing the simulation,
including interactions with the display, keys, and pulse counters.
"""

import ctypes
import os.path
from enum import Enum
from typing import List, Callable


class SimulationKey(Enum):

    """Enumeration for simulation key events."""

    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3


class STM32F103:

    """
    Interface for the STM32 firmware simulation.

    Provides methods to initialize the simulation, interact with the display,
    and update pulse counters.
    """

    def __init__(self) -> None:
        """Initialize the STM32F103 class."""
        dll_name: str = "libSimulatorSTM32F103RBTx.so"
        dll_abs_path: str = (
            "/workspace/build/Software/STM32F103RBTx/Application/Driver/Host/libsimulator_stm32f103.so"
        )
        self.dut: ctypes.CDLL = ctypes.CDLL(dll_abs_path)
        self._serial_tx_callback_c = None

    def init(self) -> None:
        """
        Initialize the embedded library.

        This is required for the library to start functioning.
        """
        self.dut.LibWrapper_Init()

    def tick(self) -> None:
        """
        Trigger a single tick in the simulation.

        This simulates a single step in the device's processing cycle.
        """
        self.dut.LibWrapper_Tick()

    def get_display_width(self) -> int:
        """
        Retrieve the display width from the library.

        :return: The width of the display in pixels.
        """
        self.dut.LibWrapper_GetDisplayWidth.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayWidth()

    def get_display_height(self) -> int:
        """
        Retrieve the display height from the library.

        :return: The height of the display in pixels.
        """
        self.dut.LibWrapper_GetDisplayHeight.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayHeight()

    def get_display_pixel(self, x: int, y: int) -> int:
        """
        Retrieve the pixel value at the specified coordinates.

        :param x: The x-coordinate of the pixel.
        :param y: The y-coordinate of the pixel.
        :return: The pixel value in RGB565 format as a 16-bit integer.
        """
        self.dut.LibWrapper_GetPixelValue.restype = ctypes.c_uint16
        self.dut.LibWrapper_GetPixelValue.argtypes = [ctypes.c_uint8, ctypes.c_uint8]
        return self.dut.LibWrapper_GetPixelValue(ctypes.c_uint8(x), ctypes.c_uint8(y))

    def key_pressed(self, key: SimulationKey):
        """
        Notify the simulation of a key press event.

        :param key: The key that was pressed (SimulationKey).
        """
        self.dut.LibWrapper_KeyPressed.restype = None
        self.dut.LibWrapper_KeyPressed.argtypes = [ctypes.c_uint8]
        self.dut.LibWrapper_KeyPressed(key.value)

    def key_released(self, key: SimulationKey):
        """
        Notify the simulation of a key release event.

        :param key: The key that was released (SimulationKey).
        """
        self.dut.LibWrapper_KeyReleased.restype = None
        self.dut.LibWrapper_KeyReleased.argtypes = [ctypes.c_uint8]
        self.dut.LibWrapper_KeyReleased(key.value)

    def update_pulse_counters(self, pulse_counters: List[int]):
        """
        Update the pulse counters in the simulation.

        :param pulse_counters: A list of pulse counter values to update.
        """
        pulse_counter_count = 4
        if len(pulse_counters) != pulse_counter_count:
            raise ValueError(
                f"Expected {pulse_counter_count} pulse counters, got {len(pulse_counters)}"
            )

        pulse_counters_array_type = ctypes.c_uint16 * pulse_counter_count
        pulse_counters_array = pulse_counters_array_type(*pulse_counters)

        self.dut.LibWrapper_UpdatePulseCounters.restype = None
        self.dut.LibWrapper_UpdatePulseCounters.argtypes = [pulse_counters_array_type]
        self.dut.LibWrapper_UpdatePulseCounters(pulse_counters_array)

    def register_serial_tx_callback(self, callback: Callable[[int, List[int], int, int], int]):
        """
        Register a Serial TX callback with the shared library.

        The callback should be a Python function that accepts four arguments:
        - `uart_id` (int): The UART ID (UartId enum value).
        - `data` (List[int]): The data to transmit.
        - `size` (int): The size of the data.
        - `timeout` (int): Timeout in milliseconds.
        The function should return an integer (`HAL_StatusTypeDef`).
        """
        # Define the C-compatible callback type
        # C: typedef int (*serial_tx_callback_type)(uint8_t uart_id, const uint8_t*, uint16_t, uint32_t);
        serial_tx_callback_type = ctypes.CFUNCTYPE(
            ctypes.c_int,                    # return type
            ctypes.c_uint8,                  # uint8_t uart_id
            ctypes.POINTER(ctypes.c_uint8),  # const uint8_t* pdata
            ctypes.c_uint16,                 # uint16_t size
            ctypes.c_uint32                  # uint32_t timeout
        )

        self.dut.LibWrapper_RegisterSerialTxCallback.argtypes = [serial_tx_callback_type]
        self.dut.LibWrapper_RegisterSerialTxCallback.restype = None

        # Wrap the Python callback
        def wrapper(uart_id, p_data, size, timeout):
            data = [p_data[i] for i in range(size)]  # Convert to Python list
            return callback(uart_id, data, size, timeout)

        self._serial_tx_callback_c = serial_tx_callback_type(wrapper)
        self.dut.LibWrapper_RegisterSerialTxCallback(self._serial_tx_callback_c)

    def register_sdcard_open_callback(self, callback: Callable[[str, int], int]):
        """Register SD card open callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,      # Return SdCardStatus as uint8
            ctypes.c_char_p,     # filename
            ctypes.c_uint8       # mode
        )
        
        self.dut.LibWrapper_RegisterSdCardOpenCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardOpenCallback.restype = None
        
        def wrapper(filename, mode):
            return callback(filename.decode('utf-8'), mode)
        
        self._sdcard_open_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardOpenCallback(self._sdcard_open_callback)

    def register_sdcard_write_callback(self, callback: Callable[[List[int], int], int]):
        """Register SD card write callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,                  # Return SdCardStatus as uint8
            ctypes.POINTER(ctypes.c_uint8),  # data
            ctypes.c_uint16                  # size
        )
        
        self.dut.LibWrapper_RegisterSdCardWriteCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardWriteCallback.restype = None
        
        def wrapper(p_data, size):
            data = [p_data[i] for i in range(size)]
            return callback(data, size)
        
        self._sdcard_write_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardWriteCallback(self._sdcard_write_callback)

    def register_sdcard_close_callback(self, callback: Callable[[], int]):
        """Register SD card close callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_uint8)  # Return SdCardStatus as uint8
        
        self.dut.LibWrapper_RegisterSdCardCloseCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardCloseCallback.restype = None
        
        self._sdcard_close_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardCloseCallback(self._sdcard_close_callback)

    def register_sdcard_initialize_callback(self, callback: Callable[[], bool]):
        """Register SD card initialize callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)
        
        self.dut.LibWrapper_RegisterSdCardInitializeCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardInitializeCallback.restype = None
        
        self._sdcard_init_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardInitializeCallback(self._sdcard_init_callback)

    def register_sdcard_start_callback(self, callback: Callable[[], bool]):
        """Register SD card start callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)
        
        self.dut.LibWrapper_RegisterSdCardStartCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardStartCallback.restype = None
        
        self._sdcard_start_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardStartCallback(self._sdcard_start_callback)

    def register_sdcard_stop_callback(self, callback: Callable[[], bool]):
        """Register SD card stop callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)
        
        self.dut.LibWrapper_RegisterSdCardStopCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardStopCallback.restype = None
        
        self._sdcard_stop_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardStopCallback(self._sdcard_stop_callback)

    def register_sdcard_reset_callback(self, callback: Callable[[], bool]):
        """Register SD card reset callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)
        
        self.dut.LibWrapper_RegisterSdCardResetCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardResetCallback.restype = None
        
        self._sdcard_reset_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardResetCallback(self._sdcard_reset_callback)

    def register_sdcard_open_callback(self, callback: Callable[[str, int], int]):
        """Register SD card open callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,      # Return SdCardStatus as uint8
            ctypes.c_char_p,     # filename
            ctypes.c_uint8       # mode
        )
        
        self.dut.LibWrapper_RegisterSdCardOpenCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardOpenCallback.restype = None
        
        def wrapper(filename, mode):
            return callback(filename.decode('utf-8'), mode)
        
        self._sdcard_open_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardOpenCallback(self._sdcard_open_callback)

    def register_sdcard_write_callback(self, callback: Callable[[List[int], int], int]):
        """Register SD card write callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,                  # Return SdCardStatus as uint8
            ctypes.POINTER(ctypes.c_uint8),  # data
            ctypes.c_uint16                  # size
        )
        
        self.dut.LibWrapper_RegisterSdCardWriteCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardWriteCallback.restype = None
        
        def wrapper(p_data, size):
            data = [p_data[i] for i in range(size)]
            return callback(data, size)
        
        self._sdcard_write_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardWriteCallback(self._sdcard_write_callback)

    def register_sdcard_close_callback(self, callback: Callable[[], int]):
        """Register SD card close callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_uint8)  # Return SdCardStatus as uint8
        
        self.dut.LibWrapper_RegisterSdCardCloseCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSdCardCloseCallback.restype = None
        
        self._sdcard_close_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardCloseCallback(self._sdcard_close_callback)