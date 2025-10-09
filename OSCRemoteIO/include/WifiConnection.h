#ifdef WIFI
#include "Connection.h"
#include <WiFi.h>


class WifiConnection : public Connection
{
private:
    const char* m_ssid;
    const char* m_pass;
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

    void test()
    {
        Serial.println("Testing mode enabled");
        while (true)
        {
            WiFiClient client = reinterpret_cast<WiFiServer*>(m_pServer)->available();
            if (client == true)
            {
                bool currentLineIsBlank = true;

                while (client.connected())
                {

                    if (client.available())
                    {


                        char c = client.read();


                        Serial.write(c);


                        // if you've gotten to the end of the line (received a newline


                        // character) and the line is blank, the http request has ended,


                        // so you can send a reply


                        if (c == '\n' && currentLineIsBlank) {
                            client.println("testing!! Woot Woot!");
        
                            delay(1);
                            client.stop();
                        }
                    }
                }
            }
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
        m_pServer = new WiFiServer(SERVER_PORT, 1);
    }
};


#endif