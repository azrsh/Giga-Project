#ifndef KD_LINE_SENSORS_h
#define KD_LINE_SENSORS_h

#include "KDSharedObjects.hpp"
#include "KDHardwere.hpp"

class KDLineSensors
{
  public:
    INLINE bool CheckFrontLineSensor() { return digitalReadFast(KDHardwere::FrontLineSensorPin); }
    INLINE bool CheckRearLineSensor() { return digitalReadFast(KDHardwere::RearLineSensorPin); }
    INLINE bool CheckRightLineSensor() { return digitalReadFast(KDHardwere::RightLineSensorPin); }
    INLINE bool CheckLeftLineSensor() { return digitalReadFast(KDHardwere::LeftLineSensorPin); }
    /*INLINE bool CheckFrontLineSensor() { return digitalReadFast(KDHardwere::FrontLineSensorPin); }
    INLINE bool CheckRearLineSensor() { return analogRead(KDHardwere::RearLineSensorPin) > 900; }
    INLINE bool CheckRightLineSensor() { return analogRead(KDHardwere::RightLineSensorPin) > 900; }
    INLINE bool CheckLeftLineSensor() { return analogRead(KDHardwere::LeftLineSensorPin) > 900; }*/
    void setWhiteValue();
    void setGreenValue();
    void setThreshold();
    void printValue();

  private:
    int whiteValue = 0;
    int greenValue = 0;
};

#endif
