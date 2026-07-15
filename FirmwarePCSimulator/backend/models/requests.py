from pydantic import BaseModel
from typing import List

class SpeedRequest(BaseModel):
    tick_interval: float


class PulseRequest(BaseModel):
    values: List[int]


class KeyRequest(BaseModel):
    key: str