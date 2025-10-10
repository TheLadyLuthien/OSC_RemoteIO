#include <Adafruit_NeoPixel.h>
#include "WifiConnection.h"

// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup()
{
    Serial.begin(115200);

#if defined(NEOPIXEL_POWER)
    // If this board has a power control pin, we must set it to output and high
    // in order to enable the NeoPixels. We put this in an #if defined so it can
    // be reused for other boards without compilation errors
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

    pixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.setBrightness(20); // not so bright

    Serial.println("Hello!");
    delay(6000);
    // say hi
    Serial.println("Hello!");

    // set color to red
    pixels.fill(0x00FF00);
    pixels.show();
    delay(100); // wait half a second

    // turn off
    pixels.fill(0x000000);
    pixels.show();
    delay(500); // wait half a second

    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

    WifiConnection* connection = new WifiConnection(5000, mac, "LaggyNet", "RabbitEars.");

    connection->initServers();

    connection->configureHttpApiEndpoints();
    connection->setOscMessageHandler([](MicroOscMessage& receivedOscMessage){
        // if (receivedOscMessage.checkOscAddress("/test"))
        // {
            Serial.println("OSC Message recieved!");
        // }
    });

    connection->connect();
    

    while (true)
    {
        connection->processOscInbound();
        connection->processHttpServer();
    }
}

// the loop routine runs over and over again forever:
void loop()
{
    while (true)
    {
        delay(5000);
    }
}