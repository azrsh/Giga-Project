#ifndef KD_KICKER_h
#define KD_KICKER_h

#include "KDDebugUtility.hpp"

class KDKicker
{
  public:
    void init();
    void kick();
    void kickWithSerialPrint()
    {
        KDDebugUtility::printString("Kick");
        KDDebugUtility::println();
        kick();
    }

  private:
    unsigned long pastKickTime = 0;
};

#endif
