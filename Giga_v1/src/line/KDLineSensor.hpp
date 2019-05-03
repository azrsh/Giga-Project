#ifndef KD_LINE_SENSOR_h
#define KD_LINE_SENSOR_h

#include "../utilities/KDMacroUtilities.hpp"
#include "../hardware/KDHardwere.hpp"

//未使用

template <uint8_t pin>
class KDLineSensor
{
  public:
    INLINE bool read() { return digitalReadFast(pin); }
    INLINE int analogRead() { return analogRead(pin); }
};

#endif
