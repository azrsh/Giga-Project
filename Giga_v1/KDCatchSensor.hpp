#ifndef KD_CATCH_SENSORS_h
#define KD_CATCH_SENSORS_h

class KDCatchSensor
{
  public:
    INLINE int read() { return analogRead(KDHardwere::CatchSensorPin); }
    void printValue();
};

#endif
