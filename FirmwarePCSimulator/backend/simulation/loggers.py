import logging
from collections.abc import Callable
from datetime import UTC, datetime
from typing import TypedDict

logger = logging.getLogger(__name__)

ASCII_PRINTABLE_MIN = ord(" ")
ASCII_PRINTABLE_MAX = ord("~") + 1
NON_PRINTABLE_PLACEHOLDER = "·"


class UartTransmission(TypedDict):
    uart_id: int
    data: list[int]
    size: int
    timeout: int


class SdCardEvent(TypedDict, total=False):
    operation: str
    filename: str
    mode: int
    size: int
    hex: list[str]
    ascii: list[str]
    timestamp_utc: str


class UartLogger:
    """Helper class to log UART transmissions."""

    def __init__(self) -> None:
        self.transmissions: list[UartTransmission] = []

    def callback(
        self,
        uart_id: int,
        data: list[int],
        size: int,
        timeout: int,
    ) -> int:
        hex_string = " ".join(f"{byte:02X}" for byte in data)

        logger.info(
            "UART %d TX: [%s], Size: %d, Timeout: %d",
            uart_id,
            hex_string,
            size,
            timeout,
        )

        self.transmissions.append(
            {
                "uart_id": uart_id,
                "data": data.copy(),
                "size": size,
                "timeout": timeout,
            },
        )

        return 0


class SdCardLogger:
    """Helper class to log SD card operations."""

    def __init__(self) -> None:
        self.operations: list[SdCardEvent] = []
        self._listeners: list[Callable[[SdCardEvent], None]] = []

    def add_listener(self, listener: Callable[[SdCardEvent], None]) -> None:
        self._listeners.append(listener)

    def _emit(self, event: SdCardEvent) -> None:
        event["timestamp_utc"] = datetime.now(UTC).isoformat()
        self.operations.append(event)

        for listener in self._listeners:
            listener(event)

    def initialize_callback(self) -> bool:
        self._emit({"operation": "initialize"})
        return True

    def start_callback(self) -> bool:
        self._emit({"operation": "start"})
        return True

    def stop_callback(self) -> bool:
        self._emit({"operation": "stop"})
        return True

    def reset_callback(self) -> bool:
        self._emit({"operation": "reset"})
        return True

    def open_callback(self, filename: str, mode: int) -> int:
        self._emit(
            {
                "operation": "open",
                "filename": filename,
                "mode": mode,
            },
        )
        return 0

    def write_callback(self, data: list[int], size: int) -> int:

        payload = data[:size]

        hex_values = [f"{b:02X}" for b in payload]
        ascii_values = [
            (
                chr(b)
                if ASCII_PRINTABLE_MIN <= b < ASCII_PRINTABLE_MAX
                else NON_PRINTABLE_PLACEHOLDER
            )
            for b in payload
        ]

        self._emit(
            {
                "operation": "write",
                "size": size,
                "hex": hex_values,
                "ascii": ascii_values,
            },
        )

        return 0

    def close_callback(self) -> int:
        self._emit({"operation": "close"})
        return 0
