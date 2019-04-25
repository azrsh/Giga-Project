#include "LEDAnimation.hpp"

constexpr int8_t CenterSwitchPin = 8;
constexpr int8_t SideSwitchPin = 9;

constexpr int8_t colorPinMap[3] =
    {
        /* red   */ A2,
        /* green */ A0,
        /* blue  */ A1,
};
constexpr int8_t ledPinMap[10] =
    {
        10,
        A3,
        A4,
        A5,
        2,
        3,
        4,
        5,
        6,
        7,
};
LEDAnimation ledAnimation = LEDAnimation(colorPinMap, ledPinMap);

void setup()
{
    Serial.begin(115200);
    pinMode(CenterSwitchPin, INPUT);
    pinMode(SideSwitchPin, INPUT);
}

void loop()
{
    bool centerSwitch = digitalReadFast(CenterSwitchPin);
    bool sideSwitch = digitalReadFast(SideSwitchPin);
    writeData(centerSwitch, sideSwitch);
    delay(10);
}

void printData(bool centerSwitch, bool sideSwitch)
{
    Serial.print("center : ");
    Serial.write(centerSwitch);
    Serial.print("    side : ");
    Serial.write(sideSwitch);
    Serial.println();
}

void writeData(bool centerSwitch, bool sideSwitch)
{
    Serial.print('S');
    Serial.write(centerSwitch);
    Serial.write(sideSwitch);
}
