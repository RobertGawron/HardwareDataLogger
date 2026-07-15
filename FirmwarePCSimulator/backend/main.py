from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
import asyncio

from backend.simulation import Simulation
from backend.websocket.sdcard import router as sdcard_router, sdcard_manager
from backend.api.simulation import router as simulation_router

app = FastAPI()

# Core simulation
simulation = Simulation(sdcard_manager)


@app.on_event("startup")
async def startup_event():
    loop = asyncio.get_running_loop()
    simulation.set_event_loop(loop)


# Register routers
app.include_router(simulation_router)
app.include_router(sdcard_router)

# Static frontend
app.mount("/", StaticFiles(directory="frontend", html=True), name="frontend")