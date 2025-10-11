#include <Arduino.h>
#include "Port.h"
#include "Connection.h"
#include "IOscMessageHandler.h"

class PortManager : public IOscMessageHandler
{
private:
    Port* m_ports[BOARD_PORT_COUNT];

    bool m_locked = false;

    Connection* m_pConnection;

public:
    bool registerPort(Port* pPort)
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

    void freeze()
    {
        m_locked = true;
    }

    void process()
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

    bool portIdInRange(unsigned int id)
    {
        return ((id > 0) && (id <= BOARD_PORT_COUNT));
    }

    Port* getPortById(unsigned int id)
    {
        if (!portIdInRange(id))
        {
            return nullptr;
        }

        return m_ports[id - 1];
    }

    void handleOscMessage(String remainingPath, MicroOscMessage& msg) override
    {
        Serial.println(" - OSC Message handled by PortManager");
        for (size_t i = 0; i < BOARD_PORT_COUNT; i++)
        {
            String testStr = String("/") + String(i + 1);
            IOscMessageHandler::testHandler(testStr, m_ports[i], remainingPath, msg);
        }
    }

    Connection* getConnection()
    {
        return m_pConnection;
    }

    PortManager(Connection* pConnection):
        m_pConnection(pConnection)
    {
    }
    ~PortManager(){}
};
