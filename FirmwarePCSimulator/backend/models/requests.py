from pydantic import BaseModel, Field


class SpeedRequest(BaseModel):
    tick_interval: float


class PulseRequest(BaseModel):
    counter_id: int = Field(ge=0, le=3)
    pulses_per_minute: int = Field(ge=0)


class KeyRequest(BaseModel):
    key: str
