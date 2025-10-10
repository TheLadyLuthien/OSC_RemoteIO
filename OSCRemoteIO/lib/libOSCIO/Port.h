#include <Arduino.h>
#include "PortBehaviorProfile.h"

class Port
{
protected:
    const unsigned int m_portId;

    bool m_isEnabled = false;
    
public:
    virtual void update()
    {

    }

    unsigned int getPortId()
    {
        return m_portId;
    }

    bool isEnabled()
    {
        return m_isEnabled;
    }

protected:
    Port(int portId):
        m_portId(portId)
    {

    }

public:
    ~Port(){};
};

class DualPinPort : public Port
{
public:
    class BehaviorProfile : public PortBehaviorProfile<DualPinPort>
    {
    protected:
        BehaviorProfile(DualPinPort* pPort):
            PortBehaviorProfile(pPort)
        {

        }
    };

protected:
    BehaviorProfile* m_pBehaviorProfile = nullptr;

    uint8_t m_pinAMode;
    uint8_t m_pinBMode;
    

public:
    const uint8_t m_pinA;
    const uint8_t m_pinB;

    void setPinAMode(uint8_t mode)
    {
        m_pinAMode = mode;
        pinMode(m_pinA, mode);
    }
    void setPinBMode(uint8_t mode)
    {
        m_pinBMode = mode;
        pinMode(m_pinB, mode);
    }
    void setPinModes(uint8_t a, uint8_t b)
    {
        setPinAMode(a);
        setPinBMode(b);
    }

    void setBehaviorProfile(BehaviorProfile* pProfile)
    {
        if (m_pBehaviorProfile != nullptr)
        {
            // destroy old profile, nolonger eneded
            delete m_pBehaviorProfile;
        }

        m_pBehaviorProfile = pProfile;

        m_pBehaviorProfile->init();
    }

    void update()
    {
        if (m_pBehaviorProfile != nullptr)
        {
            m_pBehaviorProfile->update();
        }
    }
public:
    DualPinPort(int portId, uint8_t pinA, uint8_t pinB):
        Port(portId),
        m_pinA(pinA),
        m_pinB(pinB)
    {
    }
};
