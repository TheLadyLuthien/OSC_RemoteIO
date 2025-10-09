#include <MicroOscUdp.h>

class Connection
{
public:
    enum class NetworkStatus
    {
        CONNECTED,
        CONNECTING,
        NOT_INITIALIZED,
        DISCONNECTED_FAILED,
        DISCONNECTED_LOST
    };

private:
    NetworkStatus m_status = NetworkStatus::NOT_INITIALIZED;

protected:
    const int m_udpListenPort;
    const uint8_t* m_macAddr;

    Server* m_pServer;
    UDP* m_pUdp; 
    
    IPAddress m_deviceIp;
    IPAddress m_deviceFallbackIp;

    MicroOscUdp<1024>* m_pOsc;

    void updateStatus(NetworkStatus status)
    {
        m_status = status;
    }
    
public:
    virtual bool connect() = 0;
    
    void initServer()
    {
        m_pServer->begin();
    }
    
    NetworkStatus getStatus()
    {
        return this->m_status;
    }

public:
    Connection(int listenPort, uint8_t macAddr[6]):
        m_udpListenPort(listenPort),
        m_macAddr(macAddr)
    {

    }

    ~Connection() {
        if (this->m_pServer != nullptr)
        {
            delete m_pServer;
        }
    }

};



