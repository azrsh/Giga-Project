#include <Arduino.h>
#include <Wire.h>
#include "KDHardwere.hpp"
#include "../utilities/KDModeMacros.hpp"

//ハードウェア依存クラス

void KDHardwere::initialize()
{
#ifdef DEBUG_MODE
    Serial.begin(2000000);
#endif

    Wire.begin();
    setupDigitalPins();

    //周波数変更によってFTM0は死ぬ
    analogWriteFrequency(RightMotorDirectionPin, 100000);
    analogWriteFrequency(LeftMotorDirectionPin, 100000);
    analogWriteFrequency(RearMotorDirectionPin, 100000);
}

void KDHardwere::setupDigitalPins()
{
    pinMode(KickerPin, OUTPUT);

    pinMode(RightMotorDirectionPin, OUTPUT);
    pinMode(LeftMotorDirectionPin, OUTPUT);
    pinMode(RearMotorDirectionPin, OUTPUT);

    pinMode(FrontLineSensorPin, INPUT);
    pinMode(RearLineSensorPin, INPUT);
    pinMode(RightLineSensorPin, INPUT);
    pinMode(LeftLineSensorPin, INPUT);

    pinMode(Switch1Pin, INPUT);
    pinMode(Switch2Pin, INPUT);

    pinMode(SpeakerPin, OUTPUT);

    pinMode(LEDPin, OUTPUT);
}
