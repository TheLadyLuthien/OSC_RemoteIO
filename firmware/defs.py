from os import getenv

from connection import Connection

OSC_CLIENT_UDP_HOST:str = getenv("OSC_CLIENT_UDP_HOST", "")
OSC_CLIENT_UDP_PORT:int = int(getenv("OSC_CLIENT_UDP_PORT", ""))
OSC_SERVER_UDP_HOST:str = getenv("OSC_SERVER_UDP_HOST", "")
OSC_SERVER_UDP_PORT:int = int(getenv("OSC_SERVER_UDP_PORT", ""))

class NetworkMode():    
    WIFI = 1
    ETHERNET = 2

class IDeviceConfig():

    def createConnection(self) -> Connection:
        raise NotImplementedError

    NETWORK_MODE: NetworkMode

