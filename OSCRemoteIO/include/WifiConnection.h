#ifdef WIFI
#include "Connection.h"
#include <WiFi.h>

class WifiConnection : public Connection
{
private:
    const char* m_ssid;
    const char* m_pass;

    WiFiClient m_activeClient;

public:
    bool connect() override
    {
        WiFi.begin(m_ssid, m_pass);

        while (!(
            (WiFi.status() == WL_CONNECTED) ||
            (WiFi.status() == WL_CONNECT_FAILED) ||
            (WiFi.status() == WL_NO_SSID_AVAIL)
        ))
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");

        if (WiFi.status() == WL_CONNECTED)
        {
            this->updateStatus(Connection::NetworkStatus::CONNECTED);
            Serial.println("Connected to WiFi");
            
            this->m_deviceIp = WiFi.localIP();
            Serial.println(m_deviceIp);

            return true;
        }
        else
        {
            Serial.println("Failed to connect to WiFi");
            return false;
        }
    }

    void initServer() override
    {
        m_pServer = new WiFiServer(SERVER_PORT, 1);
    }

    bool checkForNewClientConnection()
    {
        if (m_activeClient)
        {
            m_activeClient.stop();
        }

        m_activeClient = reinterpret_cast<WiFiServer*>(m_pServer)->available();

        if (!m_activeClient)
        {
            // no client
            return false;
        }

        // new client w/ data is available
        return true;
    }

    Client* getActiveClient() override
    {
        if (!(this->m_activeClient))
        {
            return nullptr;
        }
        else
        {
            return &this->m_activeClient;
        }
    }

    WifiConnection(
        int listenPort,
        uint8_t macAddr[6],
        const char* ssid,
        const char* pass
    ):
        Connection(listenPort, macAddr),
        m_ssid(ssid),
        m_pass(pass)
    {
        
    }
};


#endif