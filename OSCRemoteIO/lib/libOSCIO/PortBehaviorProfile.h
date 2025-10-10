template <typename T>
class PortBehaviorProfile
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
