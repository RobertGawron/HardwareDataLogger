import asyncio

from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles

from backend.api.simulation import router as simulation_router
from backend.simulation import Simulation
from backend.websocket.sdcard import router as sdcard_router
from backend.websocket.sdcard import sdcard_manager

app = FastAPI()

# Core simulation
simulation = Simulation(sdcard_manager)


@app.on_event("startup")
async def startup_event() -> None:
    loop = asyncio.get_running_loop()
    simulation.set_event_loop(loop)
    app.state.simulation = simulation


# Register routers
app.include_router(simulation_router)
app.include_router(sdcard_router)

# Static frontend
app.mount("/", StaticFiles(directory="frontend", html=True), name="frontend")
