#include <Arduino.h>
#include "Port.h"

class PortManager
{
private:
    Port* m_pPorts[BOARD_PORT_COUNT];

    bool m_locked = false;

public:
    bool registerPort(Port* pPort)
    {
        unsigned int portId = pPort->getPortId();
        if ((m_locked) ||
            (portId > BOARD_PORT_COUNT) ||
            (m_pPorts[portId - 1] != nullptr))
        {
            return false;
        }

        m_pPorts[portId - 1] = pPort;
        return true;
    }

    void freeze()
    {
        m_locked = true;
    }

    void process()
    {
        for (size_t i = 0; i < BOARD_PORT_COUNT; i++)
        {
            Port* pPort = m_pPorts[i];
            if ((pPort != nullptr) && pPort->isEnabled())
            {
                pPort->update();
            }
        }
    }

    PortManager()
    {
    }
    ~PortManager(){}
};
