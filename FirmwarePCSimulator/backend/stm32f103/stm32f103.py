import ctypes
from collections.abc import Callable
from pathlib import Path
from typing import Any

from backend.simulation.enums import SimulationKey

PULSE_COUNTER_COUNT = 4
UINT32_MASK = 0xFFFFFFFF

BytePtr = ctypes.POINTER(ctypes.c_uint8)


class InvalidPulseCounterCountError(ValueError):
    def __init__(self, expected: int, received: int) -> None:
        super().__init__(f"Expected {expected} pulse counters, got {received}")


class STM32F103:
    """Interface for the STM32 firmware simulation."""

    def __init__(self) -> None:
        project_root = Path(__file__).resolve().parents[2]
        dll_abs_path = project_root / "lib" / "libsimulator_stm32f103.so"

        self.dut: ctypes.CDLL = ctypes.CDLL(dll_abs_path)

        # Stored to prevent GC of callbacks
        self._serial_tx_callback_c: Any | None = None
        self._sdcard_open_callback: Any | None = None
        self._sdcard_write_callback: Any | None = None
        self._sdcard_close_callback: Any | None = None
        self._sdcard_init_callback: Any | None = None
        self._sdcard_start_callback: Any | None = None
        self._sdcard_stop_callback: Any | None = None
        self._sdcard_reset_callback: Any | None = None

    # ============================================================
    # Firmware Lifecycle
    # ============================================================

    def init(self) -> None:
        self.dut.LibWrapper_Init()

    def start(self) -> None:
        self.dut.LibWrapper_Start()

    def stop(self) -> None:
        self.dut.LibWrapper_Stop()

    def tick(self) -> None:
        self.dut.LibWrapper_Tick()

    def time_slot(self) -> None:
        self.dut.LibWrapper_TimeSlot()

    # ============================================================
    # Display
    # ============================================================

    def get_display_width(self) -> int:
        self.dut.LibWrapper_GetDisplayWidth.restype = ctypes.c_uint8
        return int(self.dut.LibWrapper_GetDisplayWidth())

    def get_display_height(self) -> int:
        self.dut.LibWrapper_GetDisplayHeight.restype = ctypes.c_uint8
        return int(self.dut.LibWrapper_GetDisplayHeight())

    def get_display_pixel(self, x: int, y: int) -> int:
        self.dut.LibWrapper_GetPixelValue.restype = ctypes.c_uint16
        self.dut.LibWrapper_GetPixelValue.argtypes = [
            ctypes.c_uint8,
            ctypes.c_uint8,
        ]
        return int(
            self.dut.LibWrapper_GetPixelValue(
                ctypes.c_uint8(x),
                ctypes.c_uint8(y),
            ),
        )

    # ============================================================
    # Keys
    # ============================================================

    def key_pressed(self, key: SimulationKey) -> None:
        self.dut.LibWrapper_KeyPressed.argtypes = [ctypes.c_uint8]
        self.dut.LibWrapper_KeyPressed.restype = None
        self.dut.LibWrapper_KeyPressed(key.value)

    def key_released(self, key: SimulationKey) -> None:
        self.dut.LibWrapper_KeyReleased.argtypes = [ctypes.c_uint8]
        self.dut.LibWrapper_KeyReleased.restype = None
        self.dut.LibWrapper_KeyReleased(key.value)

    # ============================================================
    # Pulse Counters
    # ============================================================

    def update_pulse_counter_frequency(
        self,
        pulse_counter_id: int,
        new_pulses_per_minute: int,
    ) -> bool:
        if not 0 <= pulse_counter_id < PULSE_COUNTER_COUNT:
            raise ValueError(
                f"pulse_counter_id must be in range 0-{PULSE_COUNTER_COUNT - 1}",
            )

        self.dut.LibWrapper_UpdatePulseCounterFrequency.argtypes = [
            ctypes.c_uint8,
            ctypes.c_uint32,
        ]
        self.dut.LibWrapper_UpdatePulseCounterFrequency.restype = ctypes.c_bool

        result = self.dut.LibWrapper_UpdatePulseCounterFrequency(
            ctypes.c_uint8(pulse_counter_id),
            ctypes.c_uint32(int(new_pulses_per_minute) & UINT32_MASK),
        )

        return bool(result)

    # ============================================================
    # Serial TX Callback
    # ============================================================

    def register_serial_tx_callback(
        self,
        callback: Callable[[int, list[int], int, int], int],
    ) -> None:
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_int,
            ctypes.c_uint8,
            ctypes.POINTER(ctypes.c_uint8),
            ctypes.c_uint16,
            ctypes.c_uint32,
        )

        self.dut.LibWrapper_RegisterSerialTxCallback.argtypes = [callback_type]
        self.dut.LibWrapper_RegisterSerialTxCallback.restype = None

        def wrapper(
            uart_id: int,
            p_data: ctypes.c_void_p,
            size: int,
            timeout: int,
        ) -> int:
            byte_ptr = ctypes.cast(
                p_data,
                ctypes.POINTER(ctypes.c_uint8),
            )
            data = [byte_ptr[i] for i in range(size)]
            return callback(uart_id, data, size, timeout)

        self._serial_tx_callback_c = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSerialTxCallback(
            self._serial_tx_callback_c,
        )

    # ============================================================
    # SD Card Callbacks
    # ============================================================

    def register_sdcard_initialize_callback(
        self,
        callback: Callable[[], bool],
    ) -> None:
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)

        self.dut.LibWrapper_RegisterSdCardInitializeCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardInitializeCallback.restype = None

        self._sdcard_init_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardInitializeCallback(
            self._sdcard_init_callback,
        )

    def register_sdcard_open_callback(
        self,
        callback: Callable[[str, int], int],
    ) -> None:
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,
            ctypes.c_char_p,
            ctypes.c_uint8,
        )

        self.dut.LibWrapper_RegisterSdCardOpenCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardOpenCallback.restype = None

        def wrapper(
            filename: bytes,
            mode: int,
        ) -> int:
            return callback(filename.decode("utf-8"), mode)

        self._sdcard_open_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardOpenCallback(
            self._sdcard_open_callback,
        )

    def register_sdcard_start_callback(
        self,
        callback: Callable[[], bool],
    ) -> None:
        """Register SD card start callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)

        self.dut.LibWrapper_RegisterSdCardStartCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardStartCallback.restype = None

        self._sdcard_start_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardStartCallback(
            self._sdcard_start_callback,
        )

    def register_sdcard_stop_callback(
        self,
        callback: Callable[[], bool],
    ) -> None:
        """Register SD card stop callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)

        self.dut.LibWrapper_RegisterSdCardStopCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardStopCallback.restype = None

        self._sdcard_stop_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardStopCallback(
            self._sdcard_stop_callback,
        )

    def register_sdcard_reset_callback(
        self,
        callback: Callable[[], bool],
    ) -> None:
        """Register SD card reset callback."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_bool)

        self.dut.LibWrapper_RegisterSdCardResetCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardResetCallback.restype = None

        self._sdcard_reset_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardResetCallback(
            self._sdcard_reset_callback,
        )

    def register_sdcard_close_callback(
        self,
        callback: Callable[[], int],
    ) -> None:
        """Register SD card close callback. Returns SdCardStatus as uint8."""
        callback_type = ctypes.CFUNCTYPE(ctypes.c_uint8)

        self.dut.LibWrapper_RegisterSdCardCloseCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardCloseCallback.restype = None

        self._sdcard_close_callback = callback_type(callback)
        self.dut.LibWrapper_RegisterSdCardCloseCallback(
            self._sdcard_close_callback,
        )

    def register_sdcard_write_callback(
        self,
        callback: Callable[[list[int], int], int],
    ) -> None:
        callback_type = ctypes.CFUNCTYPE(
            ctypes.c_uint8,
            ctypes.POINTER(ctypes.c_uint8),
            ctypes.c_uint16,
        )

        self.dut.LibWrapper_RegisterSdCardWriteCallback.argtypes = [
            callback_type,
        ]
        self.dut.LibWrapper_RegisterSdCardWriteCallback.restype = None

        def wrapper(
            p_data: ctypes.c_void_p,
            size: int,
        ) -> int:
            byte_ptr = ctypes.cast(
                p_data,
                ctypes.POINTER(ctypes.c_uint8),
            )
            data = [byte_ptr[i] for i in range(size)]
            return callback(data, size)

        self._sdcard_write_callback = callback_type(wrapper)
        self.dut.LibWrapper_RegisterSdCardWriteCallback(
            self._sdcard_write_callback,
        )
