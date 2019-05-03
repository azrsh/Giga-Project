#ifndef KD_SWITCH_OBSERVER_h
#define KD_SWITCH_OBSERVER_h

#include <Arduino.h>
#include "KDSwitchObserver.hpp"
#include "../../utilities/KDDebugUtility.hpp"
#include "../../sound/TonePlayer.hpp"

template <uint8_t switch1Pin, uint8_t switch2Pin>
class KDSwitchObserver
{
  private:
    bool previousMainSwitch = false;
    bool previousDashSwitch = false;
    bool mainSwitch = false;
    bool dashSwitch = false;
    TonePlayer *tonePlayerInstance;

  public:
    KDSwitchObserver(TonePlayer *tonePlayer)
        : tonePlayerInstance(tonePlayer){};
    void reset(){};
    bool readMainSwitch()
    {
        bool switch1State = digitalReadFast(switch1Pin);
        bool switch2State = digitalReadFast(switch2Pin);
        static int falseCount = 0;
        if (previousMainSwitch && !switch1State)
        {
            mainSwitch = !mainSwitch;
            //lineSensorsInstance->setGreenValue();
            //lineSensorsInstance->setThreshold();
            tonePlayerInstance->play();
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
    };
    bool readDashSwitch()
    {
        bool switch2State = digitalReadFast(KDHardwere::Switch2Pin);
        if (previousDashSwitch && !switch2State)
        {
            dashSwitch = !dashSwitch;
            //lineSensorsInstance->setWhiteValue();
        }

        previousDashSwitch = switch2State;

        return dashSwitch;
    };
    void printValue()
    {
        bool switch1State = digitalReadFast(switch1Pin);
        bool switch2State = digitalReadFast(switch2Pin);
        KDDebugUtility::printValueWithTag("rawMainSwitch", switch1State);
        KDDebugUtility::printValueWithTag("rawSubSwitch2", switch2State);
        bool mainSwitch = readMainSwitch();
        bool dashSwitch = readDashSwitch();
        KDDebugUtility::printValueWithTag("mainSwitch", mainSwitch);
        KDDebugUtility::printValueWithTag("subSwitch", dashSwitch);
        KDDebugUtility::println();
    };
};

#endif