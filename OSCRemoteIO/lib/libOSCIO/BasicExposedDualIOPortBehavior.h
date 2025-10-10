#include "Port.h"
#include <Arduino.h>

class BasicExposedDualIOPortBehavior : public DualPinPort::BehaviorProfile
{
public:
    void update() override
    {
        if (digitalRead())
    }

    void init() override
    {
        m_pPort->setPinModes(INPUT_PULLUP, OUTPUT);
    }
    
public:
    BasicExposedDualIOPortBehavior(DualPinPort* pPort):
        DualPinPort::BehaviorProfile(pPort)
    {
    }
    ~BasicExposedDualIOPortBehavior(){}
};
