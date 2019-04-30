#ifndef KD_ULTRA_SONIC_SENSORS_h
#define KD_ULTRA_SONIC_SENSORS_h

class KDUltraSonicSensors
{
  public:
    inline int getFrontDistance() { return (int)(analogRead(KDHardwere::FrontUSSensorPin) * 0.3); }
    inline int getRearDistance() { return (int)(analogRead(KDHardwere::RearUSSensorPin) * 0.3); }
    inline int getRightDistance() { return (int)(analogRead(KDHardwere::RightUSSensorPin) * 0.3); }
    inline int getLeftDistance() { return (int)(analogRead(KDHardwere::LeftUSSensorPin) * 0.3); }
    void printValue();
};

#endif
