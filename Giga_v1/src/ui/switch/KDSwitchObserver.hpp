#ifndef KD_SWITCH_OBSERVER_h
#define KD_SWITCH_OBSERVER_h

#include <Arduino.h>
#include "KDSwitchObserver.hpp"
#include "../../utilities/KDDebugUtility.hpp"

template <uint8_t pin>
class KDSwitchObserver
{
  private:
    bool previousSwitch = false;
    bool switchState = false;
    const void (*onSwitch)();

  public:
    KDSwitchObserver(const void (*onSwitch)()) : onSwitch(onSwitch){};
    void reset()
    {
        previousSwitch = false;
        switchState = false;
    };
    bool read()
    {
        bool rawState = digitalReadFast(pin);
        if (previousSwitch && !rawState)
        {
            switchState = !switchState;
            onSwitch();
        }

        previousSwitch = rawState;

        return switchState;
    };
    void printValue()
    {
        bool rawState = digitalReadFast(pin);
        KDDebugUtility::printValueWithTag("rawSwitch", rawState);
        bool switchState = read();
        KDDebugUtility::printValueWithTag("switch", switchState);
        KDDebugUtility::println();
    };
};

#endif