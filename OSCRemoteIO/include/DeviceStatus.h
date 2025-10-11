#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum class DeviceStatus
{
    STARTING_UP,
    CONNECTING,
    READY,
    WORKING,
    RUN_ERROR,
    NETWORK_ERROR
};

class StatusLightController
{
private:
    const uint8_t m_neopixelPin;
    const uint8_t m_pixelCount;

    Adafruit_NeoPixel m_pixels;

    const DeviceStatus* m_pStatus;

    // h: 0-360
    // s: 0-100
    // v: 0-100
    uint32_t easyHSV(unsigned int h, uint8_t s, uint8_t v)
    {
        return m_pixels.ColorHSV(map(h, 0, 360, 0, 65535), map(s, 0, 100, 0, 255), map(v, 0, 100, 0, 255));
    }

public:
    StatusLightController(DeviceStatus* pStatus, uint8_t neopixelPin, uint8_t pixelCount, neoPixelType type):
        m_pixels(Adafruit_NeoPixel(pixelCount, neopixelPin, type)),
        m_neopixelPin(neopixelPin),
        m_pixelCount(pixelCount),
        m_pStatus(pStatus)
    {
        m_pixels.setBrightness(30);
        m_pixels.clear();
        m_pixels.show();
    }

    void process()
    {
        const unsigned int t = millis();
        double offset = sin(2.0 * PI * ((double)t / 700.0));

        uint32_t color = 0xFF0000;

        switch (*m_pStatus)
        {
            case DeviceStatus::STARTING_UP:
            {
                color = easyHSV(24, 100, (int)(60.0 + (40.0 * offset)));
            }break;
            
            case DeviceStatus::CONNECTING:
            {
                color = easyHSV(240, 100, 100 * (int)((offset + 1.0)));
            }break;
            
            case DeviceStatus::READY:
            {
                color = easyHSV(120, 100, 50);
            }break;
            
            case DeviceStatus::WORKING:
            {
                color = easyHSV(120, 100, (int)(70.0 + (30.0 * offset)));
            }break;
            
            case DeviceStatus::RUN_ERROR:
            {
                color = easyHSV(0, 100, (int)(70.0 + (30.0 * offset)));
            }break;
            
            case DeviceStatus::NETWORK_ERROR:
            {
                color = easyHSV(0, 100, (int)((offset + 1.0)));
            }break;
        }
        
        m_pixels.setPixelColor(0, color);
        m_pixels.show();
    }
};