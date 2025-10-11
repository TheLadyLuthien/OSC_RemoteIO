#include "Port.h"
#include "PortManager.h"

bool PortManager::registerPort(Port* pPort)
{
    unsigned int portId = pPort->getPortId();
    if ((m_locked) ||
        (portId > BOARD_PORT_COUNT) ||
        (m_ports[portId - 1] != nullptr))
    {
        if (m_locked)
        {
            Serial.println("failed to register port: port manager frozen");
        }
        if (portId > BOARD_PORT_COUNT)
        {
            Serial.println("failed to register port: port id greater that ports supported");
        }
        if (m_ports[portId - 1] != nullptr)
        {
            Serial.println("failed to register port: port already registered");
        }
        return false;
    }

    m_ports[portId - 1] = pPort;

    pPort->onRegister(this);

    return true;
}

void PortManager::process()
{
    for (size_t i = 0; i < BOARD_PORT_COUNT; i++)
    {
        Port* pPort = m_ports[i];
        if ((pPort != nullptr) && pPort->isEnabled())
        {
            pPort->update();
        }
    }
}