import ctypes
import os.path
from enum import Enum
from typing import List



class DeviceUnderTest:
    def __init__(self) -> None:
        """
        Initializes the DeviceUnderTest class by loading the shared library for the simulation.
        The library path is dynamically constructed based on the script's location.
        """
        dll_name: str = "libSimulatorESP8266.so"
        dll_abs_path: str = (
            os.path.dirname(os.path.abspath(__file__))
            + "/../../.."
            + os.path.sep + "build" + os.path.sep + "Simulation/FirmwarePCSimulator/ESP8266"
            + os.path.sep + dll_name
        )
        if not os.path.exists(dll_abs_path):
            raise FileNotFoundError(f"Shared library not found: {dll_abs_path}")

        print ("Loading shared library ESP8266: ", dll_abs_path)

        self.dut: ctypes.CDLL = ctypes.CDLL(dll_abs_path)
        self._my_callback_c = None
        self._gpio_state_callback_c = None

    def init(self) -> None:
        """
        Initializes the embedded library. This is required for the library to start functioning.
        """
        self.dut.LibWrapper_Init()

    def tick(self) -> None:
        """
        Triggers the `LibWrapper_Tick` function in the shared library. This simulates a single
        tick or step in the device's processing cycle.
        """
        self.dut.LibWrapper_Tick()

 
    def register_uart0_tx_callback(self, callback):
        """
        Registers a callback function with the shared library. The callback
        should be a Python function that accepts a single `str` argument.
        """

        OnSerialTxCallbackType = ctypes.CFUNCTYPE(None, ctypes.c_char_p)
        self._my_callback_c = OnSerialTxCallbackType(callback)
        self.dut.LibWrapper_RegisterOnSerialTx(self._my_callback_c)

    def register_gpio_state_callback(self, callback):
        """
        Registers a callback function with the shared library. The callback
        should be a Python function that accepts two arguments: gpio_id (int) and state (bool).
        """
        OnGpioChangeCallbackType = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_bool)
        self._gpio_state_callback_c = OnGpioChangeCallbackType(callback)
        self.dut.LibWrapper_RegisterOnGpioChange(self._gpio_state_callback_c)


    def uart0_tx(self, data: List[int], size: int, timeout: int) -> int:
        """
        Call LibWrapper_OnSerialRx with the provided parameters.
        :param data: List of integers (uint8_t) to transmit.
        :param size: Number of bytes to transmit.
        :param timeout: Timeout value in milliseconds.
        :return: HAL_StatusTypeDef (0 = HAL_OK, 1 = HAL_ERROR, etc.)
        """
        # Define the HAL_UART_Transmit function signature
        self.dut.LibWrapper_OnSerialRx.argtypes = [
            ctypes.POINTER(ctypes.c_uint8),  # const uint8_t* pData
            ctypes.c_uint16,                # uint16_t Size
            ctypes.c_uint32                 # uint32_t Timeout
        ]
        self.dut.LibWrapper_OnSerialRx.restype = ctypes.c_int  # HAL_StatusTypeDef is an enum

        # Convert Python list to ctypes array
        data_array = (ctypes.c_uint8 * size)(*data)

        # Call the LibWrapper_OnSerialRx function
        result = self.dut.LibWrapper_OnSerialRx(data_array, ctypes.c_uint16(size), ctypes.c_uint32(timeout))
        return result