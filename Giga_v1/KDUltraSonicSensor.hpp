#ifndef KD_ULTRA_SONIC_SENSOR_h
#define KD_ULTRA_SONIC_SENSOR_h

#include "KDMacroUtilities.hpp"

class KDUltraSonicSensor
{
  private:
    const uint8_t pin;
    const float correctionValue;

  public:
    KDUltraSonicSensor(uint8_t pin, float correction) : pin(pin), correctionValue(correction){};
    INLINE int read() { return round(analogRead(pin) * correctionValue); }
};

#endif
