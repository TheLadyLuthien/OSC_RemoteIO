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
    const int m_udpListenPort;
    const uint8_t* m_macAddr;

    Server* m_pServer;
    ApiHandler* m_pApiHandler;
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
    virtual void initServer() = 0;

    // returns `true` if a new client was activated
    virtual bool checkForNewClientConnection() = 0;

    // returns `nullptr` is ther is no active client
    virtual Client* getActiveClient() = 0;


    virtual void configureApiEndpoints()
    {
        this->m_pApiHandler->get("/", [](Request& req, Response& res){
            res.print("Hello Network");
        });
    }

    // returns `true` if a request was processed this cycle
    bool processServer()
    {
        if(this->checkForNewClientConnection())
        {
            Client* pClient = this->getActiveClient();
        
            Serial.println("got here 64");
            this->m_pApiHandler->process(pClient);
            
            pClient->stop();
        }

        return true;
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



