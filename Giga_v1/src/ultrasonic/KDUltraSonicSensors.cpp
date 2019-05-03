#include <Arduino.h>
#include <Wire.h>
#include "../hardware/KDHardwere.hpp"
#include "../utilities/KDDebugUtility.hpp"
#include "KDUltraSonicSensor.hpp"
#include "KDUltraSonicSensors.hpp"

void KDUltraSonicSensors::update()
{
    enum FieldArea previousArea = currentArea;
    const int front = frontSensor->read();
    const int rear = rearSensor->read();
    const int right = rightSensor->read();
    const int left = leftSensor->read();
    if (front + rear)
    {
    }
}

enum FieldArea KDUltraSonicSensors::getCurrentArea()
{
    return currentArea;
}

int KDUltraSonicSensors::getFrontDistance() { return frontSensor->read(); }
int KDUltraSonicSensors::getRearDistance() { return rearSensor->read(); }
int KDUltraSonicSensors::getRightDistance() { return rightSensor->read(); }
int KDUltraSonicSensors::getLeftDistance() { return leftSensor->read(); }

void KDUltraSonicSensors::printValue()
{
    KDDebugUtility::printValueWithTag("Front", frontSensor->read());
    KDDebugUtility::printValueWithTag("Rear", rearSensor->read());
    KDDebugUtility::printValueWithTag("Right", rightSensor->read());
    KDDebugUtility::printValueWithTag("Left", leftSensor->read());
    KDDebugUtility::println();
}
