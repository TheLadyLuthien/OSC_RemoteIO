#include "Port.h"
#include <Arduino.h>

class BasicExposedDualIOPortBehavior : public DualPinPort::BehaviorProfile
{
public:
    void update() override
    {
        // Serial.println("port upate");
        if (digitalRead(m_pPort->m_pinA) == LOW)
        {
            Serial.println("button pressed!!");
        }
    }
    
    void init() override
    {
        Serial.println("port INIT");
        m_pPort->setPinModes(INPUT_PULLUP, OUTPUT);
    }

    void handleOscMessage(String remainingPath, MicroOscMessage& msg) override
    {
        if (remainingPath.startsWith("/output/high") || remainingPath.startsWith("/output/on"))
        {
            digitalWrite(m_pPort->m_pinB, HIGH);
        }
        else if (remainingPath.startsWith("/output/low") || remainingPath.startsWith("/output/off"))
        {
            digitalWrite(m_pPort->m_pinB, LOW);
        }
    }
    
public:
    BasicExposedDualIOPortBehavior(DualPinPort* pPort):
        DualPinPort::BehaviorProfile(pPort)
    {
    }
    ~BasicExposedDualIOPortBehavior(){}
};
