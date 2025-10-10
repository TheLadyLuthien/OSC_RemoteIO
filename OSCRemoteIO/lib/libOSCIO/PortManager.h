#include <Arduino.h>
#include "Port.h"

#define MAX_PORTS 64

class PortManager
{
private:
    const unsigned int m_portCount;

    Vector<Port> m_ports;
    /* data */
public:
    PortManager(int portCount):
        m_portCount(portCount)
    {
        m_ports = new Port[portCount];
    }
    ~PortManager(){}
};
