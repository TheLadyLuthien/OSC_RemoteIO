#include "Port.h"
#include "PortManager.h"
#include <Arduino.h>

class ArmableTriggerPortBehavior : public DualPinPort::BehaviorProfile
{
protected:
    bool m_armed = false;

    bool m_pressed = false;
    unsigned long m_lastPressed = 0;
    unsigned int m_retriggerDelay = 100;

public:
    void arm()
    {
        m_armed = true;
        digitalWrite(m_pPort->m_pinB, HIGH);
    }

    void disarm()
    {
        m_armed = false;
        digitalWrite(m_pPort->m_pinB, LOW);
    }

    bool canTrigger()
    {
        return m_armed && !m_pressed && (millis() > (m_lastPressed + m_retriggerDelay));
    }

    void update() override
    {
        bool pressed = (digitalRead(m_pPort->m_pinA) == LOW);
        
        if (pressed && canTrigger())
        {
            Serial.println("Triggered");
            // m_pPort->getPortManager()->getConnection()->m_pOsc->send;
            m_lastPressed = millis();
        }

        m_pressed = pressed;
    }
    
    void init() override
    {
        m_pPort->setPinModes(INPUT_PULLUP, OUTPUT);
    }

    void handleOscMessage(String remainingPath, MicroOscMessage& msg) override
    {
        if (remainingPath.startsWith("/arm"))
        {
            arm();
        }
        else if (remainingPath.startsWith("/disarm"))
        {
            disarm();
        }
    }
    
public:
    ArmableTriggerPortBehavior(DualPinPort* pPort):
        DualPinPort::BehaviorProfile(pPort)
    {
    }
    ~ArmableTriggerPortBehavior(){}
};
