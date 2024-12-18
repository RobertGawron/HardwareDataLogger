import ctypes
import os.path
from enum import Enum
from typing import List

class SimulationKey(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

class DeviceUnderTest:
    def __init__(self) -> None:
        """
        Initializes the DeviceUnderTest class by loading the shared library for the simulation.
        The library path is dynamically constructed based on the script's location.
        """
        dll_name: str = "libFirmwarePCSimulator.so"
        dll_abs_path: str = (
            os.path.dirname(os.path.abspath(__file__))
            + "/../.."
            + os.path.sep + "build" + os.path.sep + "Simulation/FirmwarePCSimulator/"
            + os.path.sep + dll_name
        )
        self.dut: ctypes.CDLL = ctypes.CDLL(dll_abs_path)

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

    def get_display_width(self) -> int:
        """
        Retrieves the display width from the library.

        :return: The width of the display in pixels.
        """
        self.dut.LibWrapper_GetDisplayWidth.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayWidth()

    def get_display_height(self) -> int:
        """
        Retrieves the display height from the library.

        :return: The height of the display in pixels.
        """
        self.dut.LibWrapper_GetDisplayHeight.restype = ctypes.c_uint8
        return self.dut.LibWrapper_GetDisplayHeight()

    def get_display_pixel(self, x: int, y: int) -> int:
        """
        Retrieves the pixel value at the specified coordinates from the display.
        The pixel value is returned in RGB565 format.

        :param x: The x-coordinate of the pixel.
        :param y: The y-coordinate of the pixel.
        :return: The pixel value in RGB565 format as a 16-bit integer.
        """
        self.dut.LibWrapper_GetPixelValue.restype = ctypes.c_uint16
        self.dut.LibWrapper_GetPixelValue.argtypes = [ctypes.c_uint8, ctypes.c_uint8]
        return self.dut.LibWrapper_GetPixelValue(ctypes.c_uint8(x), ctypes.c_uint8(y))

    def key_pressed(self, key: SimulationKey):
        self.dut.LibWrapper_KeyPressed.restype = None  # Returns void
        self.dut.LibWrapper_KeyPressed.argtypes = [ctypes.c_uint8]  # Accepts an integer (enum value)
        self.dut.LibWrapper_KeyPressed(key.value)

    def key_released(self, key: SimulationKey):
        self.dut.LibWrapper_KeyReleased.restype = None  # Returns void
        self.dut.LibWrapper_KeyReleased.argtypes = [ctypes.c_uint8]  # Accepts an integer (enum value)
        self.dut.LibWrapper_KeyReleased(key.value)

    def update_pulse_counters(self, pulse_counters: List[int]):
        """
        Updates the pulse counters in the shared library.

        :param pulse_counters: A list of pulse counter values to update.
        """
        PULSE_COUNTER_COUNT = 4
        if len(pulse_counters) != PULSE_COUNTER_COUNT:
            raise ValueError(f"Expected {PULSE_COUNTER_COUNT} pulse counters, got {len(pulse_counters)}")

        PulseCountersArrayType = ctypes.c_uint16 * PULSE_COUNTER_COUNT
        pulse_counters_array = PulseCountersArrayType(*pulse_counters)

        self.dut.LibWrapper_UpdatePulseCounters.restype = None
        self.dut.LibWrapper_UpdatePulseCounters.argtypes = [PulseCountersArrayType]
        self.dut.LibWrapper_UpdatePulseCounters(pulse_counters_array)
