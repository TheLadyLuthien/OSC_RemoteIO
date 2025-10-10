#ifdef BOARD_NET_WIFI

#include "Connection.h"
#include <WiFi.h>

class WifiConnection : public Connection
{
private:
    const char* m_ssid;
    const char* m_pass;

    WiFiClient m_activeHttpClient;

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
            onSuccessfulConnect();
            return true;
        }
        else
        {
            Serial.println("Failed to connect to WiFi");
            return false;
        }
    }

    void onSuccessfulConnect()
    {
        Serial.println("Connected to WiFi");

        m_deviceIp = WiFi.localIP();
        Serial.println(m_deviceIp);
            
        m_pUdp->begin(m_udpListenPort);
        m_pHttpServer->begin();
    }

    void initServers() override
    {
        m_pHttpServer = new WiFiServer(SERVER_PORT, 1);
        m_pOsc = new MicroOscUdp<OSC_PACKAGE_BITS>(m_pUdp, m_oscDestinationIp, m_oscDestinationPort);
    }

    bool checkForNewHttpClientConnection()
    {
        if (m_activeHttpClient)
        {
            m_activeHttpClient.stop();
        }

        m_activeHttpClient = reinterpret_cast<WiFiServer*>(m_pHttpServer)->available();

        if (!m_activeHttpClient)
        {
            // no client
            return false;
        }

        // new client w/ data is available
        return true;
    }

    Client* getActiveHttpClient() override
    {
        if (!(this->m_activeHttpClient))
        {
            return nullptr;
        }
        else
        {
            return &this->m_activeHttpClient;
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
        this->m_pUdp = new WiFiUDP();
    }
};


#endif