#include <Arduino.h>
#include "KDInterThreadData.hpp"
#include "KDSharedObjects.hpp"

void KDInterThreadData::read(VectorXY_t *vector ,unsigned long *timeStamp)
{
   if(isHold) 
   {
       *vector = pastVector;
       *timeStamp = pastTimeStamp;
       return;
   }

   isHold = true;
    *vector = {(int)this->x,(int)this->y};
    *timeStamp = this->timeStamp;
    pastVector = {(int)this->x,(int)this->y};
    pastTimeStamp = this->timeStamp;
    isHold = false;
}

void KDInterThreadData::push(VectorXY_t vector)
{
   if(isHold) return;
   isHold = true;
   this->x = vector.x;
   this->y = vector.y;
   this->timeStamp = millis();
   isHold = false;
}