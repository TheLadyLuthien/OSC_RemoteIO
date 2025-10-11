
#include "Core.h"

// the setup routine runs once when you press reset:
void setup()
{
    Serial.begin(115200);
#if defined(NEOPIXEL_POWER)
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

    Core* core = new Core();

    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    DeviceConfig config {
        5000,
        mac,
        "LaggyNet",
        "RabbitEars."
    };
    
    core->setConfig(config);
    
    core->init();
    
    {
        unsigned int i = 0;
        unsigned long start = millis();
        while(millis() < (start + 5000))
        {
            core->m_pStatusLightController->process();
            
            if (i % 10 == 0)
            {
                Serial.print('-');
            }

            delay(20);
            i++;
        }
    }
    Serial.println('\n');

    core->begin();
    
    while (true)
    {
        core->process();
    }
}

// the loop routine runs over and over again forever:
void loop()
{
}