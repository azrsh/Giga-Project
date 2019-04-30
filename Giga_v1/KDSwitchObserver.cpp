#include <Arduino.h>
//#include "TonePlayer.hpp"
//#include "Pitches.hpp"
#include "KDLineSensors.hpp"
#include "KDSharedObjects.hpp"
#include "KDHardwere.hpp"
#include "KDDebugUtility.hpp"
#include "KDSwitchObserver.hpp"

void KDSwitchObserver::reset()
{
    //digitalWriteFast(KDHardwere::GyroResetPin, HIGH);
    //delay(10);
    //digitalWriteFast(KDHardwere::GyroResetPin, LOW);
}

bool KDSwitchObserver::readMainSwitch()
{
    bool switch1State = digitalReadFast(KDHardwere::Switch1Pin);
    bool switch2State = digitalReadFast(KDHardwere::Switch2Pin);
    static int falseCount = 0;
    if (previousMainSwitch && !switch1State)
    {
        mainSwitch = !mainSwitch;
        lineSensorsInstance->setGreenValue();
        lineSensorsInstance->setThreshold();
        tonePlayer.play();
    }
    /*if (!previousMainSwitch && switch1State)
    {
        mainSwitch = true;
    }
    if (switch1State && switch2State)
    {
        falseCount++;
    }
    else
    {
        falseCount = 0;
    }
    if (falseCount > 100)
        mainSwitch = false;*/

    previousMainSwitch = switch1State;

    return mainSwitch;
}

bool KDSwitchObserver::readDashSwitch()
{
    bool switch2State = digitalReadFast(KDHardwere::Switch2Pin);
    if (previousDashSwitch && !switch2State)
    {
        dashSwitch = !dashSwitch;
        lineSensorsInstance->setWhiteValue();
    }

    previousDashSwitch = switch2State;

    return dashSwitch;
}

void KDSwitchObserver::printValue()
{
    bool switch1State = digitalReadFast(KDHardwere::Switch1Pin);
    bool switch2State = digitalReadFast(KDHardwere::Switch2Pin);
    KDDebugUtility::printValueWithTag("rawMainSwitch", switch1State);
    KDDebugUtility::printValueWithTag("rawSubSwitch2", switch2State);
    bool mainSwitch = readMainSwitch();
    bool dashSwitch = readDashSwitch();
    KDDebugUtility::printValueWithTag("mainSwitch", mainSwitch);
    KDDebugUtility::printValueWithTag("subSwitch", dashSwitch);
    KDDebugUtility::println();
}