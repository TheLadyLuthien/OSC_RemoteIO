#include <MicroOscUdp.h>
#include <aWOT.h>

using ApiHandler = Application;

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
    IPAddress m_oscDestinationIp;
    unsigned int m_oscDestinationPort;
    
    UDP* m_pUdp; 
    MicroOscUdp<1024>* m_pOsc;

    MicroOsc::tOscCallbackFunction m_pOscMessageHandler = nullptr;

protected:
    const unsigned int m_udpListenPort;
    const uint8_t* m_macAddr;

    Server* m_pHttpServer;
    ApiHandler* m_pApiHandler;
    
    IPAddress m_deviceIp;
    IPAddress m_deviceFallbackIp;


    void updateStatus(NetworkStatus status)
    {
        m_status = status;
    }
    
public:
    virtual bool connect() = 0;
    virtual void initServers() = 0;

    // returns `true` if a new client was activated
    virtual bool checkForNewHttpClientConnection() = 0;

    // returns `nullptr` is ther is no active client
    virtual Client* getActiveHttpClient() = 0;
    
    virtual void configureHttpApiEndpoints()
    {
        this->m_pApiHandler->get("/", [](Request& req, Response& res){
            res.print("Hello Network");
            Serial.println("Hello network!!!");
        });
    }
    
    void setOscMessageHandler(MicroOsc::tOscCallbackFunction pHandler)
    {
        this->m_pOscMessageHandler = pHandler;
    }
    
    // returns `true` if a request was processed this cycle
    bool processHttpServer()
    {
        if(this->checkForNewHttpClientConnection())
        {
            Client* pClient = this->getActiveHttpClient();
        
            this->m_pApiHandler->process(pClient);
            
            pClient->stop();
            return true;
        }

        return false;
    }

    void processOscInbound()
    {
        if (m_pOscMessageHandler != nullptr)
        {
            m_pOsc->onOscMessageReceived(m_pOscMessageHandler);
        }
    }

    NetworkStatus getStatus()
    {
        return this->m_status;
    }

public:
    Connection(int listenPort, uint8_t macAddr[6]):
        m_udpListenPort(listenPort),
        m_macAddr(macAddr),
        m_pApiHandler(new ApiHandler())
    {

    }

    ~Connection() {
        if (this->m_pApiHandler != nullptr)
        {
            delete m_pApiHandler;
        }
    }

};



