import asyncio
import threading
import time
from typing import Protocol

from backend.stm32f103.stm32f103 import STM32F103

from .enums import SimulationKey
from .loggers import SdCardEvent, SdCardLogger, UartLogger


class BroadcastManager(Protocol):
    async def broadcast(self, message: SdCardEvent) -> None: ...


class Simulation:
    """Simulation class manages the interaction between STM32 devices."""

    def __init__(self, sdcard_manager: BroadcastManager) -> None:
        # Async / WebSocket
        self.loop: asyncio.AbstractEventLoop | None = None
        self.sdcard_manager: BroadcastManager = sdcard_manager

        # Threading
        self.tick_interval: float = 0.005  # 5 ms, TODO make some config with this
        self._tick_thread: threading.Thread | None = None
        self._stop_event: threading.Event = threading.Event()

        # STM32
        self.stm32: STM32F103 = STM32F103()

        # Loggers
        self.uart_logger: UartLogger = UartLogger()
        self.sd_logger: SdCardLogger = SdCardLogger()
        self.sd_logger.add_listener(self._handle_sd_event)

        # Register callbacks
        self._register_callbacks()

        # Init firmware
        self.stm32.init()

    def set_event_loop(self, loop: asyncio.AbstractEventLoop) -> None:
        self.loop = loop

    def is_running(self) -> bool:
        return self._tick_thread is not None and self._tick_thread.is_alive()

    def _handle_sd_event(self, event: SdCardEvent) -> None:
        if self.loop is None:
            return

        self.loop.call_soon_threadsafe(
            asyncio.create_task,
            self.sdcard_manager.broadcast(event),
        )

    def _register_callbacks(self) -> None:
        self.stm32.register_serial_tx_callback(self.uart_logger.callback)

        self.stm32.register_sdcard_initialize_callback(
            self.sd_logger.initialize_callback,
        )
        self.stm32.register_sdcard_start_callback(self.sd_logger.start_callback)
        self.stm32.register_sdcard_stop_callback(self.sd_logger.stop_callback)
        self.stm32.register_sdcard_reset_callback(self.sd_logger.reset_callback)
        self.stm32.register_sdcard_open_callback(self.sd_logger.open_callback)
        self.stm32.register_sdcard_write_callback(self.sd_logger.write_callback)
        self.stm32.register_sdcard_close_callback(self.sd_logger.close_callback)

    def start_firmware(self) -> None:
        if self._tick_thread is None or not self._tick_thread.is_alive():
            self.stm32.start()
            self._stop_event.clear()
            self._tick_thread = threading.Thread(
                target=self._run_periodic_tick,
                daemon=True,
            )
            self._tick_thread.start()

    def stop_firmware(self) -> None:
        if self._tick_thread and self._tick_thread.is_alive():
            self._stop_event.set()
            self._tick_thread.join()

        self.stm32.stop()

    def reload_firmware(self) -> None:
        self.stop_firmware()
        self.start_firmware()

    def get_display_width(self) -> int:
        return self.stm32.get_display_width()

    def get_display_height(self) -> int:
        return self.stm32.get_display_height()

    def get_display_pixel(self, x: int, y: int) -> tuple[int, int, int]:
        pixel_rgb565: int = self.stm32.get_display_pixel(x, y)
        return self._convert_rgb565_to_rgb8(pixel_rgb565)

    def _run_periodic_tick(self) -> None:
        while not self._stop_event.is_set():
            self.stm32.time_slot()
            self.stm32.tick()
            time.sleep(self.tick_interval)

    def _convert_rgb565_to_rgb8(self, rgb565: int) -> tuple[int, int, int]:
        red = (rgb565 >> 11) & 0x1F
        green = (rgb565 >> 5) & 0x3F
        blue = rgb565 & 0x1F

        return (
            (red * 255) // 31,
            (green * 255) // 63,
            (blue * 255) // 31,
        )

    def key_pressed(self, key: SimulationKey) -> None:
        self.stm32.key_pressed(key)

    def key_released(self, key: SimulationKey) -> None:
        self.stm32.key_released(key)

    def update_pulse_counter_frequency(
        self,
        counter_id: int,
        pulses_per_minute: int,
    ) -> bool:
        if not self.is_running():
            return False

        return self.stm32.update_pulse_counter_frequency(
            counter_id,
            pulses_per_minute,
        )