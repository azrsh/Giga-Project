#include <Arduino.h>
#include "KDUIUnitCommunication.hpp"
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"

//_serialInstanceを元に戻すときはSerial1に置き換えること

void KDUIUnitCommunication::init()
{
    _serialInstance->begin(11520);
}

void KDUIUnitCommunication::reset()
{
    /*digitalWriteFast(KDHardwere::GyroResetPin, HIGH);
    delay(10);
    digitalWriteFast(KDHardwere::GyroResetPin, LOW);*/
}

int KDUIUnitCommunication::read()
{
    constexpr int Size = 2 + sizeof(HederCharacter);
    while (_serialInstance->available() > Size)
    {
        char header = _serialInstance->read();
        if (header == HederCharacter)
        {
            const byte centerSwitch = _serialInstance->read();
            const byte sideSwitch = _serialInstance->read();
            value = centerSwitch;
            Serial.println("recieved");
        }
    }
    return value;
}

void KDUIUnitCommunication::printValue()
{
    int gyroValue = read();
    KDDebugUtility::printValueWithTag("Gyro", gyroValue);
    KDDebugUtility::println();
}