#include <Arduino.h>
#include <Wire.h>
#include "KDHardwere.hpp"
#include "KDDebugUtility.hpp"
#include "KDUltraSonicSensors.hpp"

void KDUltraSonicSensors::printValue()
{
    KDDebugUtility::printValueWithTag("Right", GetRightDistance());
    KDDebugUtility::printValueWithTag("Left", GetLeftDistance());
    KDDebugUtility::println();
}
