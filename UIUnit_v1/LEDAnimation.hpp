#include <Arduino.h>
#include "digitalWriteFast.h"

struct
{
    int8_t R;
    int8_t G;
    int8_t B;
} typedef Color_t;

class LEDAnimation
{
  private:
    const int8_t *ColorPinMap;
    const int8_t *LEDPinMap;

  public:
    LEDAnimation(int8_t colorPinMap[3], int8_t ledPinMap[10]) : ColorPinMap(colorPinMap), LEDPinMap(ledPinMap)
    {
        for (int i = 0; i < 3; i++)
            pinMode(ColorPinMap[i], OUTPUT);
        for (int i = 0; i < 10; i++)
            pinMode(LEDPinMap[i], OUTPUT);
    }
    ~LEDAnimation() {}

    void draw(Color_t color, int map)
    {
        setColor(color);
        for (int i = 0; i < 10; i++)
        {
            int highOrLow = (map & 1 << i) >> i;
            digitalWrite(LEDPinMap[i], highOrLow);
        }
    }

    void setColor(Color_t color)
    {
        analogWrite(ColorPinMap[0], 255 - color.R);
        analogWrite(ColorPinMap[1], 255 - color.G);
        analogWrite(ColorPinMap[2], 255 - color.B);
    }
};
