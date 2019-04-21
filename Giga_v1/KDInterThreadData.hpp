#ifndef KD_INTER_THREAD_DATA_h
#define KD_INTER_THREAD_DATA_h
#include "KDSharedObjects.hpp"

class KDInterThreadData
{
  public:
    void read(VectorXY_t *vector ,unsigned long *timeStamp);
    void push(VectorXY_t vector);
  private:
    volatile bool isHold = false;
    volatile char x = 0;
    volatile char y = 0;
    volatile unsigned long timeStamp = 0;
    VectorXY_t pastVector = {0,0};
    unsigned long pastTimeStamp = 0;
};

#endif
