#include <Arduino.h>

struct DeviceConfig
{
    int listenPort;
    byte* macAddr;
    const char* ssid;
    const char* pass;
};
