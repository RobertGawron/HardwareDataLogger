from enum import Enum


class SimulationKey(Enum):
    """Enumeration for simulation key events."""
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3


class GPIOID(Enum):
    """Enumeration for GPIO identifiers."""
    GPIO1 = 13
    GPIO2 = 2
    GPIO3 = 3