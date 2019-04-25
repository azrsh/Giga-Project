#ifndef KD_SWITCH_OBSERVER_h
#define KD_SWITCH_OBSERVER_h

class KDSwitchObserver
{
  public:
    void reset();
    bool readMainSwitch();
    bool readDashSwitch();
    void printValue();

  private:
    bool previousMainSwitch = false;
    bool previousDashSwitch = false;
    bool mainSwitch = false;
    bool dashSwitch = false;
};

#endif