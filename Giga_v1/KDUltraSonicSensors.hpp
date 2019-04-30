#ifndef KD_ULTRA_SONIC_SENSORS_h
#define KD_ULTRA_SONIC_SENSORS_h

class KDUltraSonicSensors
{
  public:
    INLINE int getFrontDistance() { return (int)(analogRead(KDHardwere::FrontUSSensorPin) * 0.3); }
    INLINE int getRearDistance() { return (int)(analogRead(KDHardwere::RearUSSensorPin) * 0.3); }
    INLINE int getRightDistance() { return (int)(analogRead(KDHardwere::RightUSSensorPin) * 0.3); }
    INLINE int getLeftDistance() { return (int)(analogRead(KDHardwere::LeftUSSensorPin) * 0.3); }
    void printValue();
};

#endif
