#ifndef KD_SWITCH_OBSERVER_h
#define KD_SWITCH_OBSERVER_h

#include "TonePlayer.hpp"
#include "Pitches.hpp"

class KDSwitchObserver
{
  public:
    KDSwitchObserver(KDLineSensors *lineSensors) : lineSensorsInstance(lineSensors){};
    void reset();
    bool readMainSwitch();
    bool readDashSwitch();
    void printValue();

  private:
    bool previousMainSwitch = false;
    bool previousDashSwitch = false;
    bool mainSwitch = false;
    bool dashSwitch = false;
    KDLineSensors *lineSensorsInstance;
    int melody[1] = {Pitches::NoteC4};
    int noteDurations[1] = {4};
    TonePlayer tonePlayer = TonePlayer(1, melody, noteDurations);
};

#endif