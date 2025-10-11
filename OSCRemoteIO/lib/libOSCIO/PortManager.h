#ifndef PORT_MANAGER_DEFINED
#define PORT_MANAGER_DEFINED

#include <Arduino.h>
#include "Connection.h"
#include "IOscMessageHandler.h"

class Port;

class PortManager : public IOscMessageHandler
{
private:
    Port* m_ports[BOARD_PORT_COUNT] = {nullptr};

    bool m_locked = false;

    Connection* m_pConnection;

public:
    bool registerPort(Port* pPort);

    void freeze()
    {
        m_locked = true;
    }

    void process();

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


#endif