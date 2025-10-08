from src.connection import Connection, WifiConnection
from src.defs import IDeviceConfig, NetworkMode
from os import getenv

DEFAULT_SSID = ""
DEFAULT_PASS = ""

class DeviceProfile(IDeviceConfig):
    NETWORK_MODE = NetworkMode.WIFI

    def createConnection(self) -> Connection: 
        return WifiConnection(getenv("WIFI_SSID", DEFAULT_SSID), getenv("WIFI_PASSWORD", DEFAULT_PASS))

DEVICE_CONFIG = DeviceProfile()