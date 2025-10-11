#include "libOSCIO.h"
#include "WifiConnection.h"
#include "Config.h"

class Core
{
private:
    static Core* s_pInstance;

protected:
    PortManager* m_pPortManager = new PortManager();
    Connection* m_pConnection;

    DeviceConfig m_config;

    static void handleOscMessage(MicroOscMessage& msg)
    {
        Serial.println("OSC Message recieved!");

        Core* core = s_pInstance;
        
        char path[OSC_MAX_PATH_LENGTH];
        msg.copyAddress(path, OSC_MAX_PATH_LENGTH);
        
        String msgPath = String(path);

        IOscMessageHandler::testHandler("/port", core->m_pPortManager, msgPath, msg);
    }
    
public:

    Core()
    {
        s_pInstance = this;
    }

    void setConfig(DeviceConfig& deviceConfig)
    {
        m_config = deviceConfig;
    }

    void init()
    {
        #ifdef BOARD_NET_WIFI
        m_pConnection = new WifiConnection(m_config.listenPort, m_config.macAddr, m_config.ssid, m_config.pass);
        #endif

        DualPinPort* pPort = new DualPinPort(
            1,
            A0,
            A1
        );
        pPort->setBehaviorProfile(new BasicExposedDualIOPortBehavior(pPort));
        m_pPortManager->registerPort(pPort);

        m_pConnection->initServers();
        
        m_pConnection->configureHttpApiEndpoints();
        m_pConnection->setOscMessageHandler(handleOscMessage);
    }

    void begin()
    {
        m_pPortManager->freeze();

        m_pConnection->connect();
    }

    void process()
    {
        m_pPortManager->process();
        
        m_pConnection->processOscInbound();
        m_pConnection->processHttpServer();
    }
};