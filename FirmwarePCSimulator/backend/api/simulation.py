from typing import Annotated, cast

from fastapi import APIRouter, Depends, Request

from backend.models.requests import KeyRequest, PulseRequest, SpeedRequest
from backend.simulation import Simulation, SimulationKey

router = APIRouter(prefix="/api", tags=["simulation"])


def get_simulation(request: Request) -> Simulation:
    return cast("Simulation", request.app.state.simulation)


@router.post("/start")
def start_simulation(
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, str]:
    sim.start_firmware()
    return {"status": "running"}


@router.post("/stop")
def stop_simulation(
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, str]:
    sim.stop_firmware()
    return {"status": "stopped"}


@router.post("/reload")
def reload_simulation(
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, str]:
    sim.reload_firmware()
    return {"status": "reloaded"}


@router.get("/status")
def get_status(sim: Annotated[Simulation, Depends(get_simulation)]) -> dict[str, bool]:
    return {"running": sim.is_running()}


@router.post("/speed")
def set_speed(
    request: SpeedRequest,
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, float]:
    sim.tick_interval = request.tick_interval
    return {"tick_interval": sim.tick_interval}


@router.post("/key/press")
def key_press(
    request: KeyRequest,
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, str]:
    key = SimulationKey[request.key.upper()]
    sim.key_pressed(key)
    return {"pressed": request.key}


@router.post("/key/release")
def key_release(
    request: KeyRequest,
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, str]:
    key = SimulationKey[request.key.upper()]
    sim.key_released(key)
    return {"released": request.key}


@router.post("/pulse")
def update_pulse(
    request: PulseRequest,
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, list[int]]:
    sim.update_pulse_counters(request.values)
    return {"pulse_values": request.values}


@router.get("/display/info")
def get_display_info(
    sim: Annotated[Simulation, Depends(get_simulation)],
) -> dict[str, int]:
    return {
        "width": sim.get_display_width(),
        "height": sim.get_display_height(),
    }
