#include "connection.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#ifdef ETHERNET

class EthernetConnection : Connection
{
private:
    /* data */
public:
    void connect() override
    {
        Ethernet.init(BOARD_PIN_NET_CS);

        if (Ethernet.begin(m_macAddr) == 0)
        {

        }
    }
public:
};

#endif