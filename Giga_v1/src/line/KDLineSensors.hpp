#ifndef KD_LINE_SENSORS_h
#define KD_LINE_SENSORS_h

#include "../hardware/KDHardwere.hpp"
#include "../utilities/KDMacroUtilities.hpp"

class KDLineSensors
{
  public:
    INLINE bool checkFrontLineSensor() { return digitalReadFast(KDHardwere::FrontLineSensorPin); }
    INLINE bool checkRearLineSensor() { return digitalReadFast(KDHardwere::RearLineSensorPin); }
    INLINE bool checkRightLineSensor() { return digitalReadFast(KDHardwere::RightLineSensorPin); }
    INLINE bool checkLeftLineSensor() { return digitalReadFast(KDHardwere::LeftLineSensorPin); }
    void setWhiteValue();
    void setGreenValue();
    void setThreshold();
    void printValue();

  private:
    int whiteValue = 0;
    int greenValue = 0;
};

#endif
