#ifndef KD_DEBUG_UTILITY_h
#define KD_DEBUG_UTILITY_h

#include <Arduino.h>
#include "KDSharedObjects.hpp"

class KDDebugUtility
{
  public:
    INLINE static void println()
    {
#ifdef DEBUG_MODE
        Serial.println();
#endif
    };
    INLINE static void printString(const char str[])
    {
#ifdef DEBUG_MODE
        Serial.print(str);
#endif
    };
    INLINE static void printInt(int value)
    {
#ifdef DEBUG_MODE
        Serial.print(value);
        Serial.print("  ");
#endif
    };
    INLINE static void printValueWithTag(const char *tag, int value)
    {
#ifdef DEBUG_MODE
        Serial.print(tag);
        Serial.print(" : ");
        Serial.print(value);
        Serial.print("  ");
#endif
    };

    static void printMovementData(VectorDD_t *ballLocalVector, int targetDegrees, int bodyDirection, int targetAttitude, int angularVelocity, int power)
    {
#ifdef DEBUG_MODE
        KDDebugUtility::printValueWithTag("BDeg", ballLocalVector->degrees);
        KDDebugUtility::printValueWithTag("Dis", ballLocalVector->distance);
        KDDebugUtility::printValueWithTag("TarDeg", targetDegrees);
        KDDebugUtility::printValueWithTag("BodyDirection", bodyDirection);
        KDDebugUtility::printValueWithTag("TarAtti", targetAttitude);
        KDDebugUtility::printValueWithTag("Angular", angularVelocity);
        KDDebugUtility::printValueWithTag("Power", power);
        Serial.println();
#endif
    };
};

#endif