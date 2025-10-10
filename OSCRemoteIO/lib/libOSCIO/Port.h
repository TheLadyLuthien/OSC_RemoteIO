#include <Arduino.h>

enum class PortIoMode
{
    IO_NOT_SUPPORTED,
    IO_ENABLED,
    IO_DISABLED
};

class Port
{
private:
    const unsigned int m_portId;
    
public:
    virtual PortIoMode getInputMode()
    {
        return PortIoMode::IO_NOT_SUPPORTED;
    }
    virtual PortIoMode getOutputMode()
    {
        return PortIoMode::IO_NOT_SUPPORTED;
    }
    
protected:
    Port(int portId):
        m_portId(portId)
    {

    }


public:
    static Port createUninitializedPort(unsigned int portId)
    {
        return new Port(portId);
    }

    ~Port(){};
};

class SimpleFullIoPort : public Port
{
protected:
    const uint8_t m_inputPin;
    const uint8_t m_outputPin;

    bool m_isInputPullup;

public:
    SimpleFullIoPort(int portId, uint8_t inputPin, uint8_t outputPin, bool isInputPullup):
        Port(portId),
        m_inputPin(inputPin),
        m_outputPin(outputPin),
        m_isInputPullup(isInputPullup)
    {
        pinMode(m_inputPin, m_isInputPullup ? INPUT_PULLUP : INPUT);
        pinMode(m_outputPin, OUTPUT);
    }
};