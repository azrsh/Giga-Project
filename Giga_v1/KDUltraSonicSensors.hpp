#ifndef KD_ULTRA_SONIC_SENSORS_h
#define KD_ULTRA_SONIC_SENSORS_h

class KDUltraSonicSensors
{
  public:
    inline int GetRightDistance() { return (int)(analogRead(KDHardwere::RightUSSensorPin) * 0.3); }
    inline int GetLeftDistance() { return (int)(analogRead(KDHardwere::LeftUSSensorPin) * 0.3); }
    void printValue();
};

#endif
