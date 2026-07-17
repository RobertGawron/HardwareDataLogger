from fastapi import APIRouter, WebSocket, WebSocketDisconnect

from backend.simulation.loggers import SdCardEvent

router = APIRouter()


class ConnectionManager:
    def __init__(self) -> None:
        self.active_connections: list[WebSocket] = []

    async def connect(self, websocket: WebSocket) -> None:
        await websocket.accept()
        self.active_connections.append(websocket)

    def disconnect(self, websocket: WebSocket) -> None:
        if websocket in self.active_connections:
            self.active_connections.remove(websocket)

    async def broadcast(self, message: SdCardEvent) -> None:
        for connection in self.active_connections:
            await connection.send_json(message)


sdcard_manager: ConnectionManager = ConnectionManager()


@router.websocket("/ws/sdcard")
async def websocket_sdcard(websocket: WebSocket) -> None:
    await sdcard_manager.connect(websocket)
    try:
        while True:
            await websocket.receive_text()
    except WebSocketDisconnect:
        sdcard_manager.disconnect(websocket)
