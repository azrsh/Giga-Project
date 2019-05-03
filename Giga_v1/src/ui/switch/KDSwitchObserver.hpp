#ifndef KD_SWITCH_OBSERVER_h
#define KD_SWITCH_OBSERVER_h

class KDLineSensors;
class TonePlayer;

class KDSwitchObserver
{
  public:
    KDSwitchObserver(KDLineSensors *lineSensors, TonePlayer *tonePlayer)
        : lineSensorsInstance(lineSensors), tonePlayerInstance(tonePlayer){};
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
    TonePlayer *tonePlayerInstance;
};

#endif