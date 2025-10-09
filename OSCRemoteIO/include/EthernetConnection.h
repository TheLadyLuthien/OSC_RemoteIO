#ifdef ETHERNET

#include "connection.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


class EthernetConnection : public Connection
{
private:
    /* data */
public:
    bool connect() override
    {
        Ethernet.init(BOARD_PIN_NET_CS);

        if (Ethernet.begin(m_macAddr) == 0)
        {

        }
    }
public:
};

#endif