#ifndef I_OSC_MESSAGE_HANDLER
#define I_OSC_MESSAGE_HANDLER

#include <MicroOscMessage.h>
#include <Arduino.h>

class IOscMessageHandler
{
public:
    virtual void handleOscMessage(String path, MicroOscMessage& msg) = 0;

    static bool testHandler(String testPath, IOscMessageHandler* handler, String path, MicroOscMessage& msg)
    {
        if (path.startsWith(testPath))
        {
            handler->handleOscMessage(path.substring(testPath.length()), msg);

            return true;
        }

        return false;
    }

    static bool testHandler(String testPath, MicroOsc::tOscCallbackFunction handler, String path, MicroOscMessage& msg)
    {
        if (path.startsWith(testPath))
        {
            handler(msg);

            return true;
        }

        return false;
    }
};

#endif