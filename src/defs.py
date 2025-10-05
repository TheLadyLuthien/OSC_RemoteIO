from enum import Enum, auto
from abc import ABC, abstractmethod
from os import getenv

from connection import Connection

OSC_CLIENT_UDP_HOST:str = getenv("OSC_CLIENT_UDP_HOST", "")
OSC_CLIENT_UDP_PORT:int = int(getenv("OSC_CLIENT_UDP_PORT", ""))
OSC_SERVER_UDP_HOST:str = getenv("OSC_SERVER_UDP_HOST", "")
OSC_SERVER_UDP_PORT:int = int(getenv("OSC_SERVER_UDP_PORT", ""))

class NetworkMode(Enum):
    WIFI = auto()
    ETHERNET = auto()

class IDeviceConfig(ABC):

    @abstractmethod
    def createConnection(self) -> Connection:
        pass

    NETWORK_MODE: NetworkMode

