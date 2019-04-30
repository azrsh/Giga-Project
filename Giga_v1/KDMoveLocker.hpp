#ifndef KD_MOVE_LOCKER_h
#define KD_MOVE_LOCKER_h

#include "KDMacroUtilities.hpp"

class KDMoveLocker
{
  private:
    char lockX = 0;
    char lockY = 0;

  public:
    KDMoveLocker(){};
    ~KDMoveLocker(){};
    int getLockedDegree(int degrees) const;
    VectorXY_t getLockedVector(VectorXY_t vector) const;
    INLINE void lockMovement(char x, char y)
    {
        lockX = x;
        lockY = y;
    };
    INLINE void unlockMovement()
    {
        lockX = 0;
        lockY = 0;
    };
};

#endif