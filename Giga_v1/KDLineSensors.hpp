#ifndef KD_LINE_SENSORS_h
#define KD_LINE_SENSORS_h

#include "KDMacroUtilities.hpp"
#include "KDHardwere.hpp"

class KDLineSensors
{
  public:
    INLINE bool CheckFrontLineSensor() { return digitalReadFast(KDHardwere::FrontLineSensorPin); }
    INLINE bool CheckRearLineSensor() { return digitalReadFast(KDHardwere::RearLineSensorPin); }
    INLINE bool CheckRightLineSensor() { return digitalReadFast(KDHardwere::RightLineSensorPin); }
    INLINE bool CheckLeftLineSensor() { return digitalReadFast(KDHardwere::LeftLineSensorPin); }
    void setWhiteValue();
    void setGreenValue();
    void setThreshold();
    void printValue();

  private:
    int whiteValue = 0;
    int greenValue = 0;
};

#endif
