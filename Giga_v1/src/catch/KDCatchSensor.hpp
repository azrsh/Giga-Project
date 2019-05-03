#ifndef KD_CATCH_SENSORS_h
#define KD_CATCH_SENSORS_h

#include "../utilities/KDMacroUtilities.hpp"

class KDCatchSensor
{
  private:
    uint8_t pin;

  public:
    KDCatchSensor(uint8_t pin) : pin(pin){};
    INLINE int read() { return analogRead(pin); }
    void printValue();
};

#endif
