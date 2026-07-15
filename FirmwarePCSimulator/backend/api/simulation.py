from fastapi import APIRouter, Depends
from backend.simulation import Simulation, SimulationKey
from backend.models.requests import SpeedRequest, PulseRequest, KeyRequest

router = APIRouter(prefix="/api", tags=["simulation"])


# We inject simulation from main
def get_simulation():
    from backend.main import simulation
    return simulation


@router.post("/start")
def start_simulation(sim: Simulation = Depends(get_simulation)):
    sim.start_firmware()
    return {"status": "running"}


@router.post("/stop")
def stop_simulation(sim: Simulation = Depends(get_simulation)):
    sim.stop_firmware()
    return {"status": "stopped"}


@router.post("/reload")
def reload_simulation(sim: Simulation = Depends(get_simulation)):
    sim.reload_firmware()
    return {"status": "reloaded"}


@router.get("/status")
def get_status(sim: Simulation = Depends(get_simulation)):
    return {"running": sim.is_running()}


@router.post("/speed")
def set_speed(request: SpeedRequest, sim: Simulation = Depends(get_simulation)):
    sim.tick_interval = request.tick_interval
    return {"tick_interval": sim.tick_interval}


@router.post("/key/press")
def key_press(request: KeyRequest, sim: Simulation = Depends(get_simulation)):
    key = SimulationKey[request.key.upper()]
    sim.key_pressed(key)
    return {"pressed": request.key}


@router.post("/key/release")
def key_release(request: KeyRequest, sim: Simulation = Depends(get_simulation)):
    key = SimulationKey[request.key.upper()]
    sim.key_released(key)
    return {"released": request.key}


@router.post("/pulse")
def update_pulse(request: PulseRequest, sim: Simulation = Depends(get_simulation)):
    sim.update_pulse_counters(request.values)
    return {"pulse_values": request.values}


@router.get("/display/info")
def get_display_info(sim: Simulation = Depends(get_simulation)):
    return {
        "width": sim.get_display_width(),
        "height": sim.get_display_height()
    }