#include <Arduino.h>
#include "KDGyroSensor.hpp"
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"

//_serialInstanceを元に戻すときはSerial1に置き換えること

void KDGyroSensor::init()
{
    _serialInstance->begin(115200);
}

void KDGyroSensor::reset()
{
    //digitalWriteFast(KDHardwere::GyroResetPin, HIGH);
    //delay(10);
    //digitalWriteFast(KDHardwere::GyroResetPin, LOW);
}

int KDGyroSensor::read()
{
    constexpr int Size = 2 + sizeof('H');
    while (_serialInstance->available() > Size)
    {
        char header = _serialInstance->read();
        if (header == 'H')
        {
            byte low = _serialInstance->read();
            byte high = _serialInstance->read();
            value = makeWord(high, low);
        }
    }
    return value;
}

void KDGyroSensor::printValue()
{
    int gyroValue = read();
    KDDebugUtility::printValueWithTag("Gyro", gyroValue);
    KDDebugUtility::println();
}