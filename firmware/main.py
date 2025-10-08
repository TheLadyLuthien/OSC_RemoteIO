
from device import DEVICE_CONFIG
from defs import *

CONNECTION = DEVICE_CONFIG.createConnection()

if (CONNECTION.connect()):
    print("Connected to network")

