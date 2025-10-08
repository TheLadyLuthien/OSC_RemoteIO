
from device import DEVICE_CONFIG
from src.defs import *

CONNECTION = DEVICE_CONFIG.createConnection()

if (CONNECTION.connect()):
    print("Connected to network")

