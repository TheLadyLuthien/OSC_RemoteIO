#include "libOSCIO.h"
#include "WifiConnection.h"
#include "Config.h"
#include "DeviceStatus.h"
#include "behavior/ArmableTriggerPortBehavior.h"

class Core
{
private:
    static Core* s_pInstance;

    DeviceStatus m_deviceStatus;

public:
    PortManager* m_pPortManager;
    Connection* m_pConnection;

    StatusLightController* m_pStatusLightController;
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

        m_deviceStatus = DeviceStatus::STARTING_UP;
        m_pStatusLightController = new StatusLightController(&m_deviceStatus, BOARD_STATUS_LIGHT_PIN, BOARD_STATUS_LIGHT_COUNT, BOARD_STATUS_LIGHT_NEOTYPE);
    }

    static Core* getInstance()
    {
        return s_pInstance;
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

        m_pPortManager = new PortManager(m_pConnection);

        DualPinPort* pPort = new DualPinPort(
            1,
            A0,
            A1
        );
        m_pPortManager->registerPort(pPort);

        pPort->setBehaviorProfile(new ArmableTriggerPortBehavior(pPort));

        m_pConnection->initServers();
        
        m_pConnection->configureHttpApiEndpoints();
        m_pConnection->setOscMessageHandler(handleOscMessage);
    }

    void begin()
    {
        m_deviceStatus = DeviceStatus::CONNECTING;
        
        m_pPortManager->freeze();
        m_pConnection->connect();

        m_deviceStatus = DeviceStatus::READY;
    }

    void process()
    {
        m_pPortManager->process();
        
        m_pConnection->processOscInbound();
        m_pConnection->processHttpServer();
        
        m_pStatusLightController->process();
    }
};