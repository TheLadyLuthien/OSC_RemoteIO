from defs import *
import microosc
import socketpool
import adafruit_httpserver as httpserver

import wifi

class Connection():
    connected: bool
    socketPool: socketpool.SocketPool
    apiServer: httpserver.Server
    oscClient: microosc.OSCClient
    oscServer: microosc.OSCServer


    def connect(self) -> bool:
        raise NotImplementedError

    def initSocketpool(self) -> None:
        raise NotImplementedError

    def initServers(self) -> None:
        self.oscServer = microosc.OSCServer(self.socketPool, OSC_SERVER_UDP_HOST, OSC_SERVER_UDP_PORT)
        self.oscClient = microosc.OSCClient(self.socketPool, OSC_CLIENT_UDP_HOST, OSC_CLIENT_UDP_PORT)
         

    
class WifiConnection(Connection):
    def __init__(self, wifiSSID:str, wifiPASS:str):
            self.wifiPASS = wifiPASS
            self.wifiSSID = wifiSSID

    wifiSSID: str
    wifiPASS: str

    def connect(self) -> bool:
        b: bool =  wifi.radio.connect(self.wifiSSID, self.wifiPASS) # type: ignore
        if (b):
            self.connected = True
        return b
    
    def initSocketpool(self) -> None:
        self.socketPool = socketpool.SocketPool(wifi.radio)
        
