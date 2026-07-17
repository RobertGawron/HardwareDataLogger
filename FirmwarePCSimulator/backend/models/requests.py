from pydantic import BaseModel


class SpeedRequest(BaseModel):
    tick_interval: float


class PulseRequest(BaseModel):
    values: list[int]


class KeyRequest(BaseModel):
    key: str
