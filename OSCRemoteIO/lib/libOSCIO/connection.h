#include <MicroOscUdp.h>

class Connection
{
protected:
    const int m_listenPort;
    const uint8_t* m_macAddr;

    UDP* m_pUdp; 
    
    IPAddress m_deviceIp;
    MicroOscUdp<1024>* m_pOsc;
    
public:
    virtual void connect();
    
public:
    Connection(int listenPort, uint8_t macAddr[6]):
        m_listenPort(listenPort),
        m_macAddr(macAddr)
    {

    }

    ~Connection() {

    }
};



