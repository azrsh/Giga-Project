#include <Arduino.h>
#include "KDSwitchObserver.hpp"
#include "KDHardwere.hpp"
#include "KDSharedObjects.hpp"
#include "KDDebugUtility.hpp"

void KDSwitchObserver::reset()
{
    //digitalWriteFast(KDHardwere::GyroResetPin, HIGH);
    //delay(10);
    //digitalWriteFast(KDHardwere::GyroResetPin, LOW);
}

bool KDSwitchObserver::readMainSwitch()
{
    bool switch1State = digitalReadFast(KDHardwere::Switch1Pin);
    if (previousMainSwitch && !switch1State)
        mainSwitch = !mainSwitch;

    previousMainSwitch = switch1State;

    return mainSwitch;
}

bool KDSwitchObserver::readDashSwitch()
{
    bool switch2State = digitalReadFast(KDHardwere::Switch2Pin);
    if (previousDashSwitch && !switch2State)
        dashSwitch = !dashSwitch;

    previousDashSwitch = switch2State;

    return dashSwitch;
}

void KDSwitchObserver::printValue()
{
    bool mainSwitch = readMainSwitch();
    bool dashSwitch = readDashSwitch();
    KDDebugUtility::printValueWithTag("mainSwitch", mainSwitch);
    KDDebugUtility::printValueWithTag("dashSwitch", dashSwitch);
    KDDebugUtility::println();
}