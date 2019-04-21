#include <Arduino.h>
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"
#include "KDCatchSensor.hpp"

void KDCatchSensor::printValue()
{
    int catchSensprValue = read();
    KDDebugUtility::printValueWithTag("Catch", catchSensprValue);
    KDDebugUtility::println();
}
