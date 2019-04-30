#include <Arduino.h>
#include <Wire.h>
#include "KDHardwere.hpp"
#include "KDDebugUtility.hpp"
#include "KDUltraSonicSensors.hpp"

void KDUltraSonicSensors::printValue()
{
    KDDebugUtility::printValueWithTag("Front", getFrontDistance());
    KDDebugUtility::printValueWithTag("Rear", getRearDistance());
    KDDebugUtility::printValueWithTag("Right", getRightDistance());
    KDDebugUtility::printValueWithTag("Left", getLeftDistance());
    KDDebugUtility::println();
}
