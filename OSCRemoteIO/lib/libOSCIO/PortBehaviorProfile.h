#ifndef PORT_BEHAVIOR_DEFINED
#define PORT_BEHAVIOR_DEFINED

#include "IOscMessageHandler.h"

template <typename T>
class PortBehaviorProfile : public IOscMessageHandler
{
protected:
    T* m_pPort;

public:
    virtual void init() = 0;
    virtual void update() = 0;

protected:
    PortBehaviorProfile(T* pPort):
        m_pPort(pPort)
    {

    }
    ~PortBehaviorProfile(){}
};

#endif