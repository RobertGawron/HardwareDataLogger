import threading
import time
from typing import Tuple
from enum import Enum

from device_under_test import DeviceUnderTest



class SimulationKey(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3


class Simulation:
    def __init__(self):
        """
        Initializes the Simulation class with a default tick interval, 
        a threading event for stopping the tick process, and the device under test (DUT).
        """
        self.tick_interval: float = 0.02  # Default interval in seconds, can be configured
        self._tick_thread: threading.Thread | None = None
        self._stop_event: threading.Event = threading.Event()

        # Initialize the device under test (DUT)
        self.dut: DeviceUnderTest = DeviceUnderTest()

    def start_firmware(self) -> None:
        """
        Starts periodic calls to the `tick` method of the device under test (DUT).
        This runs in a separate thread.
        """
        if self._tick_thread is None or not self._tick_thread.is_alive():
            self.dut.init();
            
            self._stop_event.clear()
            self._tick_thread = threading.Thread(target=self._run_periodic_tick, daemon=True)
            self._tick_thread.start()

    def stop_firmware(self) -> None:
        """
        Stops the periodic calls to the `tick` method of the DUT.
        Waits for the background thread to terminate.
        """
        if self._tick_thread and self._tick_thread.is_alive():
            self._stop_event.set()
            self._tick_thread.join()

    def reload_firmware(self) -> None:
        """
        Stops and restarts the periodic calls to the `tick` method of the DUT.
        """
        self.stop_firmware()
        self.start_firmware()

    def update_pulse_counters(self, values) -> None:
        self.dut.update_pulse_counters(values)


    def get_display_width(self) -> int:
        """
        Retrieves the width of the display from the DUT.

        :return: The width of the display in pixels.
        """
        return self.dut.get_display_width()

    def get_display_height(self) -> int:
        """
        Retrieves the height of the display from the DUT.

        :return: The height of the display in pixels.
        """
        return self.dut.get_display_height()

    def get_display_pixel(self, x: int, y: int) -> Tuple[int, int, int]:
        """
        Retrieves the color of a specific pixel from the DUT and converts it 
        from RGB565 format to 8-bit RGB format.

        :param x: The x-coordinate of the pixel.
        :param y: The y-coordinate of the pixel.
        :return: A tuple containing the red, green, and blue components (8-bit each).
        """
        pixel_as_rgb565: int = self.dut.get_display_pixel(x, y)
        return self._convert_rgb565_to_rgb8(pixel_as_rgb565)

    def _run_periodic_tick(self) -> None:
        """
        Internal method that performs periodic calls to the `tick` method of the DUT.
        This runs in a loop until the stop event is set.
        """
        while not self._stop_event.is_set():
            self.dut.tick()
            time.sleep(self.tick_interval)

    def _convert_rgb565_to_rgb8(self, rgb565: int) -> Tuple[int, int, int]:
        """
        Converts a 16-bit RGB565 color value to an 8-bit RGB color value.

        :param rgb565: The 16-bit RGB565 color value.
        :return: A tuple containing the red, green, and blue components (8-bit each).
        """
        # Extract the red, green, and blue components from the RGB565 value
        red: int = (rgb565 >> 11) & 0x1F  # 5 bits
        green: int = (rgb565 >> 5) & 0x3F  # 6 bits
        blue: int = rgb565 & 0x1F  # 5 bits

        # Scale the components from 5 or 6 bits to 8 bits
        red_8: int = (red * 255) // 31
        green_8: int = (green * 255) // 63
        blue_8: int = (blue * 255) // 31

        return red_8, green_8, blue_8

    def key_pressed(self, key: SimulationKey):
        self.dut.key_pressed(key)
        print(f"Key pressed: {key.name}")

    def key_released(self, key: SimulationKey):
        self.dut.key_released(key)
        print(f"Key released: {key.name}")
